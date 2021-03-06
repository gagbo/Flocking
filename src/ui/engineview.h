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

#ifndef _UI_ENGINEVIEW_H_
#define _UI_ENGINEVIEW_H_

#include "ant.h"
#include "engineantscene.h"
#include <QGraphicsView>
#include <iostream>

class QPaintEvent;

class EngineView : public QGraphicsView
{
    Q_OBJECT

  public:
    EngineView(float dt);
    virtual ~EngineView();

    inline EngineAntScene *
    getScene() const
    {
        return ant_engine;
    }
    inline void
    add_ant(float x, float y, float vx = 0, float vy = 0)
    {
        ant_engine->add_ant(Victor(x, y), Victor(vx, vy));
    }

  public slots:
    void change_scale(float scale_factor);
    inline void
    reset_scale()
    {
        scale(1 / xy_scale, 1 / xy_scale);
        xy_scale = 1.0;
        return;
    }

  protected:
  private:
    EngineAntScene *ant_engine;
    QBrush background;
    float xy_scale;
};

#endif // _UI_ENGINEVIEW_H_
