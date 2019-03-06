/***************************************************************************//**
 * @file   hco2bco.h
 * @brief  convert heliocentric coordinates to barycentric coordinates
 * @author Bazso Akos
 ******************************************************************************/
#pragma once
#ifndef HCO2BCO__H
#define HCO2BCO__H

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
 * @brief convert heliocentric coordinates to barycentric coordinates
 * @param[in,out] obj array of type #body_t
 * @param[in] dim dimension of array \a obj
 * @param[in] center index of central body (for mass parameter GM)
 * @return 0 for success, 1 for error
 */
int hco2bco(
    body_t         obj[],
    const uint32_t dim,
    const uint32_t center
);

#ifdef __cplusplus
}
#endif

/******************************************************************************/

#endif  /* HCO2BCO__H */
