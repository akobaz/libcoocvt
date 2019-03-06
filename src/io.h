/***************************************************************************//**
 * @file   io.h
 * @brief  module for input and output of coordinate and element structures
 * @author Bazso Akos
 ******************************************************************************/
#pragma once
#ifndef COO_IO__H
#define COO_IO__H

/******************************************************************************/

/*** include prerequisite headers ***/

/* include standard headers */
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

/* include module header */
#include "types.h"

/******************************************************************************/

/*** function declarations ***/

#ifdef __cplusplus
extern "C" {
#endif

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

#ifdef __cplusplus
}
#endif

/******************************************************************************/

#endif  /* COO_IO__H */
