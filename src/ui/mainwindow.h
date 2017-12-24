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

#ifndef _UI_MAINWINDOW_H_
#define _UI_MAINWINDOW_H_

#include "engineantscene.h"
#include "engineview.h"
#include <QtWidgets>

#define WINDOW_DEFAULT_WIDTH 1440.0
#define WINDOW_DEFAULT_HEIGHT 768.0
#define VIEW_DEFAULT_WIDTH 3840.0
#define VIEW_DEFAULT_HEIGHT 2160.0
#define ANT_DEFAULT_COUNT 100
#define LO_SPEED -20.0
#define HI_SPEED 20.0

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    MainWindow(float dt, int ant_count = ANT_DEFAULT_COUNT, float world_wid = VIEW_DEFAULT_WIDTH,
        float world_hei = VIEW_DEFAULT_HEIGHT, float min_speed = LO_SPEED, float max_speed = HI_SPEED,
        float win_wid = WINDOW_DEFAULT_WIDTH, float win_hei = WINDOW_DEFAULT_HEIGHT
    );
    inline EngineAntScene *
    getScene()
    {
        return main_view->getScene();
    }

  protected:
    void closeEvent(QCloseEvent *event) override;

  public slots:
    //! Show message in status bar
    void showMessage(QString message);

  private slots:

  private:
    EngineView *main_view;
    void createActions();
    void createStatusBar();
};
#endif // _UI_MAINWINDOW_H_
