/***************************************************************************//**
 * @file   kepler.h
 * @brief  find numerical solution for elliptic Kepler Equation
 * @author Bazso Akos
 ******************************************************************************/
#pragma once
#ifndef COO_KEPLER__H
#define COO_KEPLER__H

/******************************************************************************/

/*** function declarations ***/

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @brief solver for Kepler Equation
 * @details elliptic case for elliptic eccentric anomaly x
 * \f$ x - e * sin(x) = M \f$
 * @param[in] ecc eccentricity, 0 < ecc < 1
 * @param[in] ma mean anomaly in radians
 * @return eccentric anomaly in radians
 ***/
double coo_kesolver(
    const double ecc,
    const double ma
);


/*!
 * @brief evaluate sin(x), cos(x) simultaneously
 * @details modify return value based on parameter "ecc":
 * if ecc >= 0 return ecc*sin(x), ecc*cos(x);
 * if ecc < 0 return sin(x), cos(x)
 * @param[out] sx pointer for sin(x)
 * @param[out] cx pointer for cos(x)
 * @param[in] x input value (in radians)
 * @param[in] ecc eccentricity
 * @return none
 */
void coo_sincos(
    double*      sx,
    double*      cx,
    const double x,
    const double ecc
);

#ifdef __cplusplus
}
#endif

/******************************************************************************/

#endif  /* COO_KEPLER__H */
