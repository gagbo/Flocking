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
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QPainter>

EngineAntScene::EngineAntScene(float dt, int dim)
    : dimension(dim), time_step(dt), border_color(100, 255, 100)
{
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
EngineAntScene::add_ant(Victor position, Victor velocity)
{
    Ant *new_ant = new Ant(position, velocity);
    ant_list.push_back(new_ant);
    new_ant->set_dt(time_step);
    addItem(new_ant);
    new_ant->update(); // Called so the ant is at the right pos on first frame
}

void
EngineAntScene::drawForeground(QPainter *painter, const QRectF &rect)
{
    (void)rect; // We are not using the inherited parameter

    painter->setBrush(Qt::NoBrush);
    QPen pen(border_color, 3, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin);
    painter->setPen(pen);

    float wid = views()[0]->sceneRect().width();
    float hei = views()[0]->sceneRect().height();
    painter->drawRect(QRectF(-wid / 2.0, -hei / 2.0, wid, hei));
}

void
EngineAntScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Qt::MouseButton pressed_button = event->button();
    if (pressed_button == Qt::LeftButton) {
        float x = event->scenePos().x();
        float y = event->scenePos().y();
        emit message(QString("Clicked at (%1,%2)").arg(x).arg(y));
    } else if (pressed_button == Qt::MiddleButton) {
        emit scale_reset();
    }
    return;
}

void
EngineAntScene::wheelEvent(QGraphicsSceneWheelEvent *event)
{
    int eighths_deg = event->delta(); // >0 means scrolling up
    int direction = eighths_deg > 0 ? 1 : -1;
    float scale_factor = 1;

    scale_factor += 0.2 * direction;

    emit scale_change(scale_factor);
}
