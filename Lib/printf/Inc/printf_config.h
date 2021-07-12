/**
 * @file    printf_config.h
 * @author  Sebastián Del Moral Gallardo (sebmorgal@gmail.com)
 * @brief   Config file for printf libary
 * @version 0.1
 * @date    2021-07-11
 * 
 * @copyright Copyright (c) 2021
 * 
 */

/* Define to prevent recursive inclusion ------------------------------------*/
#ifndef __PRINTF_CONFIG_H
#define __PRINTF_CONFIG_H

#ifdef __cplusplus
extern "C"
{
#endif

/* Exported includes --------------------------------------------------------*/
/* Exported defines ---------------------------------------------------------*/

/** ntoa (integer) conversion buffer size. 
 * This must be big enough to hold one converted numeric number including leading zeros, 
 * normally 32 is a sufficient value. 
 * Created on the stack 
 */
#define PRINTF_NTOA_BUFFER_SIZE             ( 32U )

/** ftoa (float) conversion buffer size. 
 * This must be big enough to hold one converted float number including leading zeros, 
 * normally 32 is a sufficient value. 
 * Created on the stack.
 */
#define PRINTF_FTOA_BUFFER_SIZE             ( 32U )

/** Define the default floating point precision.
 */
#define PRINTF_DEFAULT_FLOAT_PRECISION      ( 6 )

/** Define the largest suitable value to be printed with %f, 
 * before using exponential representation.
 */
#define PRINTF_MAX_FLOAT                    ( 1e9 )

/** Define this to disable floating point (%f) support */
#define PRINTF_DISABLE_SUPPORT_FLOAT

/** Define this to disable exponential floating point (%e) support */
#define PRINTF_DISABLE_SUPPORT_EXPONENTIAL

/** Define this to disable long long (%ll) support */
#define PRINTF_DISABLE_SUPPORT_LONG_LONG

/** Define this to disable ptrdiff_t (%t) support */
#define PRINTF_DISABLE_SUPPORT_PTRDIFF_T

/* Exported types -----------------------------------------------------------*/
/* Exported macro -----------------------------------------------------------*/
/* Exported functions prototypes --------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __PRINTF_CONFIG_H */

/*EOF*/