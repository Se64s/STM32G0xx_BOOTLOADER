/**
  ******************************************************************************
  * @file           : main_app.c
  * @brief          : Main test application
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

#include <stdbool.h>
#include <stdint.h>

#include "sys_mcu.h"
#include "sys_ll_serial.h"
#include "sys_ll_gpio.h"

#include "printf.h"
#include "memory_shared.h"
#include "shell.h"

#include "user_error.h"

/* Private includes ----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

#define APP_TICK_CNT    ( 1000000U )

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

static void app_init_peripheral(void);
static int app_cli_send_chr_wrapper(char c);
static void app_cli_loop(void);
static bool app_init_share(void);

/* Private function definition -----------------------------------------------*/

/**
 * @brief Link for putchar used in printf implementation.
 * 
 * @param character character to send.
 */
void _putchar(char character)
{
    (void)SYS_LL_SerialSend(SYS_LL_SERIAL_0, (uint8_t *)&character, 1U);
}

/**
 * @brief Init system peripheral.
 * 
 */
static void app_init_peripheral(void)
{
    (void)SYS_LL_SerialInit(SYS_LL_SERIAL_0);
    SYS_LL_GpiolInit();

    printf("\r\n\r\n--- Init Application ---\r\n");
}

/**
 * @brief Wrapper send function used in shell implementation
 * 
 * @param c character to send.
 * @return int number of bytes to sent.
 */
static int app_cli_send_chr_wrapper(char c)
{
    uint8_t u8TxData = (uint8_t)c;
    return SYS_LL_SerialSend(SYS_LL_SERIAL_0, &u8TxData, 1U);
}

/**
 * @brief Main loop for CLI app.
 * 
 */
void app_cli_loop(void)
{
    /* Init shell */
    sShellImpl shell_impl = {
        .send_char = app_cli_send_chr_wrapper,
    };
    shell_boot(&shell_impl);

    /* Data consumer loop */
    uint8_t u8DataRx = 0;
    uint32_t u32TickCnt = 0U;
    uint32_t u32TickCountSecond = 0U;

    while (1U)
    {
        if ( SYS_LL_SerialRead(SYS_LL_SERIAL_0, &u8DataRx, 1U) != 0U )
        {
            char cDataRx = (char)u8DataRx;
            shell_receive_char(cDataRx);
        }
        else
        {
            u32TickCountSecond++;
        }

        if ( u32TickCountSecond == APP_TICK_CNT )
        {
            u32TickCountSecond = 0;
            printf("\r\nApp Tick: %d", u32TickCnt++);
        }
    }
}

/**
 * @brief Init and check RAM share data.
 * 
 * @return true   App image not validated.
 * @return false  App image not validated.
 */
static bool app_init_share(void)
{
    bool bRetval = true;

    printf("\r\nMark application as valid image");

    shared_set_boot_flag(SHARE_BOOT_FLAG_VALID_APP);

    return bRetval;
}

/* Private user code ---------------------------------------------------------*/

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
    /* Init flash, system clocks and user error interface */
    Sys_Mcu_Init();

    /* Initialize all configured peripherals */
    app_init_peripheral();

    /* Update Boot share data */
    if ( !app_init_share() )
    {
        ERR_ASSERT(0U);
    }

    /* Handle for CLI app */
    app_cli_loop();

    /* Not executed */
    while (1)
    {
    }
}

/* EOF */