/***************************************************************************//**
 * @file    coocvt.h
 * @brief   main module for coordinate conversions
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
#ifndef COO_CVT__H
#define COO_CVT__H

/******************************************************************************/

/*** include header files for coordinate conversion modules ***/

/* Barycentric Cartesian Coordinates ... */
#include "bco2hco/bco2hco.h"

/* Delaunay Heliocentric Elements ... */

/* Heliocentric Cartesian Coordinates ... */
#include "hco2bco/hco2bco.h"
#include "hco2hel/hco2hel.h"

/* Heliocentric Keplerian Elements ... */
#include "hel2hco/hel2hco.h"

/* Jacobi Canonical Relative Coordinates ... */

/* Poincare Canonical Relative Coordinates ... */

/* Regularized Heliocentric Parametric Coordinates ... */

/******************************************************************************/

/*** declare data structures ***/

/*!
 * @brief define a list of possible coordinate conversion modes
 * @details use these codes as arguments to coocvt()
 */
typedef enum
{
    /* no conversion */
    CVT_NONE = 0,

    /* alphabetical list of conversion modes */
    CVT_BCO2HCO, // barycentric coord.  to heliocentric coord.
    CVT_HCO2BCO, // heliocentric coord. to barycentric coord.
    CVT_HCO2HEL, // heliocentric coord. to heliocentric elem.
    CVT_HEL2HCO, // heliocentric elem.  to heliocentric coord.

    /* total number of available modes */
    CVT_TOTAL_NUMBER
} CVT_MODE_e;

/******************************************************************************/

#endif  /* COO_CVT__H */
