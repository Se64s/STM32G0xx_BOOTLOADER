/**
 * @file    boot.c
 * @author  Sebastián Del Moral (sebmorgal@gmail.com)
 * @brief   Set of functions to handle bootloader execution jumps.
 * @version 0.1
 * @date    2021-07-01
 * 
 * @copyright Copyright (c) 2021
 * 
 */

/* Includes ------------------------------------------------------------------*/
#include "boot.h"
#include "memory_map.h"

/* Private includes ----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

static void start_app(uint32_t pc, uint32_t sp) __attribute__((naked));

/* Private function ----------------------------------------------------------*/

/**
 * @brief   Assembler function to load app address to PC.
 * @param   pc uint32 address to locate in PC reg.
 * @param   sp uint32 address to locate in SP reg.
 * @retval  None
 */
static void start_app(uint32_t pc, uint32_t sp)
{
    __asm("           \n\
          msr msp, r1 /* load r1 into MSP */\n\
          bx r0       /* branch to the address at r0 */\n\
    ");
}

/* Public function -----------------------------------------------------------*/

/**
 * @brief Pass execution to main application.
 * @retval  None
 */
void Boot_start_app(void)
{
    /* Setup location of application start address */
    uint32_t *app_code = (uint32_t *)&__rom_app_start__;

    /* Extract location of SP and reset handler */
    uint32_t app_sp = app_code[0];
    uint32_t app_start = app_code[1];

    /* Jump into application reset handler */
    start_app(app_start, app_sp);

    /* Not Reached */
    while (1) {}
}

/* EOF */