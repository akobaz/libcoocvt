/*******************************************************************************
 * MODULE  : hco2hel.c
 * PURPOSE : module for coordinate conversions
 *           from: heliocentric cartesian coordinates
 *           to  : heliocentric orbital elements
 * AUTHOR  : Bazso Akos
 * VERSION : 1.0, 21 Sep 2010
 *           1.1, 23 Aug 2011
 *           1.2, 30 Jan 2012
 *           1.3, 10 Feb 2012
 *           1.4, 19 Aug 2012
 *           1.5, 03 Mar 2019
 ******************************************************************************/
/* include standard headers */
#include <math.h>

/* include module headers */
#include "hco2hel.h"
#include "const.h"
#include "utils.h"
#include "vec3d.h"

/******************************************************************************/

/* show verbose debugging output ? 0 = no (default), 1 = yes */
#define HCO2HEL_DEBUG 0
#if HCO2HEL_DEBUG
    #include <stdio.h>
#endif

/******************************************************************************/

/*******************************************************************************
 *  FUNCTION    : hco2hel_core
 *  DESCRIPTION : convert from heliocentric cartesian coordinates to
 *                heliocentric orbital elements for single object
 *  INPUT       : - pointer "ele" of type hel_t for resulting elements
 *                - pointer "coo" of type hco_t for source coordinates
 *                - value for mass parameter mu = m0 + m(i)
 *  OUTPUT      : 0 = success, 1 = error
 *  REFERENCES  : TODO
 ******************************************************************************/
static int hco2hel_core(
    hel_t*             ele,
    const hco_t* const coo,
    const double       mu
    )
{
    vec3d_t angm, nvel;

    /* absolute value of position vector */
    const double pabs = vec3d_abs( &coo->pos );

    /* normalised velocity: nvel = vel / (mu)^1/2 */
    //const double vtmp = 1.0 / (gaussk * sqrt(mu));
    //const double vtmp = 1.0 / sqrt( mu );
    vec3d_smul( &nvel, &coo->vel, 1.0 / sqrt( mu ) );
    nvel.abs = vec3d_abs( &nvel );

    /* specific angular momentum: angm = r x v */
    vec3d_outer( &angm, &coo->pos, &nvel );
    angm.abs = vec3d_abs( &angm );

    /* inclination */
    ele->inc = atan2( hypot(angm.x, angm.y), angm.z );

    /* longitude of ascending node */
    ele->lan = atan2( angm.x, -angm.y );

    /* argument of latitude:
     * u = v + w = true anomaly + argument of pericenter
     */
    const double u = atan2(
        coo->pos.z * angm.abs,
        coo->pos.y * angm.x - coo->pos.x * angm.y
    );

    /* semi-major axis: 1 / a = 2 / |r| - |v|^2 */
    //ele->sma = 1.0 / ((2.0 / pabs) - nvel.abs * nvel.abs);
    const double inva = (2.0 / pabs) - nvel.abs * nvel.abs;
    /* check for correct semi-major axis: a > 0 */
    if ( inva > 0.0 )
    {
        ele->sma = 1.0 / inva;
    } // end if
    else
    {
#if HCO2HEL_DEBUG
    fprintf(
        stderr,
        "%s: Error = invalid semi-major axis 1/a = %g\n",
        __func__, inva
    );
#endif
        return 1;
    } // end else

    /* components of eccentric anomaly */
    //const double ecosE = 1.0 - pabs / ele->sma;
    const double ecosE = 1.0 - pabs * inva;
    //const double esinE = vec3d_inner( &coo->pos, &nvel ) / sqrt( ele->sma );
    const double esinE = vec3d_inner( &coo->pos, &nvel ) * sqrt( inva );
    const double E     = atan2( esinE, ecosE );

    /* eccentricity */
    ele->ecc = hypot( esinE, ecosE );
    /* check for correct eccentricity: 0 <= e < 1 */
    if ( (ele->ecc < 0.0) || (ele->ecc >= 1.0) )
    {
#if HCO2HEL_DEBUG
    fprintf(
        stderr,
        "%s: Error = invalid eccentricity e = %g\n",
        __func__, ele->ecc
    );
#endif
        return 1;
    } // end if

    /* mean anomaly */
    ele->man = E - esinE;

    /* true anomaly */
    const double e2 = ele->ecc * ele->ecc; // ecc^2
    const double ta = atan2( sqrt(1.0 - e2) * esinE, ecosE - e2 );

    /* argument of pericenter */
    ele->aph = u - ta;

    /* make angles positive */
    if (ele->inc < 0.0) ele->inc += M_2PI;
    if (ele->aph < 0.0) ele->aph += M_2PI;
    if (ele->lan < 0.0) ele->lan += M_2PI;
    if (ele->man < 0.0) ele->man += M_2PI;

    return 0;
} // end hco2hel_core

/******************************************************************************/

/*******************************************************************************
 *  FUNCTION    : hco2hel
 *  DESCRIPTION : convert from heliocentric cartesian coordinates to
 *                heliocentric orbital elements for all objects
 *  INPUT       : - pointer "obj" to array of type body_t for coordinates
 *                  (using members obj[].hco for input, obj[].hel for output)
 *                - dimension "dim" of array
 *                - index "center" for central body
 *  OUTPUT      : 0 = success, 1 = error
 ******************************************************************************/
int hco2hel(
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
    obj[center].hel = hel_zero;

    /* convert other objects */
    for (register uint32_t i = 0; i < dim; i++)
    {
        /* skip central object */
        if ( i == center ) continue;

        /* mass parameter G(M+m), with G = gaussk2 */
        const double mu = gaussk2 * (obj[center].mass + obj[i].mass);

        /* TODO FIXME check return value for error */
        (void)hco2hel_core( &obj[i].hel, &obj[i].hco, mu );
    } // end for

    return 0;
} // end hco2hel

/******************************************************************************/
