/*******************************************************************************
 * MODULE  : vec3d.c
 * PURPOSE : module defining a structure vec3d_t and utility functions for it
 * AUTHOR  : Bazso Akos
 * VERSION : 1.0, 24 Aug 2011
 *           1.1, 30 Jan 2012
 *           1.2, 06 Feb 2012
 *           1.3, 16 Jun 2012
 *           1.4, 17 Nov 2013
 *           1.5, 15 Apr 2014
 *           1.6, 20 Feb 2019
 ******************************************************************************/
/* include standard headers */
#include <math.h>

/* include module header */
#include "vec3d.h"

/******************************************************************************/

/***
 * vec3d_inner
 * inner (scalar) product of two vectors; a & b can be the same vector
 * <a|b> = a.x * b.x + a.y * b.y + a.z * b.z
 ***/
inline double vec3d_inner(
    const vec3d_t* const a,
    const vec3d_t* const b
    )
{
    return( a->x * b->x + a->y * b->y + a->z * b->z );
} // end vec3d_inner

/******************************************************************************/

/***
 * vec3d_abs
 * absolute value of a vector (Euclidean norm)
 * <v|v>^1/2
 ***/
inline double vec3d_abs(const vec3d_t* const v)
{
    return( sqrt(v->x * v->x + v->y * v->y + v->z * v->z) );
} // end vec3d_abs

/******************************************************************************/

/***
 * vec3d_add
 * addition of two vectors
 * a + b = (a.x + b.x, a.y + b.y, a.z + b.z)
 * NOTE no update of dest->abs because of possible side effects
 ***/
inline void vec3d_add(
    vec3d_t*             dest,
    const vec3d_t* const a,
    const vec3d_t* const b
    )
{
    dest->x = a->x + b->x;
    dest->y = a->y + b->y;
    dest->z = a->z + b->z;
} // end vec3d_add

/***
 * vec3d_add_v
 * addition of two vectors
 * function returns a vector
 ***/
inline vec3d_t vec3d_add_v(
    const vec3d_t* const a,
    const vec3d_t* const b
    )
{
    return(
        (vec3d_t){
            .x = a->x + b->x,
            .y = a->y + b->y,
            .z = a->z + b->z,
            .abs = 0.0
        }
    );
} // end vec3d_add_v

/******************************************************************************/

/***
 * vec3d_angle
 * angle between two vectors
 * cos(angle) = <a|b> / (|a| * |b|)
 * NOTE uses vec3d_abs() & vec3d_inner(), functions must already be defined
 ***/
inline double vec3d_angle(
    const vec3d_t* const a,
    const vec3d_t* const b
    )
{
    const double den = vec3d_abs(a) * vec3d_abs(b); /* denominator */
    if ( den > 0.0 )
    {
        const double num = vec3d_inner(a, b); /* numerator */
        return( acos(num / den) );
    } // end if
    else return 0.0;
} // end vec3d_angle

/******************************************************************************/

/***
 * vec3d_ipow3
 * power -3 of absolute value
 * 1 / |v|^3
 * NOTE no update of v->abs because of possible side effects
 ***/
inline double vec3d_ipow3(const vec3d_t* const v)
{
    const double tmp = vec3d_abs(v);
    if ( tmp > 0.0 )
    {
        return( 1.0 / (tmp * tmp * tmp) );
    } // end if
    else return 0.0;
} // end vec3d_ipow3

/******************************************************************************/

/***
 * vec3d_madd
 * multiply a vector with a scalar and add to another vector
 * dest = v + w * scalar
 * NOTE no update of dest->abs because of possible side effects
 ***/
inline void vec3d_madd(
    vec3d_t*             dest,
    const vec3d_t* const v,
    const vec3d_t* const w,
    const double         scalar
    )
{
    dest->x = v->x + w->x * scalar;
    dest->y = v->y + w->y * scalar;
    dest->z = v->z + w->z * scalar;
} // end vec3d_madd

/***
 * vec3d_madd_v
 * multiply a vector with a scalar and add to another vector
 * function returns a vector
 ***/
inline vec3d_t vec3d_madd_v(
    const vec3d_t* const v,
    const vec3d_t* const w,
    const double         scalar
    )
{
    return(
        (vec3d_t){
            .x = v->x + w->x * scalar,
            .y = v->y + w->y * scalar,
            .z = v->z + w->z * scalar,
            .abs = 0.0
        }
    );
} // end vec3d_madd_v

/******************************************************************************/

/***
 * vec3d_madd2
 * multiply and add two vectors and scalars
 * dest = a * v + b * w
 * a,b = scalar
 * v,w = vector
 * NOTE no update of dest->abs because of possible side effects
 ***/
inline void vec3d_madd2(
    vec3d_t*             dest,
    const double         a,
    const vec3d_t* const v,
    const double         b,
    const vec3d_t* const w
    )
{
    dest->x = a * v->x + b * w->x;
    dest->y = a * v->y + b * w->y;
    dest->z = a * v->z + b * w->z;
} // end vec3d_madd2

/***
 * vec3d_madd2_v
 * multiply and add two vectors and scalars
 * function returns a vector
 ***/
inline vec3d_t vec3d_madd2_v(
    const double         a,
    const vec3d_t* const v,
    const double         b,
    const vec3d_t* const w
    )
{
    return(
        (vec3d_t){
            .x = a * v->x + b * w->x,
            .y = a * v->y + b * w->y,
            .z = a * v->z + b * w->z,
            .abs = 0.0
        }
    );
} // end vec3d_madd2_v

/******************************************************************************/

/***
 * vec3d_matvec
 * product of a matrix with a vector
 * dest = A * v
 * NOTE no update of dest->abs because of possible side effects
 ***/
inline void vec3d_matvec(
    vec3d_t*             dest,
    const vec3d_t        mat[],
    const vec3d_t* const vec
    )
{
    dest->x = vec3d_inner( &mat[0], vec );
    dest->y = vec3d_inner( &mat[1], vec );
    dest->z = vec3d_inner( &mat[2], vec );
} // end vec3d_matvec

/***
 * vec3d_matvec_v
 * product of a matrix with a vector
 * function returns a vector
 ***/
inline vec3d_t vec3d_matvec_v(
    const vec3d_t        mat[],
    const vec3d_t* const vec
    )
{
    return(
        (vec3d_t){
            .x = vec3d_inner( &mat[0], vec ),
            .y = vec3d_inner( &mat[1], vec ),
            .z = vec3d_inner( &mat[2], vec ),
            .abs = 0.0
        }
    );
} // end vec3d_matvec_v

/******************************************************************************/

/***
 * vec3d_outer
 * outer (cross) product of two vectors
 * a x b = (a.y*b.z-a.z*b.y, a.z*b.x-a.x*b.z, a.x*b.y-a.y*b.x)
 * NOTE no update of dest->abs because of possible side effects
 ***/
inline void vec3d_outer(
    vec3d_t*             dest,
    const vec3d_t* const a,
    const vec3d_t* const b
    )
{
    dest->x = a->y * b->z - a->z * b->y;
    dest->y = a->z * b->x - a->x * b->z;
    dest->z = a->x * b->y - a->y * b->x;
} // end vec3d_outer

/***
 * vec3d_outer_v
 * outer (cross) product of two vectors
 * function returns a vector
 ***/
inline vec3d_t vec3d_outer_v(
    const vec3d_t* const a,
    const vec3d_t* const b
    )
{
    return(
        (vec3d_t){
            .x = a->y * b->z - a->z * b->y,
            .y = a->z * b->x - a->x * b->z,
            .z = a->x * b->y - a->y * b->x,
            .abs = 0.0
        }
    );
} // end vec3d_outer_v

/******************************************************************************/

/***
 * vec3d_scale
 * scale a vector to an unit vector (length = 1)
 * dest = src / |src|
 ***/
inline int vec3d_scale(
    vec3d_t*             dest,
    const vec3d_t* const src
    )
{
    dest->abs = vec3d_abs( src );
    if ( dest->abs > 0.0 )
    {
        vec3d_smul( dest, src, 1.0 / dest->abs );
        dest->abs = 1.0;
        return 1;
    } // end if
    else return 0;
} // end vec3d_scale

/******************************************************************************/

/***
 * vec3d_scale2
 * scale a vector to the given length "len"
 * dest = len * src / |src|
 ***/
inline int vec3d_scale2(
    vec3d_t*             dest,
    const vec3d_t* const src,
    const double         len
    )
{
    dest->abs = vec3d_abs( src );
    if ( dest->abs > 0.0 )
    {
        vec3d_smul( dest, src, len / dest->abs );
        dest->abs = len;
        return 1;
    } // end if
    else return 0;
} // end vec3d_scale2

/* TODO FIXME implement function
 * vec3d_t vec3d_scale2_v(v, len)
 */

/******************************************************************************/

/***
 * vec3d_smul
 * multiplication of a vector with a scalar
 * dest = s * v = (s * v.x, s * v.y, s * v.z)
 * NOTE no update of dest->abs because of possible side effects
 ***/
inline void vec3d_smul(
    vec3d_t*             dest,
    const vec3d_t* const v,
    const double         scalar
    )
{
    dest->x = scalar * v->x;
    dest->y = scalar * v->y;
    dest->z = scalar * v->z;
} // end vec3d_smul

/***
 * vec3d_smul_v
 * multiplication of a vector with a scalar
 * function returns a vector
 ***/
inline vec3d_t vec3d_smul_v(
    const vec3d_t* const v,
    const double         scalar
    )
{
    return(
        (vec3d_t){
            .x = scalar * v->x,
            .y = scalar * v->y,
            .z = scalar * v->z,
            .abs = 0.0
        }
    );
} // end vec3d_smul_v

/******************************************************************************/

/***
 * vec3d_sub
 * calculate the difference of two vectors
 * a - b = (a.x - b.x, a.y - b.y, a.z - b.z)
 * NOTE no update of dest->abs because of possible side effects
 ***/
inline void vec3d_sub(
    vec3d_t*             dest,
    const vec3d_t* const a,
    const vec3d_t* const b
    )
{
    dest->x = a->x - b->x;
    dest->y = a->y - b->y;
    dest->z = a->z - b->z;
} // end vec3d_sub

/***
 * vec3d_sub_v
 * calculate the difference of two vectors
 * function returns a vector
 ***/
inline vec3d_t vec3d_sub_v(
    const vec3d_t* const a,
    const vec3d_t* const b
    )
{
    return(
        (vec3d_t){
            .x = a->x - b->x,
            .y = a->y - b->y,
            .z = a->z - b->z,
            .abs = 0.0
        }
    );
} // end vec3d_sub_v

/******************************************************************************/
