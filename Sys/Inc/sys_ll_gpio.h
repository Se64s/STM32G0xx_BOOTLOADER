/**
 * @file    sys_ll_gpio.h
 * @author  Sebastián Del Moral Gallardo (sebmorgal@gmail.com)
 * @brief   System abstraction for low-level gpio driver.
 * @version 0.1
 * @date    2021-07-08
 * 
 * @copyright Copyright (c) 2021
 * 
 */

/* Define to prevent recursive inclusion ------------------------------------*/
#ifndef __SYS_LL_GPIO_H
#define __SYS_LL_GPIO_H

#ifdef __cplusplus
extern "C"
{
#endif

/* Exported includes --------------------------------------------------------*/

#include "sys_def.h"

/* Exported defines ---------------------------------------------------------*/
/* Exported types -----------------------------------------------------------*/
/* Exported macro -----------------------------------------------------------*/
/* Exported functions prototypes --------------------------------------------*/

/**
 * @brief Init low level gpio layer.
 * 
 */
void SYS_LL_GpiolInit(void);

#ifdef __cplusplus
}
#endif

#endif /* __SYS_LL_GPIO_H */

/* EOF */