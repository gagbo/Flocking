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

#include "victor.h"
#include <QTest>
#include <cmath>

Q_DECLARE_METATYPE(Victor);

class TestGeometry : public QObject
{
    Q_OBJECT
  private slots:
    void access(void);
    void comparison(void);
    void comparison_data(void);
    void zero(void);

    void pure_assignment(void);
    void addition(void);
    void addition_data(void);
    void substraction(void);
    void substraction_data(void);
    void multiplication(void);
    void multiplication_data(void);
    void division(void);
    void division_data(void);

    void is_2d(void);
    void p_norm(void);
    void p_norm_data(void);
    void p_normalize(void);
    void p_normalize_data(void);
};

void
TestGeometry::access(void)
{
    // Data
    float coord1(1.25);
    float coord2(-3.1);

    // Test
    Victor first(coord1, coord2);
    Victor second = Victor(coord1, coord2);
    QCOMPARE(first[0], coord1);
    QCOMPARE(first[1], coord2);
    QCOMPARE(second[0], coord1);
    QCOMPARE(second[1], coord2);
}

void
TestGeometry::comparison_data()
{
    QTest::addColumn<Victor>("first");
    QTest::addColumn<Victor>("second");
    QTest::addColumn<bool>("expected");

    QTest::newRow("Same initialisation")
        << Victor(1, 2) << Victor(1, 2) << true;
    QTest::newRow("Equal but different init")
        << Victor(-1 / 24., 3.245) << Victor(-2 / 48., 32450 / 10000.) << true;
    QTest::newRow("Same dimension, different vectors")
        << Victor(1.2, -0.3) << Victor(-1.2, 0.3) << false;
    QTest::newRow("Bad dimension so false first(2d)")
        << Victor(0.5, 0.8) << Victor(0.5, 0.8, 0) << false;
    QTest::newRow("Bad dimension so false first(3d)")
        << Victor(-1.2, 0.342, 0) << Victor(-1.2, 0.342) << false;
}

void
TestGeometry::comparison()
{
    // Data
    QFETCH(Victor, first);
    QFETCH(Victor, second);
    QFETCH(bool, expected);

    // Test
    QCOMPARE(first == second, expected);
}

void
TestGeometry::pure_assignment()
{
    // Data
    Victor first(0.0, 0.0);
    float coord1 = -1.9;
    float coord2 = 24.2;
    const Victor second(coord1, coord2);

    // Test
    first = second;
    QCOMPARE(first[0], second[0]);
    QCOMPARE(first[1], second[1]);
}

void
TestGeometry::addition_data(void)
{
    QTest::addColumn<Victor>("first");
    QTest::addColumn<Victor>("second");
    QTest::addColumn<Victor>("result");

    QTest::newRow("Simple positive")
        << Victor(1, 2) << Victor(3, 4) << Victor(4, 6);
    QTest::newRow("Simple negative")
        << Victor(-1 / 24., -3.245) << Victor(1 / 12., -2)
        << Victor(1 / 24., -5.245);
    QTest::newRow("Bad dimension leave result = first(2d)")
        << Victor(0.5, 0.8) << Victor(1, 1, 4.0) << Victor(0.5, 0.8);
    QTest::newRow("Bad dimension leave result = first(3d)")
        << Victor(-1.2, 0.342, 135) << Victor(3, 4) << Victor(-1.2, 0.342, 135);
}

void
TestGeometry::addition(void)
{
    // Data
    QFETCH(Victor, first);
    QFETCH(Victor, second);
    QFETCH(Victor, result);

    // Classic operator
    Victor test_victor = first + second;
    QCOMPARE(test_victor[0], result[0]);
    QCOMPARE(test_victor[1], result[1]);

    // Assignment operation
    first += second;
    QCOMPARE(first[0], result[0]);
    QCOMPARE(first[1], result[1]);
}

void
TestGeometry::substraction_data(void)
{
    QTest::addColumn<Victor>("first");
    QTest::addColumn<Victor>("second");
    QTest::addColumn<Victor>("result");

    QTest::newRow("Simple positive")
        << Victor(1, 2) << Victor(3, 4) << Victor(-2, -2);
    QTest::newRow("Simple negative")
        << Victor(-1 / 24., -3.245) << Victor(1 / 12., -4)
        << Victor(-3 / 24., 0.755);
    QTest::newRow("Bad dimension leave result = first(2d)")
        << Victor(0.5, 0.8) << Victor(1, 1, 4.0) << Victor(0.5, 0.8);
    QTest::newRow("Bad dimension leave result = first(3d)")
        << Victor(-1.2, 0.342, 135) << Victor(3, 4) << Victor(-1.2, 0.342, 135);
}

void
TestGeometry::substraction(void)
{
    // Data
    QFETCH(Victor, first);
    QFETCH(Victor, second);
    QFETCH(Victor, result);

    // Classic operator
    Victor test_victor = first - second;
    QCOMPARE(test_victor[0], result[0]);
    QCOMPARE(test_victor[1], result[1]);

    // Assignment operation
    first -= second;
    QCOMPARE(first[0], result[0]);
    QCOMPARE(first[1], result[1]);
}

void
TestGeometry::multiplication_data(void)
{
    QTest::addColumn<float>("coef");
    QTest::addColumn<Victor>("second");
    QTest::addColumn<Victor>("result");

    QTest::newRow("Simple positive") << 1.2 << Victor(3, 4) << Victor(3.6, 4.8);
    QTest::newRow("Fraction and negative")
        << -1 / 7. << Victor(1 / 12., -49.) << Victor(-1 / 84., 7);
    QTest::newRow("Try 0") << 0 << Victor(1, 1) << Victor(0, 0);
}

void
TestGeometry::multiplication(void)
{
    // Data
    QFETCH(float, coef);
    QFETCH(Victor, second);
    QFETCH(Victor, result);

    // Classic operator
    Victor test_victor = coef * second;
    QCOMPARE(test_victor[0], result[0]);
    QCOMPARE(test_victor[1], result[1]);

    // Assignment operation
    second *= coef;
    QCOMPARE(second[0], result[0]);
    QCOMPARE(second[1], result[1]);
}

void
TestGeometry::division_data(void)
{
    QTest::addColumn<float>("coef");
    QTest::addColumn<Victor>("second");
    QTest::addColumn<Victor>("result");

    QTest::newRow("Simple positive") << 1.2 << Victor(3.6, 4.8) << Victor(3, 4);
    QTest::newRow("Fraction and negative")
        << -1 / 7. << Victor(-1 / 84., 7.) << Victor(1 / 12., -49.);
}

void
TestGeometry::division(void)
{
    // Data
    QFETCH(float, coef);
    QFETCH(Victor, second);
    QFETCH(Victor, result);

    // Assignment operation
    second /= coef;
    QCOMPARE(second[0], result[0]);
    QCOMPARE(second[1], result[1]);
}

void
TestGeometry::is_2d()
{
    // Data
    Victor victor_3d(1., 2., 3.);
    Victor victor_2d(1., 2.);

    // Test
    QCOMPARE(victor_2d.is_2d(), true);
    QCOMPARE(victor_3d.is_2d(), false);
}

void
TestGeometry::p_norm_data(void)
{
    QTest::addColumn<Victor>("test_victor");
    QTest::addColumn<int>("p");
    QTest::addColumn<float>("result");

    QTest::newRow("2-norm of non null vector")
        << Victor(2.3, -1.0) << 2
        << std::pow(std::pow(2.3, 2) + std::pow(-1.0, 2), 0.5);
    QTest::newRow("3-norm of non null vector")
        << Victor(2.3, -1.0) << 3
        << std::pow(std::pow(2.3, 3) + std::pow(1.0, 3), 1 / 3.);
    QTest::newRow("2-norm of null vector") << Victor(0.0, 0.0) << 2 << 0.0;
}

void
TestGeometry::p_norm(void)
{
    // Data
    QFETCH(Victor, test_victor);
    QFETCH(int, p);
    QFETCH(float, result);

    // Test
    QCOMPARE(test_victor.p_norm(p), result);
}

void
TestGeometry::p_normalize_data()
{
    QTest::addColumn<Victor>("test_victor");
    QTest::addColumn<int>("p");
    QTest::addColumn<Victor>("result");

    QTest::newRow("2-normalize a vector")
        << Victor(1, -1.0) << 2
        << Victor(std::sqrt(2) / 2.0, -std::sqrt(2) / 2.0);
    QTest::newRow("3-normalize a vector")
        << Victor(1, -1.0) << 3
        << Victor(1 / std::pow(2, 1 / 3.0), -1 / std::pow(2, 1 / 3.0));
    QTest::newRow("2-normalize the null vector leaves 0")
        << Victor(0.0, 0.0) << 2 << Victor(0.0, 0.0);
}

void
TestGeometry::p_normalize(void)
{
    // Data
    QFETCH(Victor, test_victor);
    QFETCH(int, p);
    QFETCH(Victor, result);

    Victor normed = test_victor;
    normed.p_normalize(p);

    // Test
    QCOMPARE(normed[0], result[0]);
    QCOMPARE(normed[1], result[1]);
}

void
TestGeometry::zero()
{
    // Data
    float coord1 = 1;
    float coord2 = 3;
    Victor test_victor(coord1, coord2);

    test_victor.zero();

    // Test - Fuzzy compare has issues with comparing to 0 so there's an offset
    QCOMPARE(test_victor[0] + 125.34, 125.34);
    QCOMPARE(test_victor[1] + 125.34, 125.34);
}

QTEST_MAIN(TestGeometry)
#include "test_geometry.moc"
