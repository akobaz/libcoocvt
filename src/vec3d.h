/***************************************************************************//**
 * @file   vec3d.h
 * @brief  module defining a structure vec3d_t and utility functions for it
 * @author Bazso Akos
 ******************************************************************************/
#pragma once
#ifndef VEC_3D__H
#define VEC_3D__H

/******************************************************************************/

/*!
 * @brief type definition for a 3-dimensional vector
 * @details using \a abs for padding to size of 4x double,
 * also using \a abs to store absolute value of vector
 */
typedef struct
{
    double x;   ///< x component
    double y;   ///< y component
    double z;   ///< z component
    double abs; ///< absolute value as Euclidean norm
} vec3d_t;

/******************************************************************************/

/*** function declarations ***/

/*!
 * @brief calculate the absolute value of a vector
 * @verbatim abs = <v|v>^(1/2) @endverbatim
 * @param[in] v pointer to the vector of type #vec3d_t
 * @return absolute value (Euclidean norm) as scalar
 */
double vec3d_abs(const vec3d_t* const v);


/*!
 * @brief calculate the addition (sum) of two vectors
 * @verbatim dest = v + w @endverbatim
 * @param[out] dest pointer to resulting vector of type #vec3d_t
 * @param[in] v pointer to first source vector of type #vec3d_t
 * @param[in] w pointer to second source vector of type #vec3d_t
 * @return none
 */
void vec3d_add(
    vec3d_t*             dest,
    const vec3d_t* const v,
    const vec3d_t* const w
);


/*!
 * @brief calculate the addition (sum) of two vectors
 * @details special form that returns a vector
 * @verbatim dest = v + w @endverbatim
 * @param[in] v pointer to first source vector of type #vec3d_t
 * @param[in] w pointer to second source vector of type #vec3d_t
 * @return resulting vector of type #vec3d_t
 */
vec3d_t vec3d_add_v(
    const vec3d_t* const v,
    const vec3d_t* const w
);


/*!
 * @brief calculate the angle between two vectors
 * @verbatim cos(angle) = <v|w> / (|v|*|w|) @endverbatim
 * @details if \a v or \a w have length 0, then angle = 0 is returned
 * \f[ \cos \phi = \frac{ \langle v | w \rangle }{ |v| \; |w| } \f]
 * @param[in] v pointer to first source vector of type #vec3d_t
 * @param[in] w pointer to second source vector of type #vec3d_t
 * @return angle as scalar value (in radians)
 */
double vec3d_angle(
    const vec3d_t* const v,
    const vec3d_t* const w
);


/*!
 * @brief calculate the inner (scalar) product of two vectors
 * @verbatim prod = <v|w> @endverbatim
 * @param[in] v pointer to first source vector of type #vec3d_t
 * @param[in] w pointer to second source vector of type #vec3d_t
 * @return inner product as scalar value
 */
double vec3d_inner(
    const vec3d_t* const v,
    const vec3d_t* const w
);


/*!
 * @brief calculate the absolute value of a vector to the power -3
 * @verbatim pow = |v|^(-3) @endverbatim
 * \f[ \frac{1}{|v|^3} \f]
 * @param[in] v pointer to the source vector of type #vec3d_t
 * @return absoulute value raised to the power -3 as scalar
 */
double vec3d_ipow3(const vec3d_t* const v);


/*!
 * @brief multiply-and-add of two vectors and one scalar
 * @verbatim dest = v + w * s @endverbatim
 * @param[out] dest pointer to resulting vector of type #vec3d_t
 * @param[in] v pointer to the first source vector of type #vec3d_t
 * @param[in] w pointer to the second source vector of type #vec3d_t
 * @param[in] s scalar value for scaling second vector
 * @return none
 */
void vec3d_madd(
    vec3d_t*             dest,
    const vec3d_t* const v,
    const vec3d_t* const w,
    const double         s
);


/*!
 * @brief multiply-and-add of two vectors and one scalar
 * @verbatim dest = v + w * s @endverbatim
 * @details special form that returns a vector
 * @param[in] v pointer to the first source vector of type #vec3d_t
 * @param[in] w pointer to the second source vector of type #vec3d_t
 * @param[in] s scalar value for scaling second vector
 * @return resulting vector of type #vec3d_t
 */
vec3d_t vec3d_madd_v(
    const vec3d_t* const v,
    const vec3d_t* const w,
    const double         s
);


/*!
 * @brief multiply-and-add of two vectors and two scalars
 * @verbatim dest = a * v + b * w @endverbatim
 * @param[out] dest pointer to resulting vector of type #vec3d_t
 * @param[in] a scalar value for scaling first vector
 * @param[in] v pointer to the first source vector of type #vec3d_t
 * @param[in] b scalar value for scaling second vector
 * @param[in] w pointer to the second source vector of type #vec3d_t
 * @return none
 */
void vec3d_madd2(
    vec3d_t*             dest,
    const double         a,
    const vec3d_t* const v,
    const double         b,
    const vec3d_t* const w
);


/*!
 * @brief multiply-and-add of two vectors and two scalars
 * @verbatim dest = a * v + b * w @endverbatim
 * @details special form that returns a vector
 * @param[in] a scalar value for scaling first vector
 * @param[in] v pointer to the first source vector of type #vec3d_t
 * @param[in] b scalar value for scaling second vector
 * @param[in] w pointer to the second source vector of type #vec3d_t
 * @return resulting vector of type #vec3d_t
 */
vec3d_t vec3d_madd2_v(
    const double         a,
    const vec3d_t* const v,
    const double         b,
    const vec3d_t* const w
);


/*!
 * @brief calculate the matrix times vector operation
 * @verbatim dest = A * v @endverbatim
 * @details A is a square (3x3) matrix, given by an array of 3 #vec3d_t vectors
 * @param[out] dest pointer to the resulting vector
 * @param[in] mat pointer to the "matrix" of type vec3d_t[3]
 * @param[in] vec pointer to the source vector of type #vec3d_t
 * @return none
 */
void vec3d_matvec(
    vec3d_t*             dest,
    const vec3d_t        mat[],
    const vec3d_t* const vec
);


/*!
 * @brief calculate the matrix times vector operation
 * @verbatim dest = A * v @endverbatim
 * @details A is a square (3x3) matrix, given by an array of 3 #vec3d_t vectors;
 * special form that return a vector
 * @param[in] mat pointer to the "matrix" of type vec3d_t[3]
 * @param[in] vec pointer to the source vector of type #vec3d_t
 * @return resulting vector of type #vec3d_t
 */
vec3d_t vec3d_matvec_v(
    const vec3d_t        mat[],
    const vec3d_t* const vec
);


/*!
 * @brief calculate the outer (cross) product of two vectors
 * @verbatim dest = v x w @endverbatim
 * @param[out] dest pointer to the resulting vector of type #vec3d_t
 * @param[in] v pointer to the first source vector of type #vec3d_t
 * @param[in] w pointer to the second source vector of type #vec3d_t
 * @return none
 */
void vec3d_outer(
    vec3d_t*             dest,
    const vec3d_t* const v,
    const vec3d_t* const w
);


/*!
 * @brief calculate the outer (cross) product of two vectors
 * @verbatim dest = v x w @endverbatim
 * @details special form that returns a vector
 * @param[in] v pointer to the first source vector of type #vec3d_t
 * @param[in] w pointer to the second source vector of type #vec3d_t
 * @return resulting vector of type #vec3d_t
 */
vec3d_t vec3d_outer_v(
    const vec3d_t* const v,
    const vec3d_t* const w
);


/*!
 * @brief scale a given vector to an unit vector (|v| = 1)
 * @verbatim dest = v / |v| @endverbatim
 * @details if the length of input vector is "0" no scaling is performed
 * @param[out] dest pointer to the resulting vector of type #vec3d_t
 * @param[in] v pointer to the source vector of type #vec3d_t
 * @return integer, 1 = success, 0 = error
 */
int vec3d_scale(
    vec3d_t*             dest,
    const vec3d_t* const v
);


/*!
 * @brief scale a vector to the given length "len" (|v| = len)
 * @verbatim dest = len * v / |v| @endverbatim
 * @details if the length of input vector is "0" no scaling is performed
 * @param[out] dest pointer to the resulting vector of type #vec3d_t
 * @param[in] v pointer to the source vector of type #vec3d_t
 * @param[in] len scalar value for the new length
 * @return integer, 1 = success, 0 = error
 */
int vec3d_scale2(
    vec3d_t*             dest,
    const vec3d_t* const v,
    const double         len
);


/*!
 * @brief multiplication of a vector with a scalar
 * @verbatim dest = s * v @endverbatim
 * @param[out] dest pointer to the resulting vector of type #vec3d_t
 * @param[in] v pointer to the source vector of type #vec3d_t
 * @param[in] s scalar value for scaling
 * @return none
 */
void vec3d_smul(
    vec3d_t*             dest,
    const vec3d_t* const v,
    const double         s
);


/*!
 * @brief multiplication of a vector with a scalar
 * @verbatim dest = s * v @endverbatim
 * @details special form that returns a vector
 * @param[in] v pointer to the source vector of type #vec3d_t
 * @param[in] s scalar value for scaling
 * @return resulting vector of type #vec3d_t
 */
vec3d_t vec3d_smul_v(
    const vec3d_t* const v,
    const double         s
);


/*!
 * @brief calculate the difference of two vectors
 * @verbatim dest = v - w @endverbatim
 * @param[out] dest pointer to resulting vector of type #vec3d_t
 * @param[in] v pointer to first source vector of type #vec3d_t
 * @param[in] w pointer to second source vector of type #vec3d_t
 * @return none
 */
void vec3d_sub(
    vec3d_t*             dest,
    const vec3d_t* const v,
    const vec3d_t* const w
);


/*!
 * @brief calculate the difference of two vectors
 * @verbatim dest = v - w @endverbatim
 * @details special form that returns a vector
 * @param[in] v pointer to first source vector of type #vec3d_t
 * @param[in] w pointer to second source vector of type #vec3d_t
 * @return resulting vector of type #vec3d_t
 */
vec3d_t vec3d_sub_v(
    const vec3d_t* const v,
    const vec3d_t* const w
);

/******************************************************************************/

#endif  /* VEC_3D__H */
