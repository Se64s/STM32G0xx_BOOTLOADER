/**
 * @file    sys_mcu.h
 * @author  Sebastián Del Moral Gallardo (sebmorgal@gmail.com)
 * @brief   Init subset of function for init MCU basic perioheral (mamory and clocks).
 * @version 0.1
 * @date    2021-07-01
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef __SYS_MCU_H
#define __SYS_MCU_H

/* Includes ------------------------------------------------------------------*/

#include "sys_def.h"

/* Private includes ----------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------------*/

/**
 * @brief Init flash memory and system clocks.
 * 
 */
void Sys_Mcu_Init(void);

/**
 * @brief Soft reset platform.
 * 
 */
void Sys_Mcu_Reset(void);

/**
 * @brief Low-level delay implementation
 * 
 * @param u32msDelay time to delay in ms.
 */
void Sys_Mcu_Delay(uint32_t u32msDelay);

#endif /* __SYS_INIT_H */

/* EOF */