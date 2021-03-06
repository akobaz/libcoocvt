/*******************************************************************************
 * @file    vec4d.c
 * @brief   module defining a structure vec4d_t and utility functions for it
 * @author  Bazso Akos
 * @version 1.0, 03 Feb 2012
 *          1.1, 17 Nov 2013
 *          1.2, 24 Feb 2019
 *
 * @copyright
 * Copyright (C) 2012-2019 Bazso Akos
 *
 * This file is part of libcoocvt.
 *
 * libcoocvt is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * libcoocvt is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libcoocvt.  If not, see <https://www.gnu.org/licenses/>.
 *
 ******************************************************************************/
/* include standard headers */
#include <math.h>

/* include module headers */
#include "vec4d.h"

/******************************************************************************/

/***
 * vec4d_inner
 * inner (scalar) product of two vectors; a & b can be the same vector
 * <a|b> = a.u1*b.u1 + a.u2*b.u2 + a.u3*b.u3 + a.u4*b.u4
 ***/
inline double vec4d_inner(
    const vec4d_t* const a,
    const vec4d_t* const b
    )
{
    return( a->u1 * b->u1 + a->u2 * b->u2 + a->u3 * b->u3 + a->u4 * b->u4 );
} // vec4d_inner

/******************************************************************************/

/***
 * vec4d_abs
 * absolute value of a vector (Euclidean norm)
 * |v| = (<v|v>)^1/2
 ***/
inline double vec4d_abs(const vec4d_t* const v)
{
    //return( sqrt(vec4d_inner(v, v)) );
    return( sqrt(v->u1*v->u1 + v->u2*v->u2 + v->u3*v->u3 + v->u4*v->u4) );
} // end vec4d_abs

/******************************************************************************/

/***
 * vec4d_bilinear
 * bilinear product of two vectors; a & b can be the same vector
 * (a,b) = a.u4 * b.u1 - a.u3 * b.u2 + a.u2 * b.u3 - a.u1 * b.u4
 ***/
inline double vec4d_bilinear(
    const vec4d_t* const a,
    const vec4d_t* const b
    )
{
    return( a->u4 * b->u1 - a->u3 * b->u2 + a->u2 * b->u3 - a->u1 * b->u4 );
} // end vec4d_bilinear

/******************************************************************************/
