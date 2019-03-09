/*******************************************************************************
 * @file    io.c
 * @brief   module for input and output of coordinate and element structures
 * @author  Bazso Akos
 * @version 1.0, 07 Feb 2012
 *          1.1, 19 Aug 2012
 *          1.2, 29 Aug 2016
 *          1.3, 19 Oct 2016
 *          1.4, 06 Nov 2016
 *          1.5, 09 Mar 2019
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
/* include module headers */
#include "io.h"
#include "const.h"

/******************************************************************************/

/*** pre-processor definitions ***/

/* show verbose debugging output ? 0 = no (default), 1 = yes */
#define COO_IO_DEBUG 0

/******************************************************************************/

/*******************************************************************************
 * input format definitions
 * ========================
 *
 * # format for Cartesian coordinates (BCO, HCO, JCO, PCO):
 * x, y, z, vx, vy, vz, mass
 *   x, y, z .......... position components           [unit = AU]
 *   vx,vy,vz ......... velocity components           [unit = AU/day]
 *   mass ............. object's mass                 [unit = solar masses]
 *
 * # format for regularized coordinates (RCO):
 * u1, u2, u3, u4, v1, v2, v3, v4, mass
 *   u1, u2, u3, u4 ... position components           [unit = AU]
 *   v1, v2, v3, v4 ... velocity components           [unit = AU/day]
 *   mass ............. object's mass                 [unit = solar masses]
 *
 * # format for Keplerian/orbital elements (HEL):
 * a, e, i, w, O, M, mass
 *   a ................ semi-major axis               [unit = AU]
 *   e ................ eccentricity                  [unit = none]
 *   i ................ inclination                   [unit = degrees | radians]
 *   w ................ argument of pericenter        [unit = degrees | radians]
 *   O ................ longitude of ascending node   [unit = degrees | radians]
 *   M ................ mean anomaly                  [unit = degrees | radians]
 *   mass ............. object's mass                 [unit = solar masses]
 *
 * # format for Delaunay elements (DEL):
 * L, G, H, l, g, h, mass
 *   L, G, H .......... action variables              [unit = AU^2/day ?]
 *   l, g, h .......... angle  variables              [unit = degrees  | radians]
 *   mass ............. object's mass                 [unit = solar masses]
 *
 * anything following these entries will be ignored until the end
 * of the current line (until '\n' character)
 ******************************************************************************/
static const char format_input3D[]  = "%lf %lf %lf %lf %lf %lf %lf";
static const char format_input4D[]  = "%lf %lf %lf %lf %lf %lf %lf %lf %lf";

/******************************************************************************/

/*******************************************************************************
 * output format definitions
 * =========================
 *
 * # format for Cartesian coordinates (BCO, HCO, JCO, PCO):
 * ID, x, y, z, vx, vy, vz
 *   ID ............... identity number of object     [unit = none]
 *   x, y, z .......... position components           [unit = AU]
 *   vx,vy,vz ......... velocity components           [unit = AU/day]
 * TODO FIXME add mass to output ?
 *
 * # format for regularized coordinates (RCO):
 * ID, u1, u2, u3, u4, v1, v2, v3, v4
 *   ID ............... identity number of object     [unit = none]
 *   u1, u2, u3, u4 ... position components           [unit = AU]
 *   v1, v2, v3, v4 ... velocity components           [unit = AU/day]
 * TODO FIXME add mass to output ?
 *
 * # format for Keplerian orbital elements (HEL):
 * ID, a, e, i, w,  O,  M
 *   ID ............... identity number of object     [unit = none]
 *   a ................ semi-major axis               [unit = AU]
 *   e ................ eccentricity                  [unit = none]
 *   i ................ inclination                   [unit = degrees | radians]
 *   w ................ argument of pericenter        [unit = degrees | radians]
 *   O ................ longitude of ascending node   [unit = degrees | radians]
 *   M ................ mean anomaly                  [unit = degrees | radians]
 * TODO FIXME add mass to output ?
 *
 * # format for Delaunay elements (DEL):
 * ID, L, G, H, l, g, h
 *   ID ............... identity number of object     [unit = none]
 *   L, G, H .......... action variables              [unit = AU^2/day ?]
 *   l, g, h .......... angle  variables              [unit = degrees | radians]
 * TODO FIXME add mass to output ?
 ******************************************************************************/
static const char format_output3D[] = "%2u   %+.15e %+.15e %+.15e   %+.15e %+.15e %+.15e\n";
static const char format_output4D[] = "%2u   %+.15e %+.15e %+.15e %+.15e   %+.15e %+.15e %+.15e %+.15e\n";

/******************************************************************************/

/*******************************************************************************
 *  FUNCTION    : coo_read_COO
 *  DESCRIPTION : read Cartesian coordinates from file to array of type body_t
 *  INPUT       : - pointer "fp" to FILE object
 *                - array "obj" for a list of bodies
 *                - dimension "dim" of arrays
 *                - input coordinate "type" (see enum COO_TYPE_e in types.h)
 *  OUTPUT      : returns number of successfully read entries (> 0),
 *                or 0 in case of error
 ******************************************************************************/
int coo_read_COO(
    FILE*            fp,
    body_t           obj[],
    const uint32_t   dim,
    const COO_TYPE_e type
    )
{
    /* check input pointers */
    if ( (fp == nullptr) || (obj == nullptr) )
    {
        /* TODO FIXME print error message */
        return 0;
    } // end if

    register uint32_t i;
    hco_t*            p = nullptr;

    for (i = 0; i < dim; i++)
    {
        /* select which type of coordinates to read:
         * type = {COO_BCO, COO_HCO, COO_JCO, COO_PCO}
         */
        switch ( type )
        {
            /* Barycentric coordinates */
            case COO_BCO: p = &obj[i].bco; break;

            /* Heliocentric coordinates */
            case COO_HCO: p = &obj[i].hco; break;

            /* Jacobi coordinates */
            case COO_JCO: p = &obj[i].jco; break;

            /* Poincare coordinates */
            case COO_PCO: p = &obj[i].pco; break;

            /* wrong input type */
            case COO_NONE:
            default:
                /* TODO FIXME print error message */
                return 0;
        } // end switch

        if (
            fscanf(
                fp,
                format_input3D,
                &p->pos.x,
                &p->pos.y,
                &p->pos.z,
                &p->vel.x,
                &p->vel.y,
                &p->vel.z,
                &obj[i].mass
            ) == EOF
        ) break;

        /* ignore rest of this line */
        while ( fgetc(fp) != '\n' );
    } // end for

    return( (int)i );
} // end coo_read_COO

/******************************************************************************/

/*******************************************************************************
 *  FUNCTION    : coo_read_DEL
 *  DESCRIPTION : read Delaunay elements from file to array of type body_t
 *  INPUT       : - pointer "fp" to FILE object
 *                - array "obj" for a list of bodies
 *                - dimension "dim" of array "obj"
 *                - flag "use_deg" to switch between input in degrees/radians
 *  OUTPUT      : returns number of successfully read entries (> 0),
 *                or 0 in case of error
 ******************************************************************************/
int coo_read_DEL(
    FILE*          fp,
    body_t         obj[],
    const uint32_t dim,
    const bool     use_deg
    )
{
    /* check input pointers */
    if ( (fp == nullptr) || (obj == nullptr) )
    {
        /* TODO FIXME show error message */
        return 0;
    } // end if

    register uint32_t i;

    for (i = 0; i < dim; i++)
    {
        if (
            fscanf(
                fp,
                format_input3D,
                &obj[i].del.L,
                &obj[i].del.G,
                &obj[i].del.H,
                &obj[i].del.l,
                &obj[i].del.g,
                &obj[i].del.h,
                &obj[i].mass
            ) == EOF
        ) break;

        /* convert angles to radians ? */
        if ( use_deg == true )
        {
            obj[i].del.l *= deg2rad;
            obj[i].del.g *= deg2rad;
            obj[i].del.h *= deg2rad;
        } // end if

        /* ignore rest of this line */
        while ( fgetc(fp) != '\n' );
    } // end for

    return( (int)i );
} // end coo_read_DEL

/******************************************************************************/

/*******************************************************************************
 *  FUNCTION    : coo_read_HEL
 *  DESCRIPTION : read orbital elements from file to array of type body_t
 *  INPUT       : - pointer "fp" to FILE object
 *                - array "obj" for a list of bodies
 *                - dimension "dim" of array "obj"
 *                - flag "use_deg" to switch between input in degrees/radians
 *  OUTPUT      : returns number of successfully read entries (> 0),
 *                or 0 in case of error
 ******************************************************************************/
int coo_read_HEL(
    FILE*          fp,
    body_t         obj[],
    const uint32_t dim,
    const bool     use_deg
    )
{
    /* check input pointers */
    if ( (fp == nullptr) || (obj == nullptr) )
    {
        /* TODO FIXME show error message */
        return 0;
    } // end if

    register uint32_t i;

    for (i = 0; i < dim; i++)
    {
        if (
            fscanf(
                fp,
                format_input3D,
                &obj[i].hel.sma,
                &obj[i].hel.ecc,
                &obj[i].hel.inc,
                &obj[i].hel.aph,
                &obj[i].hel.lan,
                &obj[i].hel.man,
                &obj[i].mass
            ) == EOF
        ) break;

        /* convert angles to radians ? */
        if ( use_deg == true )
        {
            obj[i].hel.inc *= deg2rad;
            obj[i].hel.aph *= deg2rad;
            obj[i].hel.lan *= deg2rad;
            obj[i].hel.man *= deg2rad;
        } // end if

        /* ignore rest of this line */
        while ( fgetc(fp) != '\n' );
    } // end for

    return( (int)i );
} // end coo_read_HEL

/******************************************************************************/

/*******************************************************************************
 *  FUNCTION    : coo_read_RCO
 *  DESCRIPTION : read regularized coordinates from file to array of type body_t
 *  INPUT       : - pointer "fp" to FILE object
 *                - array "obj" for a list of bodies
 *                - dimension "dim" of arrays
 *  OUTPUT      : returns number of successfully read entries (> 0),
 *                or 0 in case of error
 ******************************************************************************/
int coo_read_RCO(
    FILE*          fp,
    body_t         obj[],
    const uint32_t dim
    )
{
    /* check input pointers */
    if ( (fp == nullptr) || (obj == nullptr) )
    {
        /* TODO FIXME print error message */
        return 0;
    } // end if

    register uint32_t i;

    for (i = 0; i < dim; i++)
    {
        if (
            fscanf(
                fp,
                format_input4D,
                &obj[i].rco.pos.u1,
                &obj[i].rco.pos.u2,
                &obj[i].rco.pos.u3,
                &obj[i].rco.pos.u4,
                &obj[i].rco.vel.u1,
                &obj[i].rco.vel.u2,
                &obj[i].rco.vel.u3,
                &obj[i].rco.vel.u4,
                &obj[i].mass
            ) == EOF
        ) break;

        /* ignore rest of this line */
        while ( fgetc(fp) != '\n' );
    } // end for

    return( (int)i );
} // end coo_read_RCO

/******************************************************************************/

/*******************************************************************************
 *  FUNCTION    : coo_show_COO
 *  DESCRIPTION : print Cartesian coordinates of all objects
 *  INPUT       : - pointer "fp" to FILE object
 *                - array "obj" for a list of bodies
 *                - dimension "dim" of array "obj"
 *                - output coordinate "type" (see enum COO_TYPE_e in types.h)
 *  OUTPUT      : returns 0 on error, 1 on success
 ******************************************************************************/
int coo_show_COO(
    FILE*            fp,
    const body_t     obj[],
    const uint32_t   dim,
    const COO_TYPE_e type
    )
{
    /* check input pointers */
    if ( (fp == nullptr) || (obj == nullptr) )
    {
        /* TODO FIXME print error message */
        return 0;
    } // end if

    const hco_t* p = nullptr;

    for (register uint32_t i = 0; i < dim; i++)
    {
        /* select which type of coordinates to read:
         * type = {COO_BCO, COO_HCO, COO_JCO, COO_PCO}
         */
        switch ( type )
        {
            /* Barycentric coordinates */
            case COO_BCO: p = &obj[i].bco; break;

            /* Heliocentric coordinates */
            case COO_HCO: p = &obj[i].hco; break;

            /* Jacobi coordinates */
            case COO_JCO: p = &obj[i].jco; break;

            /* Poincare coordinates */
            case COO_PCO: p = &obj[i].pco; break;

            /* wrong input type */
            case COO_NONE:
            default:
                /* TODO FIXME print error message */
                return 0;
        } // end switch

        fprintf(
            fp,
            format_output3D,
            i,
            p->pos.x,
            p->pos.y,
            p->pos.z,
            p->vel.x,
            p->vel.y,
            p->vel.z
        );
    } // end for

    return 1;
} // end coo_show_COO

/******************************************************************************/

/*******************************************************************************
 *  FUNCTION    : coo_show_DEL
 *  DESCRIPTION : print Delaunay elements from array to file
 *  INPUT       : - pointer "fp" to FILE object
 *                - array "obj" for a list of bodies
 *                - dimension "dim" of array "obj"
 *                - flag "use_deg" to switch between output in degrees/radians
 *  OUTPUT      : returns 0 on error, 1 on success
 ******************************************************************************/
int coo_show_DEL(
    FILE*          fp,
    const body_t   obj[],
    const uint32_t dim,
    const bool     use_deg
    )
{
    /* check input pointers */
    if ( (fp == nullptr) || (obj == nullptr) )
    {
        /* TODO FIXME show error message */
        return 0;
    } // end if

    for (register uint32_t i = 0; i < dim; i++)
    {
        del_t tmp = obj[i].del;

        /* convert angles to degrees ? */
        if ( use_deg == true )
        {
            tmp.l *= rad2deg;
            tmp.g *= rad2deg;
            tmp.h *= rad2deg;
        } // end if

        fprintf(
            fp,
            format_output3D,
            i,
            tmp.L,
            tmp.G,
            tmp.H,
            tmp.l,
            tmp.g,
            tmp.h
        );
    } // end for

    return 1;
} // end coo_show_DEL

/******************************************************************************/

/*******************************************************************************
 *  FUNCTION    : coo_show_HEL
 *  DESCRIPTION : print orbital elements from array to file
 *  INPUT       : - pointer "fp" to FILE object
 *                - array "obj" for a list of bodies
 *                - dimension "dim" of array "obj"
 *                - flag "use_deg" to switch between output in degrees/radians
 *  OUTPUT      : returns 0 on error, 1 on success
 ******************************************************************************/
int coo_show_HEL(
    FILE*          fp,
    const body_t   obj[],
    const uint32_t dim,
    const bool     use_deg
    )
{
    /* check input pointers */
    if ( (fp == nullptr) || (obj == nullptr) )
    {
        /* TODO FIXME show error message */
        return 0;
    } // end if

    for (register uint32_t i = 0; i < dim; i++)
    {
        hel_t tmp = obj[i].hel;

        /* convert angles to radians ? */
        if ( use_deg )
        {
            tmp.inc *= rad2deg;
            tmp.aph *= rad2deg;
            tmp.lan *= rad2deg;
            tmp.man *= rad2deg;
        } // end if

        fprintf(
            fp,
            format_output3D,
            i,
            tmp.sma,
            tmp.ecc,
            tmp.inc,
            tmp.aph,
            tmp.lan,
            tmp.man
        );
    } // end for

    return 1;
} // end coo_show_HEL

/******************************************************************************/

/*******************************************************************************
 *  FUNCTION    : coo_show_RCO
 *  DESCRIPTION : print regularized parametric coordinates from array to file
 *  INPUT       : - pointer "fp" to FILE object
 *                - array "obj" for a list of bodies
 *                - dimension "dim" of array "obj"
 *  OUTPUT      : returns 0 on error, 1 on success
 ******************************************************************************/
int coo_show_RCO(
    FILE*          fp,
    const body_t   obj[],
    const uint32_t dim
    )
{
    /* check input pointers */
    if ( (fp == nullptr) || (obj == nullptr) )
    {
        /* TODO FIXME show error message */
        return 0;
    } // end if

    for (register uint32_t i = 0; i < dim; i++)
    {
        fprintf(
            fp,
            format_output4D,
            i,
            obj[i].rco.pos.u1,
            obj[i].rco.pos.u2,
            obj[i].rco.pos.u3,
            obj[i].rco.pos.u4,
            obj[i].rco.vel.u1,
            obj[i].rco.vel.u2,
            obj[i].rco.vel.u3,
            obj[i].rco.vel.u4
        );
    } // end for

    return 1;
} // end coo_show_RCO

/******************************************************************************/
