/*******************************************************************************
 * MODULE  : hel2hco.c
 * PURPOSE : module for coordinate conversions
 *           from: heliocentric orbital elements
 *           to  : heliocentric cartesian coordinates
 * AUTHOR  : Bazso Akos
 * VERSION : 1.0, 21 Sep 2010
 *           1.1, 23 Aug 2011
 *           1.2, 31 Jan 2012
 *           1.3, 10 Feb 2012
 *           1.4, 19 Aug 2012
 *           1.5, 03 Mar 2019
 ******************************************************************************/
/* include standard headers */
#include <math.h>

/* include module headers */
#include "hel2hco.h"
#include "const.h"
#include "kepler.h"
#include "utils.h"
#include "vec3d.h"

/******************************************************************************/

/* show verbose debugging output ? 0 = no (default), 1 = yes */
#define HEL2HCO_DEBUG 0
#if HEL2HCO_DEBUG
    #include <stdio.h>
#endif

/******************************************************************************/

/*******************************************************************************
 *  FUNCTION    : hel2hco_core
 *  DESCRIPTION : convert from heliocentric orbital elements to heliocentric
 *                cartesian coordinates for single object
 *  INPUT       : - pointer of type hel_t for source elements "ele"
 *                - pointer of type hco_t for resulting coordinates "coo"
 *                - value for mass parameter mu = m0 + m(i)
 *  OUTPUT      : 0 = success, 1 = error
 ******************************************************************************/
static int hel2hco_core(
    hco_t*             coo,
    const hel_t* const ele,
    const double       mu
    )
{
    double cosinc, sininc;   /* Inklination */
    double cosaph, sinaph;   /* Arg. d. Perihels */
    double coslan, sinlan;   /* Knotenlaenge */
    double cosE, sinE;       /* exzentr. Anom. */
    double q1, q2;

    /* check a > 0 */
    if ( ele->sma <= 0.0 ) return 1;

    /* check 0 <= ecc < 1 */
    if ( (ele->ecc < 0.0) || (ele->ecc >= 1.0) ) return 1;

    /* TODO check e == 0, i == 0 */

    /* trigonometric functions of the angles ...
     * NOTE leave last argument "-1"
     */
    coo_sincos( &sininc, &cosinc, ele->inc, -1.0 );
    coo_sincos( &sinaph, &cosaph, ele->aph, -1.0 );
    coo_sincos( &sinlan, &coslan, ele->lan, -1.0 );

    /* transformation matrix elements */
    const double s11 =  coslan * cosaph - sinlan * sinaph * cosinc;
    const double s21 =  sinlan * cosaph + coslan * sinaph * cosinc;
    const double s31 =  sinaph * sininc;
    const double s12 = -coslan * sinaph - sinlan * cosaph * cosinc;
    const double s22 = -sinlan * sinaph + coslan * cosaph * cosinc;
    const double s32 =  cosaph * sininc;

    /* eccentric anomaly via solution of Kepler's Equation;
     * TODO FIXME use sensible default value for E as backup
     * in case that kesolver() fails
     */
    const double ea = coo_kesolver( ele->ecc, ele->man ); // tmp = ...
    coo_sincos( &sinE, &cosE, ea, -1.0 );

    /* Cartesian coordinates */
    const double tmpe = sqrt(1.0 - ele->ecc * ele->ecc);
    q1 = ele->sma * (cosE - ele->ecc);
    q2 = ele->sma * tmpe * sinE;
    coo->pos.x = s11 * q1 + s12 * q2;
    coo->pos.y = s21 * q1 + s22 * q2;
    coo->pos.z = s31 * q1 + s32 * q2;

    /* Cartesian velocities */
    //q1 = gaussk * sqrt(mu) / ((1.0 - ele->ecc * cosE) * sqrt(ele->sma));
    q1  = sqrt( mu ) / ((1.0 - ele->ecc * cosE) * sqrt( ele->sma ));
    q2  = q1 * tmpe * cosE;
    q1 *= -sinE;
    coo->vel.x = s11 * q1 + s12 * q2;
    coo->vel.y = s21 * q1 + s22 * q2;
    coo->vel.z = s31 * q1 + s32 * q2;

    return 0;
} // end hel2hco_core

/******************************************************************************/

/*******************************************************************************
 *  FUNCTION    : hel2hco
 *  DESCRIPTION : convert from heliocentric orbital elements to heliocentric
 *                cartesian coordinates for all objects
 *  INPUT       : - pointer "obj" to array of type body_t for coordinates
 *                  (using members obj[].hel for input, obj[].hco for output)
 *                - dimension "dim" of array
 *                - index "center" for central body
 *  OUTPUT      : 0 = success, 1 = error
 ******************************************************************************/
int hel2hco(
    body_t         obj[],
    const uint32_t dim,
    const uint32_t center
    )
{
    /* check input */
    if ( (obj == nullptr) || (dim < center) )
    {
        /* TODO print error message */
        return 1;
    } // end if

    /* set central object to zero */
    obj[center].hco = hco_zero;

    /* convert other objects */
    for (register uint32_t i = 0; i < dim; i++)
    {
        /* skip central object */
        if ( i == center ) continue;

        /* mass parameter G(M+m), with G = gaussk2 */
        const double mu = gaussk2 * (obj[center].mass + obj[i].mass);

        /* TODO FIXME check return value for error */
        (void)hel2hco_core( &obj[i].hco, &obj[i].hel, mu );
    } // end for

    return 0;
} // end hel2hco

/******************************************************************************/
