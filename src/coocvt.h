/***************************************************************************//**
 * @file    coocvt.h
 * @brief   main module for coordinate conversions
 * @author  Bazso Akos
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
