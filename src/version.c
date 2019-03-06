/*******************************************************************************
 * MODULE  : version.c
 * PURPOSE : provide version number for Coordinate Conversion Library
 * AUTHOR  : Bazso Akos
 * VERSION : 1.0, 03 Mar 2019
 ******************************************************************************/
 /* include standard headers */
#include <stdio.h>

/* include module headers */
#include "version.h"

/******************************************************************************/

/* use verbose debug output? 0 = no (default), 1 = yes */
#define COO_VERSION_DEBUG 0

/******************************************************************************/

/***
 * macros for version number as strings
 * NOTE solution after https://stackoverflow.com/questions/240353/
 ***/
#define STR(x)            #x
#define TOSTR(x)          STR(x)
#define COO_VERSION_MAJOR 2019
#define COO_VERSION_MINOR 03
#define COO_VERSION       TOSTR(COO_VERSION_MAJOR) "." TOSTR(COO_VERSION_MINOR)

/******************************************************************************/

/*******************************************************************************
 *  FUNCTION    : coo_version
 *  DESCRIPTION : print the library's version number to stdout
 *  INPUT       : none
 *  OUTPUT      : none
 ******************************************************************************/
inline void coo_show_version(void)
{
    static const char name[] = "Coordinate Conversion Library";
    fprintf(stdout, "%s v%s\n", name, COO_VERSION);
    return;
} // end coo_show_version

/******************************************************************************/

/*******************************************************************************
 *  FUNCTION    : coo_get_major_version
 *  DESCRIPTION : query the current major version
 *  INPUT       : none
 *  OUTPUT      : major version as integer
 ******************************************************************************/
inline int coo_get_major_version(void)
{
    return( (int)COO_VERSION_MAJOR );
} // end coo_get_major_version

/******************************************************************************/

/*******************************************************************************
 *  FUNCTION    : coo_get_minor_version
 *  DESCRIPTION : query the current minor version
 *  INPUT       : none
 *  OUTPUT      : minor version as integer
 ******************************************************************************/
inline int coo_get_minor_version(void)
{
    return( (int)COO_VERSION_MINOR );
} // end coo_get_minor_version

/******************************************************************************/
