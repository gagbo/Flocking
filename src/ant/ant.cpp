/* Copyright (c) 2017 Gerry Agbobada
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "ant.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>
#include <QtWidgets>
#include <limits>

#define ANT_DEF_FRICTION 0.1
#define ANT_DEF_MAX_FORCE 1
#define ANT_DEF_MASS 1000.0
#define ANT_DEF_VISION 50.0
#define ANT_DEF_VIEW_ANGLE 100.0

#define SPEED_ZERO_THRESHOLD 0.0001
#define PI 3.141592653589793
#define RAD_TO_DEG (180.0 / PI)

#define CRUISE_SPEED 1500.0
#define SEPARATION_POTENTIAL_EXP 0.5

uint Ant::next_id = 0;
uint Ant::count_alive = 0;
const QPointF Ant::triangle_body[3] = {QPointF(-10.0, 20.0),
                                       QPointF(10.0, 20.0), QPointF(0, -20.0)};

Ant::Ant(int dim) : color(35, 250, 20)
{
    id = Ant::next_id++;
    Ant::count_alive++;
    position = Victor(dim);
    velocity = Victor(dim);
    accel = Victor(dim);
    mass = ANT_DEF_MASS;
    friction = ANT_DEF_FRICTION;
    // max_force = std::numeric_limits<float>::max();
    max_force = ANT_DEF_MAX_FORCE;
    view_distance = ANT_DEF_VISION;
    view_angle = ANT_DEF_VIEW_ANGLE;
    world_wid = 0;
    world_hei = 0;

    // These values are very wrong and should be corrected by the engine
    vel_angle = 0;
    time_step = std::numeric_limits<float>::max();
}

Ant::Ant(const Victor &pos, const Victor &init_speed) : color(250, 250, 20)
{
    int dim = position.is_2d() ? 2 : 3;
    id = Ant::next_id++;
    Ant::count_alive++;
    position = pos;
    velocity = init_speed;
    accel = Victor(dim);
    mass = ANT_DEF_MASS;
    friction = ANT_DEF_FRICTION;
    // max_force = std::numeric_limits<float>::max();
    max_force = ANT_DEF_MAX_FORCE;
    view_distance = ANT_DEF_VISION;
    view_angle = ANT_DEF_VIEW_ANGLE;
    world_wid = 0;
    world_hei = 0;

    // These values are very wrong and should be corrected by the engine
    vel_angle = 0;
    time_step = std::numeric_limits<float>::max();
}

Ant::~Ant()
{
    Ant::count_alive--;
}

std::ostream &
operator<<(std::ostream &os, const Ant &ant)
{
    os << "Ant " << ant.id << " ( Mass = " << ant.mass
       << " ; Friction = " << ant.friction << " ; Max Force = " << ant.max_force
       << " )\n"
       << "Position    \t" << ant.position << "\n"
       << "Velocity    \t" << ant.velocity << "\n"
       << "Acceleration\t" << ant.accel << " -> Force is "
       << ant.mass * ant.accel
       << " ( norm = " << (ant.mass * ant.accel).p_norm() << " )\n";

    return os;
}

void
Ant::advance(int phase)
{
    if (phase == 0) {
        return;
    }

    decision();
    update();
    // std::cerr << "Advancing " << *this << std::endl;
}

QRectF
Ant::boundingRect() const
{
    float adjust = 0.5;
    return QRectF(-18 - adjust, -22 - adjust, 36 + adjust, 60 + adjust);
}

void
Ant::paint(QPainter *painter, const QStyleOptionGraphicsItem *dummy_style_opt,
           QWidget *dummy_widget)
{
    // Body
    painter->setBrush(color);
    if (velocity.p_norm() < SPEED_ZERO_THRESHOLD) {
        painter->setBrush(Qt::darkBlue);
    }
    // painter->drawEllipse(-10, -20, 20, 40);
    painter->drawPolygon(triangle_body, 3);

    // Eyes
    painter->setBrush(Qt::white);
    painter->drawEllipse(-10, -17, 8, 8);
    painter->drawEllipse(2, -17, 8, 8);
}

void
Ant::update()
{
    // accel = capped_accel_to(target, dt);
    // accel = capped_accel_towards(direction, dt);
    velocity += time_step * accel;
    velocity *= (1.0 - friction);
    position += time_step * velocity;

    wrap_around_position();

    accel.zero();
    vel_angle = 180 - RAD_TO_DEG * std::atan2(velocity[0], velocity[1]);
    setRotation(vel_angle);
    setPos(position[0], position[1]);
}

void
Ant::wrap_around_position()
{
    // TODO: Understand why those 2 lines below do not work vs the long method
    // float wid = scene()->views()[0]->width();
    // float hei = scene()->views()[0]->height();
    world_wid = scene()->views()[0]->sceneRect().width();
    world_hei = scene()->views()[0]->sceneRect().height();
    if (position[0] < -world_wid / 2.0) {
        do {
            position[0] += world_wid;
        } while (position[0] < -world_wid / 2.0);
    } else if (position[0] > world_wid / 2.0) {
        do {
            position[0] -= world_wid;
        } while (position[0] > world_wid / 2.0);
    }

    if (position[1] < -world_hei / 2.0) {
        do {
            position[1] += world_hei;
        } while (position[1] < -world_hei / 2.0);
    } else if (position[1] > world_hei / 2.0) {
        do {
            position[1] -= world_hei;
        } while (position[1] > world_hei / 2.0);
    }
}

Victor
Ant::point_to(const Ant &other) const
{
    if (world_hei == 0 || world_wid == 0) {
        return Victor(0.0, 0.0);
    }
    Victor naive_vec = other.position - position;
    if (naive_vec[0] > world_wid / 2.0) {
        naive_vec[0] -= world_wid;
    } else if (naive_vec[0] < -world_wid / 2.0) {
        naive_vec[0] += world_wid;
    }
    if (naive_vec[1] > world_hei / 2.0) {
        naive_vec[1] -= world_hei;
    } else if (naive_vec[1] < -world_hei / 2.0) {
        naive_vec[1] += world_hei;
    }

    return naive_vec;
}

QPainterPath
Ant::shape() const
{
    QPainterPath path;
    path.addRect(-10, -20, 20, 40);
    return path;
}

void
Ant::decision()
{
    // accel = capped_accel_to(Victor(width / 3.0, height / 4.0));
    neighbour_ants = scene()->items();
    neighbour_ants.clear();
    for (auto other_ant : scene()->items()) {
        if (other_ant == this) {
            neighbour_ants.push_back(other_ant);
            continue;
        }
        Victor to_other = point_to(*dynamic_cast<Ant *>(other_ant));
        if (to_other.p_norm() > view_distance) {
            continue;
        }
        float angle = vel_angle;
        angle -= 180 - RAD_TO_DEG * std::atan2(to_other[0], to_other[1]);

        if (std::abs(angle) > view_angle &&
            (360 - std::abs(angle)) > view_angle) {
            continue;
        }

        neighbour_ants.push_back(other_ant);
    }
    Victor decided_velocity(0.0, 0.0);
    decided_velocity = 0.125 * decision_cohesion_velocity();
    decided_velocity += 0.5 * decision_alignment_velocity();
    decided_velocity += 0.375 * decision_separation_velocity();
    accel = capped_accel_towards(decided_velocity);
    /* std::cerr << "Decided that accel = " << accel << " -> Force is "
     *           << mass * accel << " ( norm = " << (mass * accel).p_norm()
     *           << " )\n";
     */
}

Victor
Ant::accel_to(const Victor &target) const
{
    Victor desired_velocity = target - position;
    /* std::cerr << "Distance to " << target << " is " <<
     * desired_velocity.p_norm()
     *           << "\n";
     */
    desired_velocity /= time_step;
    Victor desired_accel = desired_velocity - velocity;
    desired_accel /= time_step;

    return desired_accel;
}

Victor
Ant::capped_accel_to(const Victor &target) const
{
    Victor desired_accel = accel_to(target);
    if (mass * desired_accel.p_norm() > max_force) {
        desired_accel.p_normalize();
        desired_accel *= max_force / mass;
    }

    return desired_accel;
}

Victor
Ant::decision_separation_velocity() const
{
    // Choose a distance at which boids start avoiding each other
    Victor desired(position.is_2d() ? 2 : 3);

    foreach (QGraphicsItem *item, neighbour_ants) {
        if (item == this) {
            continue;
        }
        Victor to_rival = point_to(dynamic_cast<const Ant &>(*item));
        Victor weighted_diff = -1 * to_rival;
        float dist = weighted_diff.p_norm();
        weighted_diff.p_normalize();
        weighted_diff /= pow((dist + view_distance / 4.0) / view_angle,
                             SEPARATION_POTENTIAL_EXP);
        desired += weighted_diff;
    }
    desired.p_normalize();
    desired *= CRUISE_SPEED / time_step;

    return desired;
}

Victor
Ant::decision_alignment_velocity() const
{
    Victor desired(position.is_2d() ? 2 : 3);

    int considered_neigbours = 0;
    foreach (QGraphicsItem *item, neighbour_ants) {
        ++considered_neigbours;
        desired += dynamic_cast<Ant *>(item)->velocity;
    }

    if (considered_neigbours > 0) {
        desired /= considered_neigbours;
    }

    desired.p_normalize();
    desired *= CRUISE_SPEED / time_step;

    return desired;
}

Victor
Ant::decision_cohesion_velocity() const
{
    Victor desired(position.is_2d() ? 2 : 3);

    foreach (QGraphicsItem *item, neighbour_ants) {
        desired += point_to(dynamic_cast<Ant &>(*item));
    }
    desired /= count_alive; // Now desired is the mean position

    desired.p_normalize();
    desired *= CRUISE_SPEED / time_step;

    return desired;
}
