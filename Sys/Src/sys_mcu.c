/**
 * @file    sys_mcu.c
 * @author  Sebastián Del Moral Gallardo (sebmorgal@gmail.com)
 * @brief   Init subset of function for init MCU basic perioheral (mamory and clocks).
 * @version 0.1
 * @date    2021-07-01
 * 
 * @copyright Copyright (c) 2021
 * 
 */

/* Includes ------------------------------------------------------------------*/

#include "sys_mcu.h"
#include "sys_ll_serial.h"
#include "user_error.h"
#include "bsp_mcu.h"

/* Private includes ----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

static void vErrorHandler(char *msg, uint32_t len);

/* Private user code ---------------------------------------------------------*/

/**
  * @brief  Init resources for init errors and show info by serial interface
  * @param  msg: error message
  * @param  len: size of error msg
  * @retval None
  */
static void vErrorHandler(char *msg, uint32_t len)
{
    uint8_t *pu8MsgAddr = (uint8_t*)msg;
    uint16_t u8MsgLen = (uint16_t)len;

    /* Init interface */
    (void)SYS_LL_SerialInit(SYS_LL_SERIAL_0);

    /* Send data */
    (void)SYS_LL_SerialSend(SYS_LL_SERIAL_0, pu8MsgAddr, u8MsgLen);
}

/* Public functions ----------------------------------------------------------*/

void Sys_Mcu_Init(void)
{
    /* Init low-level flash and clocks */
    BSP_Mcu_Init();

    /* Init Error interface */
    vErrorInit(vErrorHandler);
}

void Sys_Mcu_Reset(void)
{
    BSP_Mcu_Reset();
}

void Sys_Mcu_Delay(uint32_t u32msDelay)
{
    BSP_Mcu_Delay(u32msDelay);
}

/* EOF */