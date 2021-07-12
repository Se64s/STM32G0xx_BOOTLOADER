/**
 * @file    bsp_it.h
 * @author  Sebastián Del Moral Gallardo (sebmorgal@gmail.com)
 * @brief   Handlers for irq rutines.
 * @version 0.1
 * @date    2021-07-11
 * 
 * @copyright Copyright (c) 2021
 * 
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BSP_IT_H
#define __BSP_IT_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Private includes ----------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------------*/
void NMI_Handler(void);
void HardFault_Handler(void);
void SVC_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);

#ifdef __cplusplus
}
#endif

#endif /* __BSP_IT_H */

/* EOF */