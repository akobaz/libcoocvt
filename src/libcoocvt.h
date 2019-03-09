/***************************************************************************//**
 * @file    libcoocvt.h
 * @brief   main header and API definition for Coordinate Conversion Library
 * @author  Bazso Akos
 * @version 2019.03
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
#ifndef LIBCOOCVT__H
#define LIBCOOCVT__H

/******************************************************************************/

/*** include prerequisite standard headers ***/

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

/******************************************************************************/

/*** declare data structures ***/

/*!
 * @brief type definition for a 3-dimensional vector
 * @details using \a abs for padding to size of 4x double,
 * also using \a abs to store absolute value of vector
 */
typedef struct
{
    double x;   ///< x component
    double y;   ///< y component
    double z;   ///< z component
    double abs; ///< absolute value as Euclidean norm
} vec3d_t;


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


/*!
 * @brief type definition for Heliocentric Cartesian Coordinates (HCO)
 * @details compound structure for 3-dimensional position vector \a pos and
 * 3-dimensional velocity vector \a vel of type #vec3d_t
 */
typedef struct
{
    vec3d_t pos; ///< position
    vec3d_t vel; ///< velocity
} hco_t;


/*!
 * @brief type definition for Barycentric Cartesian Coordinates (BCO)
 * @note same as #hco_t
 */
typedef hco_t bco_t;


/*!
 * @brief type definition for Jacobi canonical Cartesian Coordinates (JCO)
 * @note same as #hco_t
 */
typedef hco_t jco_t;


/*!
 * @brief type definition for Poincare canonical Cartesian Coordinates (PCO)
 * @note same as #hco_t
 */
typedef hco_t pco_t;


/*!
 * @brief type definition for Heliocentric regularized parametric coordinates (RCO)
 * @details compound structure for 4-dimensional position vector \a pos and
 * 4-dimensional velocity vector \a vel of type #vec4d_t
 */
typedef struct
{
    vec4d_t pos; ///< position
    vec4d_t vel; ///< velocity
} rco_t;


/*!
 * @brief type definition for Heliocentric Keplerian orbital elements (HEL)
 * @note only for elliptic motion (0 < ecc < 1);
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
 * @brief type definition for Heliocentric (elliptic) Delaunay elements (DEL)
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

/*** function declarations ***/

#ifdef __cplusplus
extern "C" {
#endif

/*** main conversion function ***/

/*!
 * @brief main coordinate conversion function
 * @details convert in-place in array \a obj using conversion \a mode
 * @param[in,out] obj pointer to array of coordinate structures of type #body_t
 * @param[in] dim dimension of array \a obj
 * @param[in] center index of central body
 * @param[in] mode specify type of conversion, see enum #CVT_MODE_e
 * @return 0 for success, 1 for error
 */
int coocvt(
    body_t         obj[],
    const uint32_t dim,
    const uint32_t center,
    CVT_MODE_e     mode
);

/*** input / output functions ***/

/*!
 * @brief read Cartesian coordinates from file into array
 * @param[in] fp pointer to FILE object for reading input
 * @param[out] obj array of type #body_t to store coordinates
 * @param[in] dim dimension of array \a obj, read at most this number of entries
 * @param[in] type chosen type of input coordinates, see enum #COO_TYPE_e
 * @return 0 on error, number of entries read on success (> 0)
 */
int coo_read_COO(
    FILE*            fp,
    body_t           obj[],
    const uint32_t   dim,
    const COO_TYPE_e type
);


/*!
 * @brief read Delaunay elements from file into array
 * @param[in] fp pointer to FILE object for reading input
 * @param[out] obj array of type #body_t to store Delaunay elements
 * @param[in] dim dimension of array \a obj, read at most this number of entries
 * @param[in] use_deg Boolean flag to indicate whether input angles are
 * in degrees (set \a use_deg = true) and need to be converted to radians,
 * or angles are already in radians (set \a use_deg = false)
 * @return 0 on error, number of entries read on success (> 0)
 */
int coo_read_DEL(
    FILE*          fp,
    body_t         obj[],
    const uint32_t dim,
    const bool     use_deg
);


/*!
 * @brief read heliocentric orbital elements from file into array
 * @param[in] fp pointer to FILE object for reading input
 * @param[out] obj array of type #body_t to store Kepler elements
 * @param[in] dim dimension of array \a obj, read at most this number of entries
 * @param[in] use_deg Boolean flag to indicate whether input angles are
 * in degrees (set \a use_deg = true) and need to be converted to radians,
 * or angles are already in radians (set \a use_deg = false)
 * @return 0 on error, number of entries read on success (> 0)
 */
int coo_read_HEL(
    FILE*          fp,
    body_t         obj[],
    const uint32_t dim,
    const bool     use_deg
);


/*!
 * @brief read regularized parametric coordinates from file into array
 * @param[in] fp pointer to FILE object for reading input
 * @param[out] obj array of type #body_t to store coordinates
 * @param[in] dim dimension of array \a obj, read at most this number of entries
 * @return 0 on error, number of entries read on success (> 0)
 */
int coo_read_RCO(
    FILE*          fp,
    body_t         obj[],
    const uint32_t dim
);


/*!
 * @brief print Cartesian coordinates from array to file object
 * @param[in] fp pointer to FILE object for writing output
 * @param[in] obj array of type #body_t
 * @param[in] dim dimension of array \a obj, write at most this number of entries
 * @param[in] type chosen type of output coordinates, see enum #COO_TYPE_e
 * @return 0 on error, 1 on success
 */
int coo_show_COO(
    FILE*            fp,
    const body_t     obj[],
    const uint32_t   dim,
    const COO_TYPE_e type
);


/*!
 * @brief print Delaunay elements from array to file object
 * @param[in] fp pointer to FILE object for writing output
 * @param[in] obj array of type #body_t
 * @param[in] dim dimension of array \a obj, write at most this number of entries
 * @param[in] use_deg Boolean flag that indicates whether to output angles
 * in degrees (set \a use_deg = true), or in radians (set \a use_deg = false)
 * @return 0 on error, 1 on success
 */
int coo_show_DEL(
    FILE*          fp,
    const body_t   obj[],
    const uint32_t dim,
    const bool     use_deg
);


/*!
 * @brief print heliocentric orbital elements from array to file object
 * @param[in] fp pointer to FILE object for writing output
 * @param[in] obj array of type #body_t
 * @param[in] dim dimension of array \a obj, write at most this number of entries
 * @param[in] use_deg Boolean flag that indicates whether to output angles
 * in degrees (set \a use_deg = true), or in radians (set \a use_deg = false)
 * @return 0 on error, 1 on success
 */
int coo_show_HEL(
    FILE*          fp,
    const body_t   obj[],
    const uint32_t dim,
    const bool     use_deg
);


/*!
 * @brief print regularized parametric coordinates from array to file object
 * @param[in] fp pointer to FILE object for writing output
 * @param[in] obj array of type #body_t
 * @param[in] dim dimension of array \a obj, write at most this number of entries
 * @return 0 on error, 1 on success
 */
int coo_show_RCO(
    FILE*          fp,
    const body_t   obj[],
    const uint32_t dim
);

/*** utility functions ***/

/*!
 * @brief determine barycenter (center of mass) position & velocity
 * @details barycenter for objects in range [fromIdx : uptoIdx-1]
 * @param[out] bc coordinates for center of mass (barycenter)
 * @param[in] obj input array of type #body_t
 * @param[in] fromIdx lowest index in array \a obj
 * @param[in] uptoIdx highest index in array \a obj
 * @param[in] type coordinate type from enum #COO_TYPE_e
 * @return 0 for success, 1 for error
 */
int coo_get_barycenter(
    hco_t*           bc,
    body_t           obj[],
    const uint32_t   fromIdx,
    const uint32_t   uptoIdx,
    const COO_TYPE_e type
);


/*!
 * @brief shift coordinates relative to new center
 * @details translates source coordinates to new coordinate center via
 * dest = src - cen
 * @param[out] dest pointer to new coordinates of type #hco_t
 * @param[in] src pointer to original coordinates of type #hco_t
 * @param[in] cen pointer to center coordinates of type #hco_t
 * @return none
 */
void coo_recenter(
    hco_t*             dest,
    const hco_t* const src,
    const hco_t* const cen
);


/*!
 * @brief return sum of masses
 * @details adding up masses for objects in range [fromIdx : uptoIdx-1]
 * @param[in] obj array of objects of type #body_t
 * @param[in] fromIdx lowest index in array \a obj
 * @param[in] uptoIdx highest index in array \a obj
 * @return total mass (>0), or 0 (if uptoIdx < fromIdx)
 */
double coo_total_mass(
    const body_t   obj[],
    const uint32_t fromIdx,
    const uint32_t uptoIdx
);

/*** version information functions ***/

/*!
 * @brief print the library's version number to stdout
 * @return none
 */
void coo_show_version(void);


/*!
 * @brief query the current major version
 * @return major version as integer
 */
int coo_get_major_version(void);


/*!
 * @brief query the current minor version
 * @return minor version as integer
 */
int coo_get_minor_version(void);

#ifdef __cplusplus
}
#endif

/******************************************************************************/

#endif  /* LIBCOOCVT__H */
