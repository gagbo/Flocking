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

#include <QApplication>
#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QtWidgets>
#include <iostream>

#include "FlockingConfig.h"
#include "ant.h"
#include "mainwindow.h"

int
main(int argc, char *argv[])
{
    std::cout << argv[0] << " Version " << Flocking_VERSION_MAJOR << "."
              << Flocking_VERSION_MINOR << std::endl;

    srand(static_cast<unsigned>(time(NULL)));

    QApplication app(argc, argv);
    QCoreApplication::setOrganizationName("Gerry A");
    QCoreApplication::setApplicationName("Flocking Autonomous Agents");
    QCoreApplication::setApplicationVersion(QT_VERSION_STR);
    QCommandLineParser parser;
    parser.setApplicationDescription(QCoreApplication::applicationName());
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("width",
                                 "The width of the visualization panel");
    parser.addPositionalArgument("height",
                                 "The height of the visualization panel");
    parser.addPositionalArgument("time_step", "The time step of the engine");
    parser.process(app);

    float time_step = 1000.0 / 50.0;
    int ant_starting_count = 200;
    float world_width = 3160.0;
    float world_height = 2160.0;
    MainWindow mainWin(time_step, ant_starting_count, world_width, world_height);
    mainWin.show();

    QTimer timer;
    QObject::connect(&timer, SIGNAL(timeout()), mainWin.getScene(),
                     SLOT(advance()));
    timer.start(time_step);
    return app.exec();
}
