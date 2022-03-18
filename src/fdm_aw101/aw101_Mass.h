/****************************************************************************//*
 * Copyright (C) 2021 Marek M. Cel
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 ******************************************************************************/
#ifndef AW101_MASS_H
#define AW101_MASS_H

////////////////////////////////////////////////////////////////////////////////

#include <fdm/fdm_Mass.h>

////////////////////////////////////////////////////////////////////////////////

namespace fdm
{

class AW101_Aircraft;   // aircraft class forward declaration

/**
 * @brief AW101 mass class.
 */
class AW101_Mass : public Mass
{
public:

    /** Constructor. */
    AW101_Mass( const AW101_Aircraft *aircraft, Input *input );

    /** Destructor. */
    virtual ~AW101_Mass();

private:

    const AW101_Aircraft *_aircraft;    ///< aircraft model main object
};

} // end of fdm namespace

////////////////////////////////////////////////////////////////////////////////

#endif // AW101_MASS_H
