/*******************************************************************************
 * MODULE  : coocvt.c
 * PURPOSE : main module for coordinate conversions
 * AUTHOR  : Bazso Akos
 * VERSION : 1.0, 20 Feb 2012
 *           1.1, 19 Aug 2012
 *           1.2, 06 Mar 2019
 ******************************************************************************/
/* include standard headers */

/* include module headers */
#include "types.h"
#include "coocvt.h"

/******************************************************************************/

/*** pre-processor definitions ***/

/* show verbose debugging output ? 0 = no (default), 1 = yes */
#define COO_CVT_DEBUG 0
#if COO_CVT_DEBUG
    #include <stdio.h>
#endif

/******************************************************************************/

/*******************************************************************************
 *  FUNCTION    : coocvt
 *  DESCRIPTION : perform coordinate conversion between two sets of coordinates
 *  INPUT       : - pointer "obj" to array of type body_t
 *                - dimension "dim" of array "obj"
 *                - index "center" of central body
 *                - conversion "mode" specifying the types of input and output
 *                  coordinates, take values from enum cvt_mode_e
 *  OUTPUT      : 0 for success, 1 for error
 ******************************************************************************/
/* TODO FIXME use bounds fromIdx, uptoIdx
 * TODO FIXME indicate index of central body
 */
int coocvt(
    body_t         obj[],
    const uint32_t dim,
    const uint32_t center,
    CVT_MODE_e     mode
    )
{
    /* default: no error */
    int ret = 0;

    /* check input array */
    if ( obj == nullptr )
    {
        /* TODO print error message */
        return 1;
    } // end if

    /* check input indices */
    if ( dim < center )
    {
        /* TODO print error message */
        return 1;
    } // end if

    /* select which conversion "mode" to apply */
    switch ( mode )
    {
        case CVT_BCO2HCO:
            ret = bco2hco( obj, dim, center );
            break;

        case CVT_HCO2BCO:
            ret = hco2bco( obj, dim, center );
            break;

        case CVT_HCO2HEL:
            ret = hco2hel( obj, dim, center );
            break;

        case CVT_HEL2HCO:
            ret = hel2hco( obj, dim, center );
            break;

        /* D'OH, don't know what to do ... */
        case CVT_NONE:
        case CVT_TOTAL_NUMBER:
        default:
            /* TODO print error message */
            ret = 1;
            break;
    } // end switch

    return ret;
} // end coocvt

/******************************************************************************/
