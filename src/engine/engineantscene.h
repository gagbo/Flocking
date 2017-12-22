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

#ifndef _ENGINE_ENGINEANTSCENE_H_
#define _ENGINE_ENGINEANTSCENE_H_

#include "ant.h"
#include "victor.h"
#include <QGraphicsScene>
#include <vector>
#define DEFAULT_TIMESTEP 1

class QGraphicsSceneMouseEvent;

class EngineAntScene : public QGraphicsScene
{
    Q_OBJECT

  public:
    //! Default Constructor
    EngineAntScene(float dt = DEFAULT_TIMESTEP, int dim = 2);

    //! Destructor
    ~EngineAntScene();

    //! Constructs a new ant, and add it to this scene
    void add_ant(Victor position, Victor velocity = Victor(0, 0));

    //! Get the current time step
    inline float
    dt()
    {
        return time_step;
    }

    //! Get the list of ants owned by this scene
    inline std::vector<Ant *> &
    list()
    {
        return ant_list;
    }

    //! Set the current time step
    inline void
    set_dt(float dt)
    {
        time_step = dt;
    }

  signals:
    //! Emit a message to be read and/or printed by MainWindow
    void message(QString);

    //! Emit a signal to multiply the scale of the view by given factor
    void scale_change(float);

    //! Emit a signal to reset the scale of the view to 1:1
    void scale_reset(void);

  protected:
    std::vector<Ant *> ant_list; //!< List of the ants owned by the scene
    int dimension;               //!< Spatial dimension (probably always 2)
    float time_step;             //!< Time step of the physics engine
    QColor border_color; //!< Color of the border to draw where the scene wraps
                         //! around

    //! Draw a border around the views[0] scene rectangle
    /*! This is an overloaded method, the second parameter is not used.
     *  We use views[0] scene rectangle because this is how we choose the
     *  size of the world to begin with, in the constructor of MainWindow
     */
    void drawForeground(QPainter *, const QRectF &);

    //! Handle mouse button events to emit signals upwards
    /*! The Left button emits a message to tell where we clicked
     *  The middle button resets the scaling of the representation of the scene
     *  The right button does nothing yet (it should pop a menu someday)
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *);

    //! Handle mouse scroll events to emit zoom signals to the containing view
    void wheelEvent(QGraphicsSceneWheelEvent *);
};

#endif // _ENGINE_ENGINEANTSCENE_H_
