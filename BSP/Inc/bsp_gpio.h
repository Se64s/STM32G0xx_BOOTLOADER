/**
 * @file    bsp_gpio.h
 * @author  Sebastián Del Moral (sebmorgal@gmail.com)
 * @brief   Low-level initial setup.
 * @version 0.1
 * @date    2020-09-27
 * 
 * @copyright Copyright (c) 2020
 * 
 */

/* Define to prevent recursive inclusion ------------------------------------*/
#ifndef __BSP_GPIO_H
#define __BSP_GPIO_H

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
 * @brief Init GPIO interface.
 * 
 */
void BSP_Gpio_Init(void);

#ifdef __cplusplus
}
#endif

#endif /* __BSP_GPIO_H */

/*EOF*/