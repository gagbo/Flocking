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
#include <cmath>

class TestGeometry: public QObject
{
    Q_OBJECT
private slots:
    void access(void);
    void comparison(void);
    
    void pure_assignment(void);
    void addition(void);
    void substraction(void);
    void multiplication(void);
    void division(void);
    
    void is_2d(void);
    void p_norm(void);
    void p_normalize(void);
    void zero(void);
};

void TestGeometry::access(void)
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

void TestGeometry::comparison()
{
    // Data
    Victor first(1.0, 2.3);
    Victor second(3.1234 / 3.1234, 2.300);
    bool expected = true;
    
    // Test
    QCOMPARE(first == second, expected);
    
}

void TestGeometry::pure_assignment()
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


void TestGeometry::addition(void)
{
    // Data
    Victor first(1., 2.);
    Victor second(3., 4.);
    Victor result(4., 6.);
    
    // Classic operator
    Victor test_victor = first + second;
    QCOMPARE(test_victor[0], result[0]);
    QCOMPARE(test_victor[1], result[1]);
    
    // Assignment operation
    first += second;
    QCOMPARE(first[0], result[0]);
    QCOMPARE(first[1], result[1]);
}

void TestGeometry::substraction(void)
{
    // Data
    Victor first(1., 6.);
    Victor second(3., 4.);
    Victor result(-2., 2.);
    
    // Classic operator
    Victor test_victor = first - second;
    QCOMPARE(test_victor[0], result[0]);
    QCOMPARE(test_victor[1], result[1]);
    
    // Assignment operation
    first -= second;
    QCOMPARE(first[0], result[0]);
    QCOMPARE(first[1], result[1]);
}

void TestGeometry::multiplication(void)
{
    // Data
    float coef(1.2);
    Victor second(3., 4.);
    Victor result(3.6, 4.8);
    
    // Classic operator
    Victor test_victor = coef * second;
    QCOMPARE(test_victor[0], result[0]);
    QCOMPARE(test_victor[1], result[1]);
    
    // Assignment operation
    second *= coef;
    QCOMPARE(second[0], result[0]);
    QCOMPARE(second[1], result[1]);
}

void TestGeometry::division(void)
{
    // Data
    float coef(0.75);
    Victor second(3., 4.);
    Victor result(4, 16./3.);
    
    // Assignment operation
    second /= coef;
    QCOMPARE(second[0], result[0]);
    QCOMPARE(second[1], result[1]);
}

void TestGeometry::is_2d()
{
    // Data
    Victor victor_3d(1., 2., 3.);
    Victor victor_2d(1., 2.);
    
    // Test
    QCOMPARE(victor_2d.is_2d(), true);
    QCOMPARE(victor_3d.is_2d(), false);
}

void TestGeometry::p_norm()
{
    // Data
    float coord1 = 2.3;
    float coord2 = -1.0;
    Victor test_victor(coord1, coord2);
    float norm_2 = std::pow(std::pow(coord1, 2) + std::pow(coord2, 2), 0.5);
    float norm_3 = std::pow(std::pow(std::abs(coord1), 3) + std::pow(std::abs(coord2), 3), 1/3.);
    
    // Test
    QCOMPARE(test_victor.p_norm(), norm_2);
    QCOMPARE(test_victor.p_norm(3), norm_3);
    
}

void TestGeometry::p_normalize()
{
    // Data
    float coord1 = 1;
    float coord2 = -1;
    Victor test_victor(coord1, coord2);
    Victor result_2 = Victor(std::sqrt(2)/2.0, -std::sqrt(2)/2.0);
    Victor result_3 = Victor(1/std::pow(2, 1/3.0), -1/std::pow(2, 1/3.0));
    
    Victor normed_2 = test_victor;
    normed_2.p_normalize();
    
    Victor normed_3 = test_victor;
    normed_3.p_normalize(3);
    
    // Test
    QCOMPARE(normed_2[0], result_2[0]);
    QCOMPARE(normed_2[1], result_2[1]);
    QCOMPARE(normed_3[0], result_3[0]);
    QCOMPARE(normed_3[1], result_3[1]);
    
    
}

void TestGeometry::zero()
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
