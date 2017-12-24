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

#include "mainwindow.h"

MainWindow::MainWindow(float dt, int ant_count, float world_wid, float world_hei, float min_speed, float max_speed, float win_wid, float win_hei) : main_view(new EngineView(dt))
{
    setCentralWidget(main_view);
    main_view->setSceneRect(-world_wid / 2, -world_hei / 2,
                            world_wid, world_hei);

    for (int i = 0; i < ant_count; ++i) {
        float rand_x = -world_wid / 2.0 +
                       static_cast<float>(rand()) /
                           (static_cast<float>(RAND_MAX / world_wid));
        float rand_y = -world_hei / 2.0 +
                       static_cast<float>(rand()) /
                           (static_cast<float>(RAND_MAX / world_hei));
        float rand_vx =
            min_speed +
            static_cast<float>(rand()) /
                (static_cast<float>(RAND_MAX / (max_speed - min_speed)));
        float rand_vy =
            min_speed +
            static_cast<float>(rand()) /
                (static_cast<float>(RAND_MAX / (max_speed - min_speed)));
        main_view->add_ant(rand_x, rand_y, rand_vx, rand_vy);
    }

    createActions();
    createStatusBar();
    resize(win_wid, win_hei);
    move((win_wid - width()) / 2,
         (win_hei - height()) / 2);

    setUnifiedTitleAndToolBarOnMac(true);

    connect(main_view->getScene(), SIGNAL(message(QString)), this,
            SLOT(showMessage(QString)));
}

void
MainWindow::closeEvent(QCloseEvent *event)
{
    event->accept();
    // event->ignore();
}

void
MainWindow::createActions()
{
    menuBar()->addMenu("&File");
    menuBar()->addMenu("&Edit");
    menuBar()->addMenu("&View");
    menuBar()->addMenu("&Simulate");
    menuBar()->addMenu("&Help");
}

void
MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}

void
MainWindow::showMessage(QString msg)
{
    // display message on main window status bar
    statusBar()->showMessage(msg);
}
