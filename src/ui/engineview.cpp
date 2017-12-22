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

#include "engineview.h"
#include <QGraphicsScene>
#include <QtGui/QPainter>
#include <QtWidgets>

EngineView::EngineView(float dt)
{
    ant_engine = new EngineAntScene(dt, 2);
    setScene(ant_engine);

    setRenderHint(QPainter::Antialiasing);
    setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    setDragMode(QGraphicsView::ScrollHandDrag);

    background = QBrush(QColor(64, 32, 64));
    setBackgroundBrush(background);

    xy_scale = 1;
    connect(ant_engine, SIGNAL(scale_change(float)), this,
            SLOT(change_scale(float)));
    connect(ant_engine, SIGNAL(scale_reset(void)), this,
            SLOT(reset_scale(void)));
}

EngineView::~EngineView()
{
    delete ant_engine;
}

void
EngineView::change_scale(float scale_factor)
{
    xy_scale *= scale_factor;
    scale(scale_factor, scale_factor);
    return;
}
