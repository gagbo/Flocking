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

#include <QGraphicsItem>
#include <iostream>

class Ant : public QGraphicsItem
{
  public:
    static uint next_id;     //!< Id to use for the next created Ant
    static uint count_alive; //!< Counts the number of Ant currently allocated
    /////////////// Constructors

    //! Construct a new Ant to move in d dimensions (default 2)
    Ant(int dim = 2);

    //! Construct a new Ant at position
    Ant(const Victor &position);

    /////////////// Destructor
    ~Ant();

    /////////////// Methods

    //! Give an approximate bounding rectangle for the Ant
    QRectF boundingRect() const override;

    //! Give the shape of the Ant for collision detection
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    //! Update the position and velocity of ant, reset acceleration
    /*! Also where friction and/or mass and/or other members can be updated
     * based on the new position
     */
    void update();

    //! Update the position so it stays always in Scene
    /*! The scene is supposed centered around (0,0)
     * so we just check position against +/- {width, height}/2
     */
    void wrap_around_position();

    //! Decide where to go. Set acceleration properly to prepare for update
    void decision(float width, float height);

    //! Return the capped accel needed to reach target
    /*! \param target should be the position of the target
     * the method will then compute the difference (Ant -> target)
     * and compute the acceleration Victor to reach it.
     */
    Victor capped_accel_to(const Victor &target) const;

    //! Return the capped accel needed to reach target velocity
    /*! \param target_velocity is the velocity we want to reach
     */
    inline Victor
    capped_accel_towards(const Victor &target_velocity) const
    {
        Victor fake_target = position + time_step * target_velocity;
        Victor result = capped_accel_to(fake_target);
        std::cerr << "capped_accel towards : " << target_velocity << " is "
                  << result << "\n";
        return result;
    }

    //! Return the acceleration needed to reach target
    /*! \param target should be the position of the target
     * the method will then compute the difference (Ant -> target)
     * and compute the acceleration Victor to reach it.
     */
    Victor accel_to(const Victor &target) const;

    //! Return the acceleration needed to reach target velocity
    /*! \param target_velocity is the velocity we want to reach
     */
    inline Victor
    accel_towards(const Victor &target_velocity) const
    {
        Victor fake_target = position + time_step * target_velocity;
        Victor result = accel_to(fake_target);
        std::cerr << "accel towards : " << target_velocity << " is " << result
                  << "\n";
        return result;
    }

    /////////////// Decision methods

    Victor decision_separation_velocity() const;
    Victor decision_alignment_velocity() const;
    Victor decision_cohesion_velocity() const;

    inline float
    x() const
    {
        return position[0];
    }
    inline float
    y() const
    {
        return position[1];
    }
    inline float
    z() const
    {
        return position.is_2d() ? 0.0 : position[2];
    }

    inline void
    set_dt(float dt)
    {
        time_step = dt;
    }

    friend std::ostream &operator<<(std::ostream &os, const Ant &ant);

  protected:
    void advance(int phase) override;
    int id;              //!< Global Ant Id
    Victor position;     //!< Position
    Victor velocity;     //!< Velocity
    Victor accel;        //!< Acceleration
    float mass;          //!< Mass of the Ant
    float friction;      //!< Friction seen by the ant
    float max_force;     //!< Maximum force the Ant can apply to move itself
    QColor color;        //!< Color
    float time_step;     //!< Time step given from the engine
    float view_distance; //!< View distance
};
#endif // _ANT_ANT_H_
