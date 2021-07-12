/**
 * @file    bsp_mcu.h
 * @author  Sebastián Del Moral (sebmorgal@gmail.com)
 * @brief   Low-level initial setup.
 * @version 0.1
 * @date    2020-09-27
 * 
 * @copyright Copyright (c) 2020
 * 
 */

/* Define to prevent recursive inclusion ------------------------------------*/
#ifndef __BSP_MCU_H
#define __BSP_MCU_H

#ifdef __cplusplus
extern "C"
{
#endif

/* Exported includes --------------------------------------------------------*/
/* Exported defines ---------------------------------------------------------*/
/* Exported types -----------------------------------------------------------*/
/* Exported macro -----------------------------------------------------------*/
/* Exported functions prototypes --------------------------------------------*/

/**
 * @brief Init flash memory and system clocks.
 * 
 */
void BSP_Mcu_Init(void);

/**
 * @brief Reset platform.
 * 
 */
void BSP_Mcu_Reset(void);

/**
 * @brief Low level delay function.
 * 
 * @param u32MsTime time to wait in ms.
 */
void BSP_Mcu_Delay(uint32_t u32MsTime);

#ifdef __cplusplus
}
#endif

#endif /* __BSP_MCU_H */

/*EOF*/