/*******************************************************************************
 * @file    kepler.c
 * @brief   find numerical solution for elliptic Kepler Equation
 * @details simplified version based on Kepler Equation Solver Library
 * @author  Bazso Akos
 * @version 1.0, 11 Feb 2012
 *          1.1, 15 Oct 2015
 *          1.2, 19 Oct 2016
 *          1.3, 24 Feb 2019
 *          1.4, 09 Mar 2019
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
#include "kepler.h"
#include "const.h"

/******************************************************************************/

/*** pre-processor definitions ***/

/* show verbose debugging output ? 0 = no (default), 1 = yes */
#define COO_KEPLER_DEBUG 0
#if COO_KEPLER_DEBUG
    #include <stdio.h>
#endif

/******************************************************************************/

/*** internal constants ***/

/* to avoid division by zero */
static const double addzero = 1.0e-19;

/******************************************************************************/

/*******************************************************************************
 *  FUNCTION    : reduce
 *  DESCRIPTION : reduce input by mod(2*pi) to interval -pi <= x < pi
 *  INPUT       : angle x in radians
 *  OUTPUT      : reduced angle
 ******************************************************************************/
static inline double reduce(double x)
{
    x -= floor(x / M_2PI) * M_2PI;
    if (x >  M_PI) x -= M_2PI;
    if (x < -M_PI) x += M_2PI;
    return( x );
} // end reduce

/******************************************************************************/

/*******************************************************************************
 *  FUNCTION    : coo_sincos
 *  DESCRIPTION : evaluate sin(x), cos(x) simultaneously;
 *                if ecc >= 0 return ecc*sin(x), ecc*cos(x),
 *                if ecc < 0 return sin(x), cos(x)
 *  INPUT       : - pointer for sin(x)
 *                - pointer for cos(x)
 *                - angle x in radians
 *                - value "ecc" for extra multiplication
 *  OUTPUT      : none
 ******************************************************************************/
inline void coo_sincos(
    double*      sx,
    double*      cx,
    const double x,
    const double ecc
    )
{
    const double tx  = tan(0.5 * x);          // tan(x/2)
    const double den = 1.0 / (1.0 + tx * tx); // 1/[1+tan^2(x/2)]

    *cx = (1.0 - tx * tx) * den;              // cos(x)
    *sx = 2.0 * tx * den;                     // sin(x)

    /* multiply by eccentricity ? */
    if ( ecc >= 0.0 )
    {
        *cx *= ecc;                           // ecc*cos(x)
        *sx *= ecc;                           // ecc*sin(x)
    } // end if

    return;
} // end coo_sincos

/******************************************************************************/

/*******************************************************************************
 *  FUNCTION    : itercore
 *  DESCRIPTION : apply single pass of iteration method of Danby-Burkardt (1983)
 *                with quintic convergence to Kepler's Equation
 *  INPUT       : - value "ecc" for eccentricity 0 <= ecc < 1
 *                - value "ma" for mean anomaly 0 <= ma < pi in radians
 *                - value "x" in radians as initial guess for E0
 *  OUTPUT      : iterated value x(n+1) = E0 + delta(5)
 ******************************************************************************/
static double itercore(
    const double ecc,
    const double ma,
    const double x
    )
{
    double ecosx, esinx, dx;

    /* calculate sin, cos */
    coo_sincos( &esinx, &ecosx, x, ecc );

    /* evaluate Kepler Equation */
    const double f0 = ma - x + esinx;

    /* evaluate (scaled) derivatives of Kepler Equation */
    const double f1 = 1.0 - ecosx + addzero; /* to avoid NaN at (x,e) = (0,1) */
    const double f2 = esinx / 2.0;
    const double f3 = ecosx / 6.0;
    const double f4 = -esinx / 24.0;

    /* Iteration method: Newton-Raphson, quadratic convergence */
    dx = f0 / f1;

    /* Iteration method: Halley, cubic convergence */
    dx = f0 / (f1 + f2 * dx);

    /* Iteration method: Danby-Burkardt, quartic convergence */
    dx = f0 / (f1 + f2 * dx + f3 * dx * dx);

    /* Iteration method: Danby-Burkardt, quintic convergence */
    dx = f0 / (f1 + f2 * dx + f3 * dx * dx + f4 * dx * dx * dx);

    return( x + dx );
} // end itercore

/******************************************************************************/

/*******************************************************************************
 *  FUNCTION    : markley
 *  DESCRIPTION : quasi-direct solution method of Markley (1995) for Kepler Eq.
 *  INPUT       : - value "ecc" for eccentricity 0 <= ecc < 1
 *                - value "ma" for mean anomaly 0 <= ma < pi in radians
 *  OUTPUT      : solution E(e,M) for eccentric anomaly
 *  REFERENCE   : Markley (1995), Celest. Mech. Dyn. Astron. 63, p.101-111
 ******************************************************************************/
static double markley(
    const double ecc,
    const double ma
    )
{
    //double x, a, ad, ak, d, q, r, w;

    /* calculate parameters */
    const double tmp = 1.0 / (M_PISQ - 6.0);
    const double ad  = 3.0 * M_PISQ * tmp;
    const double ak  = 1.6 * M_PI * tmp;
    const double a   = ad + ak * (M_PI - ma) / (1.0 + ecc);                 // eq.(20)
    const double d   = 3.0 * (1.0 - ecc) + a * ecc;                         // eq.(5)
    const double q   = 2.0 * a * d * (1.0 - ecc) - ma * ma;                 // eq.(9)
    const double r   = 3.0 * a * d * (d - 1.0 + ecc) * ma + ma * ma * ma;   // eq.(10)
    double       w   = cbrt( fabs(r) + sqrt(q * q * q + r * r) );           // eq.(14)
    w               *= w;

    /*** STEP #1: find starter from Pade approximation ***/
    double x0 = 0.0;
    if ( w > 0.0 )
    {
        /* starter E0 */
        x0 = (2.0 * r * w / (w * w + q * w + q * q) + ma) / d;              // eq.(15)
    } // end if

    /*** STEP #2: 5th order correction for starter after Danby & Burkardt (1983) ***/
    return(
        itercore(ecc, ma, x0)                                               // eq.(24)
    );
} // end markley

/******************************************************************************/

/*******************************************************************************
 *  FUNCTION    : coo_kesolver
 *  DESCRIPTION : simplified version of solver function from
 *                Kepler Equation Solver Library
 *  INPUT       : - value "ecc" for eccentricity 0 <= ecc < 1
 *                - value "ma" for mean anomaly in radians,
 *                  any arbitrary real number is OK
 *  OUTPUT      : solution E(e,M) for eccentric anomaly in range 0 <= E < 2*pi
 ******************************************************************************/
double coo_kesolver(
    const double ecc,
    const double ma
    )
{
    /* reduce mean anomaly to -pi <= M < pi */
    const double mr = reduce(ma);

    /* solve Kepler Equation for negative values of M */
    if ( mr < 0.0 )
    {
        return( -markley(ecc, -mr) + M_2PI );
    } // end if
    /* solve Kepler Equation for positive values of M */
    else
    {
        return( markley(ecc, mr) );
    } // end else
} // end coo_kesolver

/******************************************************************************/
