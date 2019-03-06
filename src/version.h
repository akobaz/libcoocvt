/***************************************************************************//**
 * @file    version.h
 * @brief   provide version number for Coordinate Conversion Library
 * @author  Bazso Akos
 ******************************************************************************/
#pragma once
#ifndef COO_VERSION__H
#define COO_VERSION__H

/******************************************************************************/

/*** function declarations ***/

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @brief print the library's version number to stdout
 * @return none
 */
void coo_show_version(void);


/*!
 * @brief query the current major version
 * @return major version as integer
 */
int coo_get_major_version(void);


/*!
 * @brief query the current minor version
 * @return minor version as integer
 */
int coo_get_minor_version(void);

#ifdef __cplusplus
}
#endif

/******************************************************************************/

#endif  /* COO_VERSION__H */
