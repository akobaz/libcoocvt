/***************************************************************************//**
 * @file    types.h
 * @brief   header file for definitions of coordinate types and structures
 * @author  Bazso Akos
 * @version 1.3, 06 Mar 2019
 *
 * @cond
 * VERSION HISTORY:
 * 1.2, 19 Oct 2016
 * 1.1, 19 Aug 2012
 * 1.0, 07 Feb 2012
 * @endcond
 ******************************************************************************/
#pragma once
#ifndef COO_TYPES__H
#define COO_TYPES__H

/******************************************************************************/

/*** include prerequisite headers ***/

/* include standard headers */
#include <stdint.h>

/* include module headers */
#include "vec3d.h"
#include "vec4d.h"

/******************************************************************************/

/*** define pre-processor constants ***/

/* declare new C++ 2011-like "keyword" for NULL pointer */
#define nullptr ((void*)0)

/******************************************************************************/

/*** define data structures ***/

/*!
 * @brief Heliocentric Cartesian Coordinates (HCO)
 */
typedef struct
{
    vec3d_t pos; ///< position
    vec3d_t vel; ///< velocity
} hco_t;


/*!
 * @brief Barycentric Cartesian Coordinates (BCO)
 * @note same as #hco_t
 */
typedef hco_t bco_t;


/*!
 * @brief Jacobi canonical relative Cartesian Coordinates (JCO)
 * @note same as #hco_t
 */
typedef hco_t jco_t;


/*!
 * @brief Poincare relative canonical Cartesian Coordinates (PCO)
 * @note same as #hco_t
 */
typedef hco_t pco_t;


/*!
 * @brief Heliocentric regularized parametric coordinates (RCO)
 */
typedef struct
{
    vec4d_t pos; ///< position
    vec4d_t vel; ///< velocity
} rco_t;


/*!
 * @brief Heliocentric Keplerian orbital elements (HEL)
 * @details only for elliptic motion (0 < ecc < 1)
 */
typedef struct
{
    double sma; ///< semi-major axis
    double ecc; ///< eccentricity
    double inc; ///< inclination
    double aph; ///< argument of perihelion
    double lan; ///< longitude of ascending node
    double man; ///< mean anomaly
} hel_t;


/*!
 * @brief Heliocentric (elliptic) Delaunay elements (DEL)
 * @details canonical action-angle elements
 */
typedef struct
{
    double L; ///< L = [G (M+m) a]^(1/2)
    double G; ///< G = L (1 - e^2)^(1/2)
    double H; ///< H = G cos(i)
    double l; ///< l = mean anomaly
    double g; ///< g = argument of perihelion
    double h; ///< h = longitude of ascending node
} del_t;


/*!
 * @brief collection of coordinates for a single object
 * @details using \a hel as generic elements for any kind of Cartesian coord.
 */
typedef struct
{
    /* Cartesian coordinates */
    bco_t  bco;  ///< barycentric (center of mass) coordinates
    hco_t  hco;  ///< heliocentric coordinates
    jco_t  jco;  ///< Jacobi coordinates
    pco_t  pco;  ///< Poincare coordinates
    rco_t  rco;  ///< regularized coordinates

    /* Orbital elements */
    del_t  del;  ///< Delaunay elements
    hel_t  hel;  ///< Keplerian elements

    double mass; ///< mass in units of solar mass

    /* TODO add flag(s) to track used coordinate types ??? */
} body_t;


/*!
 * @brief enumeration of different coordinate types
 * @details for use with uint8_t as flags for different bits
 */
typedef enum
{
    COO_NONE = 0,  ///< invalid type

    COO_BCO  = 1,  ///< Barycentric coordinates
    COO_HCO  = 2,  ///< Heliocentric coordinates
    COO_JCO  = 4,  ///< Jacobi canonical coordinates
    COO_PCO  = 8,  ///< Poincare canonical coordinates
    COO_RCO  = 16, ///< regularized parametric coordinates

    COO_DEL  = 32, ///< Delaunay orbital elements
    COO_HEL  = 64, ///< Keplerian orbital elements

    COO_TOTAL,     ///< total number of entries
} COO_TYPE_e;

/******************************************************************************/

#endif  /* COO_TYPES__H */
