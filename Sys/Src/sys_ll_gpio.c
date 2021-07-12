/**
 * @file    sys_ll_gpio.c
 * @author  Sebastián Del Moral Gallardo (sebmorgal@gmail.com)
 * @brief   System abstraction for low-level gpio driver.
 * @version 0.1
 * @date    2021-07-08
 * 
 * @copyright Copyright (c) 2021
 * 
 */

/* Private includes --------------------------------------------------------*/

#include "sys_ll_gpio.h"
#include "bsp_gpio.h"

/* Private defines ---------------------------------------------------------*/
/* Private variable --------------------------------------------------------*/
/* Private macro -----------------------------------------------------------*/
/* Private functions prototypes --------------------------------------------*/
/* Private functions definition --------------------------------------------*/
/* Public function definition ----------------------------------------------*/

void SYS_LL_GpiolInit(void)
{
    BSP_Gpio_Init();
}

/* EOF */