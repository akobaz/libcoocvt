/*******************************************************************************
 * @file    const.c
 * @brief   module providing global constants for Coordinate Conversion Library
 * @details constant definitions for strict C99 and MSVC mode
 * @author  Bazso Akos
 * @version 1.0, 19 Oct 2016
 *          1.1, 19 Feb 2019
 *
 * @copyright
 * Copyright (C) 2016-2019 Bazso Akos
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
#include "const.h"

/******************************************************************************/

/*** export global constants ***/

/* two-times-pi: 2*pi */
const double M_2PI   = (M_PI + M_PI);

/* pi-squared: pi^2 */
const double M_PISQ  = (M_PI * M_PI);

/* convert from degrees to radians */
const double deg2rad = M_PI / 180.0;

/* convert from radians to degrees */
const double rad2deg = 180.0 / M_PI;

/******************************************************************************/

/*******************************************************************************
 * Gaussian gravitational constant "k" to full accurracy as given by the
 * IAU 1976 definition,
 * dimensions [k^2] = [AU^3 M_Sun^-1 days^-2] ~ [G] = [m^3 kg^-1 s^-2]
 ******************************************************************************/
const double gaussk  = 0.01720209895;
const double gaussk2 = 2.9591220828559115E-04;

/******************************************************************************/
