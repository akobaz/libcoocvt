/***************************************************************************//**
 * @file   hco2hel.h
 * @brief  convert heliocentric coordinates to heliocentric elements
 * @author Bazso Akos
 ******************************************************************************/
#pragma once
#ifndef HCO2HEL__H
#define HCO2HEL__H

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
 * @brief convert heliocentric coordinates to heliocentric elements
 * @param[in,out] obj array of type #body_t
 * @param[in] dim dimension of array \a obj
 * @param[in] center index of central body (for mass parameter GM)
 * @return 0 for success, 1 for error
 */
int hco2hel(
    body_t         obj[],
    const uint32_t dim,
    const uint32_t center
);

#ifdef __cplusplus
}
#endif

/******************************************************************************/

#endif  /* HCO2HEL__H */
