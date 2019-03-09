/***************************************************************************//**
 * @file    vec4d.h
 * @brief   module defining a structure vec4d_t and utility functions for it
 * @author  Bazso Akos
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
#pragma once
#ifndef VEC_4D__H
#define VEC_4D__H

/******************************************************************************/

/*!
 * @brief type definition for a 4-dimensional vector
 * @details used for regularized parametric coordinates in Kustaanheimo-Stiefel
 * regularization, complex extension of 3D cartesian coordinates;
 * using \a abs to store absolute value of vector
 */
typedef struct
{
    double u1;  ///< u1 component
    double u2;  ///< u2 component
    double u3;  ///< u3 component
    double u4;  ///< u4 component
    double abs; ///< absolute value as Euclidean norm
} vec4d_t;

/******************************************************************************/

/*** function declarations ***/

/*!
 * @brief calculate the absolute value of a vector
 * @verbatim |v| = (<v|v>)^1/2 @endverbatim
 * @param[in] v pointer to the vector of type #vec4d_t
 * @return absolute value (Euclidean norm) as scalar
 */
double vec4d_abs(const vec4d_t* const v);


/*!
 * @brief calculate the bilinear product of two vectors
 * @verbatim prod = (v,w) @endverbatim
 * @param[in] v pointer to first source vector of type #vec4d_t
 * @param[in] w pointer to second source vector of type #vec4d_t
 * @return bilinear product as scalar value
 */
double vec4d_bilinear(
    const vec4d_t* const v,
    const vec4d_t* const w
);


/*!
 * @brief calculate the inner (scalar) product of two vectors
 * @verbatim prod = <v|w> @endverbatim
 * @param[in] v pointer to first source vector of type #vec4d_t
 * @param[in] w pointer to second source vector of type #vec4d_t
 * @return inner product as scalar value
 */
double vec4d_inner(
    const vec4d_t* const v,
    const vec4d_t* const w
);

/******************************************************************************/

#endif  /* VEC_4D__H */
