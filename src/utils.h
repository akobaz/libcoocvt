/***************************************************************************//**
 * @file   utils.h
 * @brief  utility functions for other libcoocvt modules
 * @author Bazso Akos
 ******************************************************************************/
#pragma once
#ifndef COO_UTILS__H
#define COO_UTILS__H

/******************************************************************************/

/*** include pre-requisite headers ***/

/* include module header */
#include "vec3d.h"
#include "vec4d.h"
#include "types.h"

/******************************************************************************/

/*!
 * @brief export constants for zero-initialization
 */
extern const vec3d_t v3d_zero;
extern const vec4d_t v4d_zero;
extern const bco_t   bco_zero;
extern const del_t   del_zero;
extern const hco_t   hco_zero;
extern const hel_t   hel_zero;
extern const jco_t   jco_zero;
extern const pco_t   pco_zero;
extern const rco_t   rco_zero;

/******************************************************************************/

/*** function declarations ***/

#ifdef __cplusplus
extern "C" {
#endif

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


/*!
 * @brief return sum of masses
 * @details compensated summation version of function coo_total_mass()
 * @param[in] obj array of objects of type #body_t
 * @param[in] fromIdx lowest index in array \a obj
 * @param[in] uptoIdx highest index in array \a obj
 * @return total mass (>0), or 0 (if uptoIdx < fromIdx)
 */
double coo_total_mass_cs(
    const body_t   obj[],
    const uint32_t fromIdx,
    const uint32_t uptoIdx
);

#ifdef __cplusplus
}
#endif

/******************************************************************************/

#endif  /* COO_UTILS__H */
