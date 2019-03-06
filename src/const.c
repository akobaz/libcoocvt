/*******************************************************************************
 * MODULE  : const.c
 * PURPOSE : module providing global constants for libcoocvt library
 * AUTHOR  : Bazso Akos
 * VERSION : 1.0, 19 Oct 2016
 *           1.1, 19 Feb 2019
 ******************************************************************************/
/* include standard headers */
#include <math.h>

/* include module header */
#include "const.h"

/******************************************************************************/

/*** export global constants ***/

/* two-times-pi: 2*pi */
const double M_2PI   = (M_PI + M_PI);

/* pi-squared: pi^2 */
const double M_PISQ  = (M_PI * M_PI);

/* convert from degrees to radians */
const double deg2rad = M_PI / 180.0;

/* convert from radians to degrees */
const double rad2deg = 180.0 / M_PI;

/******************************************************************************/

/*******************************************************************************
 * Gaussian gravitational constant "k" to full accurracy as given by the
 * IAU 1976 definition,
 * dimensions [k^2] = [AU^3 M_Sun^-1 days^-2] ~ [G] = [m^3 kg^-1 s^-2]
 ******************************************************************************/
const double gaussk  = 0.01720209895;
const double gaussk2 = 2.9591220828559115E-04;

/******************************************************************************/
