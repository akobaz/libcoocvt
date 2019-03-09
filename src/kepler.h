/***************************************************************************//**
 * @file    kepler.h
 * @brief   find numerical solution for elliptic Kepler Equation
 * @details simplified version based on Kepler Equation Solver Library
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
#ifndef COO_KEPLER__H
#define COO_KEPLER__H

/******************************************************************************/

/*** function declarations ***/

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @brief solver for Kepler Equation
 * @details elliptic case for elliptic eccentric anomaly x
 * \f$ x - e * sin(x) = M \f$
 * @param[in] ecc eccentricity, 0 < ecc < 1
 * @param[in] ma mean anomaly in radians
 * @return eccentric anomaly in radians
 ***/
double coo_kesolver(
    const double ecc,
    const double ma
);


/*!
 * @brief evaluate sin(x), cos(x) simultaneously
 * @details modify return value based on parameter "ecc":
 * if ecc >= 0 return ecc*sin(x), ecc*cos(x);
 * if ecc < 0 return sin(x), cos(x)
 * @param[out] sx pointer for sin(x)
 * @param[out] cx pointer for cos(x)
 * @param[in] x input value (in radians)
 * @param[in] ecc eccentricity
 * @return none
 */
void coo_sincos(
    double*      sx,
    double*      cx,
    const double x,
    const double ecc
);

#ifdef __cplusplus
}
#endif

/******************************************************************************/

#endif  /* COO_KEPLER__H */
