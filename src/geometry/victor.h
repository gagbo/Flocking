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

#ifndef _GEOMETRY_VICTOR_H_
#define _GEOMETRY_VICTOR_H_

#include <iostream>
#include <vector>

//! A class for geometrical floating-point based vectors and their operations
class Victor
{
  public:
    /////////////// Constructors

    //! Construct a NULL vector of dimension d (default constructor, dim 2)
    Victor(int d = 2);

    //! Construct a 2d Vector from coordinates
    Victor(float x, float y);

    //! Construct a 3d Vector from coordinates
    Victor(float x, float y, float z);

    //! Copy constructor
    Victor(const Victor &other);

    /////////////// Destructor
    //! Flush and clean the std::vector containing coordinates
    ~Victor();

    /////////////// Simple accessors
    //! Return true if the Victor is 2 dimensional
    inline bool
    is_2d(void) const
    {
        return d == 2;
    }

    /////////////// Convenience methods

    //! Return the p-norm distance (default 2) to another Victor
    /*! The method should throw an error if the dimensions are not compatible
     */
    float p_distance(const Victor &other, int p = 2) const;

    //! Return the p-norm distance (default 2) between 2 Victors
    /*! Call the p_distance method under the hood
     */
    inline friend float
    p_distance(const Victor &first, const Victor &second, int p = 2)
    {
        return first.p_distance(second, p);
    }

    //! Return the p-norm (default 2) of the Victor
    float p_norm(int p = 2) const;

    //! Normalize the Victor according to p_norm (default 2)
    inline void
    p_normalize(int p = 2)
    {
        *this /= this->p_norm(p);
    }

    //! Put all values of Victor to 0
    inline void
    zero(void)
    {
        for (int i = 0; i < d; ++i) {
            coord[i] = 0;
        }
    }

    // Operations
    Victor operator+(const Victor &rhs) const;
    Victor operator-(const Victor &rhs) const;
    Victor &operator=(const Victor &rhs);
    float &operator[](int zero_based_coordinate);
    const float &operator[](int zero_based_coordinate) const;
    Victor &operator*=(float coef);
    Victor &operator/=(float coef);
    Victor &operator+=(const Victor &rhs);
    Victor &operator-=(const Victor &rhs);
    friend Victor operator*(float coef, const Victor &rhs);
    friend std::ostream &operator<<(std::ostream &os, const Victor &v);

  protected:
    int d;
    std::vector<float> coord;
};
#endif // _GEOMETRY_VICTOR_H_
