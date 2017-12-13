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

#include <limits>

uint Ant::next_id = 0;
uint Ant::count_alive = 0;

Ant::Ant(int dim)
{
    id = Ant::next_id++;
    Ant::count_alive++;
    position = Victor(dim);
    velocity = Victor(dim);
    accel = Victor(dim);
    mass = 1;
    friction = 0;
    max_force = std::numeric_limits<float>::max();
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
Ant::update(float dt)
{
    // accel = capped_accel_to(target, dt);
    // accel = capped_accel_towards(direction, dt);
    velocity += dt * accel;
    velocity *= (1.0 - friction);
    position += dt * velocity;
    accel.zero();
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
