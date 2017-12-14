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

#define ANT_DEF_FRICTION 0.5
#define ANT_DEF_MAX_FORCE 3.0
#define ANT_DEF_MASS 1.0

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
    max_force = std::numeric_limits<float>::max();
    max_force = ANT_DEF_MAX_FORCE;
}

Ant::Ant(const Victor &pos) : color(35, 250, 20)
{
    int dim = position.is_2d() ? 2 : 3;
    id = Ant::next_id++;
    Ant::count_alive++;
    position = pos;
    velocity = Victor(dim);
    accel = Victor(dim);
    mass = ANT_DEF_MASS;
    friction = ANT_DEF_FRICTION;
    max_force = std::numeric_limits<float>::max();
    max_force = ANT_DEF_MAX_FORCE;
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
       << "Acceleration\t" << ant.accel << "\n";

    return os;
}

void
Ant::advance(int phase)
{
    if (!phase) {
        return;
    }

    decision(960, 540, time_step);
    std::cerr << "Advancing " << *this << std::endl;
    update(time_step);
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
    painter->drawEllipse(-10, -20, 20, 40);
}

void
Ant::update(float dt)
{
    // accel = capped_accel_to(target, dt);
    // accel = capped_accel_towards(direction, dt);
    velocity += dt * accel;
    velocity *= (1.0 - friction);
    position += dt * velocity;

    accel.zero();
    // setRotation(std::atan2(velocity[1], velocity[0]));
    setPos(mapFromParent(position[0], position[1]));
}

QPainterPath
Ant::shape() const
{
    QPainterPath path;
    path.addRect(-10, -20, 20, 40);
    return path;
}

void
Ant::decision(float width, float height, float dt)
{
    accel = capped_accel_to(Victor(width / 2.0, height / 2.0), dt);
    std::cerr << "Decided that accel = " << accel << std::endl;
}

Victor
Ant::accel_to(const Victor &target, float delay) const
{
    Victor desired_velocity = target - position;
    desired_velocity /= delay;
    Victor desired_accel = desired_velocity;
    desired_accel /= delay;

    return desired_accel;
}

Victor
Ant::capped_accel_to(const Victor &target, float delay) const
{
    Victor desired_accel = accel_to(target, delay);
    if (mass * desired_accel.p_norm() > max_force) {
        desired_accel.p_normalize();
        desired_accel *= max_force / mass;
    }

    return desired_accel;
}
