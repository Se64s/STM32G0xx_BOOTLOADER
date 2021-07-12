/**
 * @file    sys_def.h
 * @author  Sebastián Del Moral Gallardo (sebmorgal@gmail.com)
 * @brief   General definitions used in Sys abstraction layer.
 * @version 0.1
 * @date    2021-07-08
 * 
 * @copyright Copyright (c) 2021
 * 
 */

/* Define to prevent recursive inclusion ------------------------------------*/
#ifndef __SYS_DEF_H
#define __SYS_DEF_H

#ifdef __cplusplus
extern "C"
{
#endif

/* Exported includes --------------------------------------------------------*/

#include <stdint.h>
#include <stdbool.h>

/* Exported defines ---------------------------------------------------------*/
/* Exported types -----------------------------------------------------------*/

/** General sys layer status code */
typedef enum
{
    SYS_STATUS_OK =     0U,
    SYS_STATUS_FAIL =   1U,
    SYS_STATUS_BUSY =   2U,
    SYS_STATUS_NO_DEF = 255U
} sys_status_t;

/* Exported macro -----------------------------------------------------------*/
/* Exported functions prototypes --------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __SYS_DEF_H */

/* EOF */