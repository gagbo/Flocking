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

#ifndef _ANT_ANT_H_
#define _ANT_ANT_H_

#include "victor.h"

#include <iostream>

class Ant
{
  public:
    static uint next_id;     //!< Id to use for the next created Ant
    static uint count_alive; //!< Counts the number of Ant currently allocated
    /////////////// Constructors

    //! Construct a new Ant to move in d dimensions (default 2)
    Ant(int dim = 2);

    /////////////// Destructor
    ~Ant();

    /////////////// Methods

    //! Update the position and velocity of ant, reset acceleration
    /*! Also where friction and/or mass and/or other members can be updated
     * based on the new position
     */
    void update(float dt = 1);

    //! Return the capped accel needed to reach target in delay s
    /*! \param target should be the position of the target
     * the method will then compute the difference (Ant -> target)
     * and compute the acceleration Victor to reach it.
     * \param delay is the time in which we want to reach target.
     * it should be equal to the engine's time step
     */
    Victor capped_accel_to(const Victor &target, float delay = 1) const;

    //! Return the capped accel needed to reach target velocity in delay seconds
    /*! \param target_velocity is the velocity we want to reach
     * \param delay is the time in which we want to reach target velocity
     * it should be equal to the engine's time step
     */
    inline Victor
    capped_accel_towards(const Victor &target_velocity, float delay = 1)
    {
        Victor fake_target = position + delay * target_velocity;
        return capped_accel_to(fake_target, delay);
    }

    //! Return the acceleration needed to reach target in delay seconds
    /*! \param target should be the position of the target
     * the method will then compute the difference (Ant -> target)
     * and compute the acceleration Victor to reach it.
     * \param delay is the time in which we want to reach target
     * it should be equal to the engine's time step
     */
    Victor accel_to(const Victor &target, float delay = 1) const;

    //! Return the acceleration needed to reach target velocity in delay seconds
    /*! \param target_velocity is the velocity we want to reach
     * \param delay is the time in which we want to reach target velocity
     * it should be equal to the engine's time step
     */
    inline Victor
    accel_towards(const Victor &target_velocity, float delay = 1)
    {
        Victor fake_target = position + delay * target_velocity;
        return accel_to(fake_target, delay);
    }

    friend std::ostream &operator<<(std::ostream &os, const Ant &ant);

  protected:
    int id;
    Victor position; //!< Position
    Victor velocity; //!< Velocity
    Victor accel;    //!< Acceleration
    float mass;
    float friction;
    float max_force;
};
#endif // _ANT_ANT_H_
