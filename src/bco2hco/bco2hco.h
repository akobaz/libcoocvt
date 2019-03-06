/***************************************************************************//**
 * @file   bco2hco.h
 * @brief  convert barycentric coordinates to heliocentric coordinates
 * @author Bazso Akos
 ******************************************************************************/
#pragma once
#ifndef BCO2HCO__H
#define BCO2HCO__H

/******************************************************************************/

/*** include prerequisite headers ***/

/* project headers */
#include "types.h"

/******************************************************************************/

/*** function declarations ***/

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @brief convert barycentric coordinates to heliocentric coordinates
 * @param[in,out] obj array of type #body_t
 * @param[in] dim dimension of array \a obj
 * @param[in] center index of central body (for mass parameter GM)
 * @return 0 for success, 1 for error
 */
int bco2hco(
    body_t         obj[],
    const uint32_t dim,
    const uint32_t center
);

#ifdef __cplusplus
}
#endif

/******************************************************************************/

#endif  /* BCO2HCO__H */
