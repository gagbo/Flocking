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
#include <vector>
#include <QGraphicsScene>

class EngineAntScene : public QGraphicsScene
{
  public:
    EngineAntScene(int dim = 2);
    ~EngineAntScene();

    void add_ant(Victor position);

    inline float
    dt()
    {
        return time_step;
    }
    inline float
    width()
    {
        return wid;
    }
    inline float
    height()
    {
        return hei;
    }

    inline const std::vector<Ant*> &
    list()
    {
        return ant_list;
    }

    inline void
    set_wid(float width)
    {
        wid = width;
    }

    inline void
    set_hei(float height)
    {
        hei = height;
    }

    inline void
    set_dt(float dt)
    {
        time_step = dt;
    }

  protected:
    std::vector<Ant*> ant_list;
    int dimension;
    float time_step;
    float wid;
    float hei;
};

#endif // _ENGINE_ENGINEANTSCENE_H_
