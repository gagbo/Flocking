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

#include <QTest>
#include "victor.h"

class TestGeometry: public QObject
{
    Q_OBJECT
private slots:
    void addition(void);
    void substraction(void);
    void multiplication(void);
};

void TestGeometry::addition(void)
{
    Victor first(1., 2.);
    Victor second(3., 4.);
    Victor result(4., 6.);
    QCOMPARE(first[0] + second[0], result[0]);
    QCOMPARE(first[1] + second[1], result[1]);
}

void TestGeometry::substraction(void)
{
    Victor first(1., 6.);
    Victor second(3., 4.);
    Victor result(-2., 2.);
    QCOMPARE(first[0] - second[0], result[0]);
    QCOMPARE(first[1] - second[1], result[1]);
}

void TestGeometry::multiplication(void)
{
    float coef(1.2);
    Victor second(3., 4.);
    Victor result(3.6, 4.8);
    QCOMPARE(coef * second[0], result[0]);
    QCOMPARE(coef * second[1], result[1]);
}


QTEST_MAIN(TestGeometry)
#include "test_geometry.moc"
