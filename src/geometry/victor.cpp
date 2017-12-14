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

#include <cmath>

Victor::Victor(int dim) : d(dim)
{
    coord.clear();
    for (int i = 0; i < d; ++i) {
        coord.push_back(0.0);
    }
}

Victor::Victor(float x, float y) : d(2)
{
    coord.clear();
    coord.push_back(x);
    coord.push_back(y);
}

Victor::Victor(float x, float y, float z) : d(3)
{
    coord.clear();
    coord.push_back(x);
    coord.push_back(y);
    coord.push_back(z);
}

Victor::Victor(const Victor &other)
{
    d = other.is_2d() ? 2 : 3;
    coord.clear();
    for (int i = 0; i < d; ++i) {
        coord.push_back(other[i]);
    }
}

Victor::~Victor()
{
    coord.clear();
}

float
Victor::p_distance(const Victor &other, int p) const
{
    int dim = d;
    if (d != other.d) {
        std::cerr << "Distance : not compatible dimension -> cropped at d=2\n";
        dim = 2;
    }
    double norm = 0; // double because of the exponentiation

    for (int i = 0; i < d; ++i) {
        norm += std::pow((coord[i] - other[i]), p);
    }

    return std::pow(norm, 1.0 / p);
}

float
Victor::p_norm(int p) const
{
    return p_distance(Victor(d), p);
}

Victor
Victor::operator+(const Victor &rhs) const
{
    Victor result = Victor(*this);
    result += rhs;
    return result;
}

Victor
Victor::operator-(const Victor &rhs) const
{
    Victor result = Victor(*this);
    result -= rhs;
    return result;
}

Victor
Victor::operator=(const Victor &rhs) const
{
    return Victor(rhs);
}

float &Victor::operator[](int zero_based_coordinate)
{
    return coord[zero_based_coordinate];
}

const float &Victor::operator[](int zero_based_coordinate) const
{
    return coord[zero_based_coordinate];
}

void
Victor::operator*=(float coef)
{
    for (int i = 0; i < d; ++i) {
        coord[i] *= coef;
    }
}

void
Victor::operator/=(float coef)
{
    for (int i = 0; i < d; ++i) {
        coord[i] /= coef;
    }
}

void
Victor::operator+=(const Victor &rhs)
{
    if (rhs.d != d) {
        std::cerr << "Victor addition : not compatible dimensions -> unchanged "
                     "Victor\n";
        return;
    }
    for (int i = 0; i < d; ++i) {
        coord[i] += rhs[i];
    }
    return;
}

void
Victor::operator-=(const Victor &rhs)
{
    if (rhs.d != d) {
        std::cerr << "Victor addition : not compatible dimensions -> unchanged "
                     "Victor\n";
        return;
    }
    for (int i = 0; i < d; ++i) {
        coord[i] -= rhs[i];
    }
    return;
}

Victor operator*(float coef, const Victor &rhs)
{
    Victor result = Victor(rhs);
    result *= coef;
    return result;
}

std::ostream &
operator<<(std::ostream &os, const Victor &v)
{
    for (int i = 0; i < v.d - 1; ++i) {
        os << v[i] << "\t";
    }
    os << v[v.d - 1];
    return os;
}
