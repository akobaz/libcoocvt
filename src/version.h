/***************************************************************************//**
 * @file    version.h
 * @brief   provide version number for Coordinate Conversion Library
 * @author  Bazso Akos
 *
 * @copyright
 * Copyright (C) 2019 Bazso Akos
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
