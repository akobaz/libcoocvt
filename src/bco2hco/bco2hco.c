/*******************************************************************************
 * MODULE  : bco2hco.c
 * PURPOSE : module for coordinate conversions
 *           from: heliocentric Cartesian coordinates
 *           to  : barycentric Cartesian coordinates
 * AUTHOR  : Bazso Akos
 * VERSION : 1.0, 02 Feb 2012
 *           1.1, 10 Feb 2012
 *           1.2, 21 Feb 2012
 *           1.3, 19 Aug 2012
 *           1.4, 23 Oct 2016
 *           1.5, 02 Mar 2019
 ******************************************************************************/
/* include module headers */
#include "bco2hco.h"
#include "utils.h"

/******************************************************************************/

/* show verbose debugging output ? 0 = no (default), 1 = yes */
#define BCO2HCO_DEBUG 0
#if BCO2HCO_DEBUG
    #include <stdio.h>
#endif

/******************************************************************************/

/*******************************************************************************
 *  FUNCTION    : bco2hco
 *  DESCRIPTION : convert from barycentric Cartesian coordinates to
 *                heliocentric Cartesian coordinates
 *  INPUT       : - pointer "obj" to array of type body_t for coordinates
 *                  (using members obj[].bco for input, obj[].hco for output)
 *                - dimension "dim" of array
 *                - index "center" for central body
 *  OUTPUT      : 0 = success, 1 = error
 ******************************************************************************/
inline int bco2hco(
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

    /* coordinates of central body */
    const hco_t bc = obj[center].bco;

    /***
     * subtract barycentric position/velocity of object with index "center"
     * to transform to heliocentric coordinates:
     * hco = bco - bc
     ***/
    for (register uint32_t i = 0; i < dim; i++)
    {
        coo_recenter( &obj[i].hco, &obj[i].bco, &bc );
    } // end for

    return 0;
} // end bco2hco

/******************************************************************************/
