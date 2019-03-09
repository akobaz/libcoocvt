/***************************************************************************//**
 * @file    const.h
 * @brief   module providing global constants for Coordinate Conversion Library
 * @details constant definitions for strict C99 and MSVC mode
 * @author  Bazso Akos
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
#pragma once
#ifndef COO_CONST__H
#define COO_CONST__H

/******************************************************************************/

/*** export global constants ***/

/* check for definition of "pi" */
/*!
 * @brief value of pi
 */
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


/*!
 * @brief value of 2*pi
 */
extern const double M_2PI;


/*!
 * @brief value of pi^2
 */
extern const double M_PISQ;


/*!
 * @brief convert from degrees to radians
 * @details pi / 180
 */
extern const double deg2rad;


/*!
 * @brief convert from radians to degrees
 * @details 180 / pi
 */
extern const double rad2deg;


/*!
 * @brief Gaussian gravitational constant k
 */
extern const double gaussk;


/*!
 * @brief Gaussian gravitational constant squared: k^2
 */
extern const double gaussk2;

/******************************************************************************/

#endif  /* COO_CONST__H */
