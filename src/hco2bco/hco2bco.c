/*******************************************************************************
 * MODULE  : hco2bco.c
 * PURPOSE : module for coordinate conversions
 *           from: heliocentric Cartesian coordinates
 *           to  : barycentric Cartesian coordinates
 * AUTHOR  : Bazso Akos
 * VERSION : 1.0, 02 Feb 2012
 *           1.1, 10 Feb 2012
 *           1.2, 19 Aug 2012
 *           1.3, 11 Nov 2016
 *           1.4, 02 Mar 2019
 ******************************************************************************/
/* include module headers */
#include "hco2bco.h"
#include "utils.h"

/******************************************************************************/

/* show verbose debugging output ? 0 = no (default), 1 = yes */
#define HCO2BCO_DEBUG 0
#if HCO2BCO_DEBUG
    #include <stdio.h>
#endif

/******************************************************************************/

/*******************************************************************************
 *  FUNCTION    : hco2bco
 *  DESCRIPTION : convert from heliocentric Cartesian coordinates to
 *                barycentric Cartesian coordinates
 *  INPUT       : - pointer "obj" to array of type body_t for coordinates
 *                  (using members obj[].hco for input, obj[].bco for output)
 *                - dimension "dim" of array
 *                - index "center" for central body
 *  OUTPUT      : 0 = success, 1 = error
 ******************************************************************************/
int hco2bco(
    body_t         obj[],
    const uint32_t dim,
    const uint32_t center
    )
{
    /* check input */
    if ( (obj == nullptr) || (dim < center) )
    {
        /* TODO FIXME print error message */
        return 1;
    } // end if

    /* determine barycenter (center of mass) position/velocity */
    hco_t bc; /* barycenter */
    if ( coo_get_barycenter( &bc, obj, 0, dim, COO_HCO ) != 0 )
    {
        /* TODO FIXME print error message */
        return 1;
    } // end if

    /***
     * subtract barycenter position/velocity "bc" from all objects
     * to transform to barycentric coordinates:
     * bco = hco - bc
     ***/
    for (register uint32_t i = 0; i < dim; i++)
    {
        coo_recenter( &obj[i].bco, &obj[i].hco, &bc );
    } // end for

    return 0;
} // end hco2bco

/******************************************************************************/
