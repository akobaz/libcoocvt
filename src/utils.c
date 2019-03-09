/*******************************************************************************
 * @file    utils.c
 * @brief   utility functions for other Coordinate Conversion Library modules
 * @author  Bazso Akos
 * @version 1.0, 02 Feb 2012
 *          1.1, 08 Feb 2012
 *          1.2, 19 Aug 2012
 *          1.3, 18 Oct 2016
 *          1.4, 11 Nov 2016
 *          1.5, 09 Mar 2019
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
#include "utils.h"

/******************************************************************************/

/*** pre-processor definitions ***/

/* show verbose debugging output ? 0 = no (default), 1 = yes */
#define COO_UTILS_DEBUG 0
#if COO_UTILS_DEBUG
    #include <stdio.h>
#endif

/******************************************************************************/

/***
 * global constants
 * zero vectors of different types for initialisation of variables
 ***/

/* vector types */
const vec3d_t v3d_zero = {0.0, 0.0, 0.0, 0.0};
const vec4d_t v4d_zero = {0.0, 0.0, 0.0, 0.0, 0.0};

/* cartesian coordinate types */
const bco_t   bco_zero = {{0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0}};
const hco_t   hco_zero = {{0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0}};
const jco_t   jco_zero = {{0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0}};
const pco_t   pco_zero = {{0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0}};

/* parametric coordinate type */
const rco_t   rco_zero = {{0.0, 0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0, 0.0}};

/* orbital element types */
const del_t   del_zero = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
const hel_t   hel_zero = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

/******************************************************************************/

/*******************************************************************************
 *  FUNCTION    : coo_total_mass
 *  DESCRIPTION : return sum of masses for objects fromIdx through uptoIdx
 *  INPUT       : - pointer to array "obj" of type body_t
 *                - starting index "fromIdx"
 *                - final index "uptoIdx"
 *  OUTPUT      : sum of values between "fromIdx" and "uptoIdx" - 1
 ******************************************************************************/
inline double coo_total_mass(
    const body_t   obj[],
    const uint32_t fromIdx,
    const uint32_t uptoIdx
    )
{
    double mtot = 0.0;
    for (register uint32_t idx = fromIdx; idx < uptoIdx; idx++)
    {
        mtot += obj[idx].mass;
    } // end for
    return( mtot );
} // end coo_total_mass

/******************************************************************************/

/*******************************************************************************
 *  FUNCTION    : coo_total_mass_cs
 *  DESCRIPTION : compensated summation version of function coo_total_mass()
 *  INPUT       : - pointer to array "obj" of type body_t
 *                - starting index "fromIdx"
 *                - final index "uptoIdx"
 *  OUTPUT      : sum of values between "fromIdx" and "uptoIdx" - 1
 ******************************************************************************/
inline double coo_total_mass_cs(
    const body_t   obj[],
    const uint32_t fromIdx,
    const uint32_t uptoIdx
    )
{
    /* NOTE 'volatile' avoids optimization of this variable (?) */
    volatile double errm;
    double newm, oldm, incm;

    errm = newm = oldm = 0.0;
    for (register uint32_t idx = fromIdx; idx < uptoIdx; idx++)
    {
        incm = errm + obj[idx].mass;    // mass increment
        newm = oldm + incm;             // new total mass
        /***
         * TODO leave this statement exactly as it is !!!
         * NOTE don't use gcc -funsafe optimizations
         ***/
        errm = (oldm - newm) + incm;    // update error variable
        oldm = newm;
    } // end for
    return( newm );
} // end coo_total_mass_cs

/******************************************************************************/

/* helper function for barycentric coordinates */
static inline void getBarycenter_BCO(
    body_t         src[],
    hco_t*         bc,
    const uint32_t fromIdx,
    const uint32_t uptoIdx
    )
{
    /* sum up mass-weighted positions & velocities */
    for (register uint32_t i = fromIdx; i < uptoIdx; i++)
    {
        // bc = bc + src[i] * mass[i]
        vec3d_madd(&bc->pos, &bc->pos, &src[i].bco.pos, src[i].mass);
        vec3d_madd(&bc->vel, &bc->vel, &src[i].bco.vel, src[i].mass);
    } // end for
} // end getBarycenter_BCO

/******************************************************************************/

/* helper function for heliocentric coordinates */
static inline void getBarycenter_HCO(
    body_t         src[],
    hco_t*         bc,
    const uint32_t fromIdx,
    const uint32_t uptoIdx
    )
{
    /* sum up mass-weighted positions & velocities */
    for (register uint32_t i = fromIdx; i < uptoIdx; i++)
    {
        // bc = bc + src[i] * mass[i]
        vec3d_madd(&bc->pos, &bc->pos, &src[i].hco.pos, src[i].mass);
        vec3d_madd(&bc->vel, &bc->vel, &src[i].hco.vel, src[i].mass);
    } // end for
} // end getBarycenter_HCO

/******************************************************************************/

/* helper function for Jacobi coordinates */
static inline void getBarycenter_JCO(
    body_t         src[],
    hco_t*         bc,
    const uint32_t fromIdx,
    const uint32_t uptoIdx
    )
{
    /* sum up mass-weighted positions & velocities */
    for (register uint32_t i = fromIdx; i < uptoIdx; i++)
    {
        // bc = bc + src[i] * mass[i]
        vec3d_madd(&bc->pos, &bc->pos, &src[i].jco.pos, src[i].mass);
        vec3d_madd(&bc->vel, &bc->vel, &src[i].jco.vel, src[i].mass);
    } // end for
} // end getBarycenter_JCO

/******************************************************************************/

/* helper function for Poincare coordinates */
static inline void getBarycenter_PCO(
    body_t         src[],
    hco_t*         bc,
    const uint32_t fromIdx,
    const uint32_t uptoIdx
    )
{
    /* sum up mass-weighted positions & velocities */
    for (register uint32_t i = fromIdx; i < uptoIdx; i++)
    {
        // bc = bc + src[i] * mass[i]
        vec3d_madd(&bc->pos, &bc->pos, &src[i].pco.pos, src[i].mass);
        vec3d_madd(&bc->vel, &bc->vel, &src[i].pco.vel, src[i].mass);
    } // end for
} // end getBarycenter_PCO

/******************************************************************************/

/*******************************************************************************
 *  FUNCTION    : getBarycenter
 *  DESCRIPTION : determine barycenter position and velocity
 *  INPUT       : - pointer to array of type hco_t for source coordinates "src"
 *                - pointer of type hco_t to barycenter coordinates "bc"
 *                - pointer to array "mass"
 *                - starting index "fromIdx"
 *                - final index "uptoIdx"
 *                - coordinate "type" from enum COO_TYPE_e
 *  OUTPUT      : 0 for success, 1 for error
 ******************************************************************************/
int coo_get_barycenter(
    hco_t*           bc,
    body_t           src[],
    const uint32_t   fromIdx,
    const uint32_t   uptoIdx,
    const COO_TYPE_e type
    )
{
    /* check input for invalid pointers */
    if ( (bc == nullptr) || (src == nullptr) )
    {
        /* TODO print error message */
        return 1;
    } // end if

    /* check array indices */
    if ( fromIdx > uptoIdx )
    {
        /* TODO print error message */
        return 1;
    } // end if

    /* reset all barycenter components to zero */
    *bc = hco_zero;

    /* select which type of coordinates */
    switch ( type )
    {
        /* barycentric coordinates */
        case COO_BCO:
            getBarycenter_BCO( src, bc, fromIdx, uptoIdx );
            break;

        /* heliocentric coordinates */
        case COO_HCO:
            getBarycenter_HCO( src, bc, fromIdx, uptoIdx );
            break;

        /* Jacobi coordinates */
        case COO_JCO:
            getBarycenter_JCO( src, bc, fromIdx, uptoIdx );
            break;

        /* Poincare coordinates */
        case COO_PCO:
            getBarycenter_PCO( src, bc, fromIdx, uptoIdx );
            break;

        /* TODO FIXME implement barycenter for case COO_RCO */

        /* invalid case */
        case COO_NONE:
        default:
            /* TODO print error message */
            return 1;
    } // end switch

    /* inverse of total mass */
    const double mtot = 1.0 / coo_total_mass_cs( src, fromIdx, uptoIdx );

    /* scale with total mass of system:
     * bc = bc * mtot
     */
    vec3d_smul( &bc->pos, &bc->pos, mtot ); // position vector component
    vec3d_smul( &bc->vel, &bc->vel, mtot ); // velocity vector component

    return 0;
} // end coo_get_barycenter

/******************************************************************************/

/*******************************************************************************
 *  FUNCTION    : coo_recenter
 *  DESCRIPTION : translate source coordinates "src" (positions and velocities)
 *                to new coordinate center "cen";
 *                effectively a wrapper function for vec3d_sub()
 *  INPUT       : - pointer "dest" to new coordinates of type hco_t
 *                - pointer "src" to old coordinates of type hco_t
 *                - pointer "cen" to input center coordinates of type hco_t
 *  OUTPUT      : none
 ******************************************************************************/
inline void coo_recenter(
    hco_t*             dest,
    const hco_t* const src,
    const hco_t* const cen
    )
{
    /* dest = src - cen */
    vec3d_sub( &dest->pos, &src->pos, &cen->pos ); // position component
    vec3d_sub( &dest->vel, &src->vel, &cen->vel ); // velocity component
} // end coo_recenter

/******************************************************************************/
