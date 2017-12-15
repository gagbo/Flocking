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

#define ANT_DEF_FRICTION 0.2
#define ANT_DEF_MAX_FORCE 1
#define ANT_DEF_MASS 100.0
#define ANT_DEF_VISION 200.0
#define SPEED_ZERO_THRESHOLD 0.0001
#define PI 3.141592653589793
#define RAD_TO_DEG 180.0 / PI

uint Ant::next_id = 0;
uint Ant::count_alive = 0;

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
    world_wid = 0;
    world_hei = 0;
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
    world_wid = 0;
    world_hei = 0;
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
    if (!phase) {
        return;
    }

    decision();
    update();
    std::cerr << "Advancing " << *this << std::endl;
}

QRectF
Ant::boundingRect() const
{
    float adjust = 0.5;
    return QRectF(-18 - adjust, -22 - adjust, 36 + adjust, 60 + adjust);
}

void
Ant::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    // Body
    painter->setBrush(color);
    if (velocity.p_norm() < SPEED_ZERO_THRESHOLD) {
        painter->setBrush(Qt::darkBlue);
    }
    painter->drawEllipse(-10, -20, 20, 40);

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
    setRotation(180 - RAD_TO_DEG * std::atan2(velocity[0], velocity[1]));
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
    all_ants = scene()->items();
    Victor decided_velocity(0.0, 0.0);
    decided_velocity = 0.1 * decision_cohesion_velocity();
    decided_velocity += 0.5 * decision_alignment_velocity();
    decided_velocity += 0.4 * decision_separation_velocity();
    accel = capped_accel_towards(decided_velocity);
    std::cerr << "Decided that accel = " << accel << " -> Force is "
              << mass * accel << " ( norm = " << (mass * accel).p_norm()
              << " )\n";
}

Victor
Ant::accel_to(const Victor &target) const
{
    Victor desired_velocity = target - position;
    std::cerr << "Distance to " << target << " is " << desired_velocity.p_norm()
              << "\n";
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
    float separation = view_distance / 2;
    Victor desired(position.is_2d() ? 2 : 3);

    foreach (QGraphicsItem *item, all_ants) {
        if (item == this)
            continue;
        Victor to_rival = point_to(dynamic_cast<const Ant &>(*item));
        if (to_rival.p_norm() > separation) {
            continue;
        }
        Victor weighted_diff = -1 * to_rival;
        float dist = weighted_diff.p_norm();
        weighted_diff.p_normalize();
        weighted_diff /= dist;
        desired += weighted_diff;
    }

    return desired;
}

Victor
Ant::decision_alignment_velocity() const
{
    Victor desired(position.is_2d() ? 2 : 3);

    foreach (QGraphicsItem *item, all_ants) {
        desired += dynamic_cast<Ant *>(item)->velocity;
    }

    //desired /= count_alive;

    return desired;
}

Victor
Ant::decision_cohesion_velocity() const
{
    Victor desired(position.is_2d() ? 2 : 3);

    foreach (QGraphicsItem *item, all_ants) {
        desired += dynamic_cast<Ant *>(item)->position;
    }
    desired /= count_alive; // Now desired is the mean position
    desired -= position;    // Now desired is
                            // the vector from position to mean pos
    desired /= time_step;   // Now desired is
                            // the speed from position to mean pos

    return desired;
}
