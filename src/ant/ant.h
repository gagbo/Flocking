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

class Ant
{
  public:
    /////////////// Constructors
      
    //! Construct a new Ant to move in d dimensions (default 2)
    Ant(int dim = 2);
    
    //! Update the position and velocity of ant, reset acceleration
    /*! Also where friction and/or mass and/or other members can be updated
     * based on the new position
     */
    void update(void);
    
    //! Return the steering force needed to reach target, limited by max_force
    /*! target should be the position of the target
     * the method will then compute the difference (Ant -> target)
     * and compute the acceleration Victor to reach it.
     */
    Victor steer_to_capped(const Victor& target);
    
    //! Return the steering force needed to reach target
    /*! target should be the position of the target
     * the method will then compute the difference (Ant -> target)
     * and compute the acceleration Victor to reach it.
     */
    Victor steer_to(const Victor& target);

  protected:
    Victor position;
    Victor velocity_int; //!< Velocity integrated over engine tick
    Victor accel_int;    //!< Acceleration integrated over engine tick
    float mass;
    float friction;
    float max_force;
};
#endif  // _ANT_ANT_H_
