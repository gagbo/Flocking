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

#define WINDOW_DEFAULT_WIDTH 960 
#define WINDOW_DEFAULT_HEIGHT 540

MainWindow::MainWindow() : main_view(new EngineView)
{
    setCentralWidget(main_view);

    createActions();
    createStatusBar();
    resize(WINDOW_DEFAULT_WIDTH,
           WINDOW_DEFAULT_HEIGHT);
    move((WINDOW_DEFAULT_WIDTH - width()) / 2,
         (WINDOW_DEFAULT_HEIGHT - height()) / 2);

    setUnifiedTitleAndToolBarOnMac(true);
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
}

void
MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}
