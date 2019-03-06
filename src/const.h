/***************************************************************************//**
 * @file    const.h
 * @brief   module providing global constants for libcoocvt library
 * @details constant definitions for strict C99 and MSVC mode
 * @author  Bazso Akos
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
