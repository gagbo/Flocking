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

#include "engineantscene.h"

#define DEFAULT_TIMESTEP 100
#define DEFAULT_WIDTH 960
#define DEFAULT_HEIGHT 540

EngineAntScene::EngineAntScene(int dim) : dimension(dim)
{
    hei = DEFAULT_HEIGHT;
    wid = DEFAULT_WIDTH;
    time_step = DEFAULT_TIMESTEP;
    setSceneRect(-wid/2.0, -hei/2.0, wid, hei);
    setItemIndexMethod(QGraphicsScene::BspTreeIndex);
}

EngineAntScene::~EngineAntScene()
{
    for (auto ant : ant_list) {
        delete ant;
    }
    ant_list.clear();
}

void
EngineAntScene::add_ant(Victor position)
{
    Ant* new_ant = new Ant(position);
    ant_list.push_back(new_ant);
    new_ant->set_dt(time_step);
    addItem(new_ant);
}
