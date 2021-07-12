/**
  ******************************************************************************
  * @file           : main_boot.c
  * @brief          : Bootloader app body
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
#include "boot.h"

/* Private includes ----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

#define WAITING_CHR         '.'         /*!< Defined char to indicate waiting on CLI */
#define BREAK_CHR           'x'         /*!< Defined break character to enter into CLI mode */

#define INIT_DELAY_COUNT    ( 5U )      /*!< Number of seconds for break detection */
#define INIT_DELAY_1SEC     ( 1000U )   /*!< Number of ms of a second */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

static void app_init_peripheral(void);
static bool app_scan_break_chr(void);
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

    printf("\r\n\r\n--- Init Bootloader ---\r\n");
}

/**
 * @brief Clear input buffer searching for break character.
 * 
 * @return true Found breck character.
 * @return false cleared buffer without finding breack character.
 */
static bool app_scan_break_chr(void)
{
    uint8_t u8RxChr;
    uint32_t u32InitDelayCount = INIT_DELAY_COUNT;
    bool bRetval = false;

    printf("\r\nPress '%c' to init CLI", BREAK_CHR);

    /* Give some time to capture break chr*/
    while ( u32InitDelayCount-- )
    {
        Sys_Mcu_Delay(INIT_DELAY_1SEC);

        while ( SYS_LL_SerialRead(SYS_LL_SERIAL_0, &u8RxChr, 1U) != 0U )
        {
            if ( u8RxChr == BREAK_CHR )
            {
                bRetval = true;
            }
        }

        if ( bRetval )
        {
            printf("\r\nBreak chr found, init CLI");
            break;
        }

        printf("%c", WAITING_CHR);
    }

    return bRetval;
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

    while (1U)
    {
        if ( SYS_LL_SerialRead(SYS_LL_SERIAL_0, &u8DataRx, 1U) != 0U )
        {
            char cDataRx = (char)u8DataRx;
            shell_receive_char(cDataRx);
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

    shared_init_struct();
    shared_increment_boot_count();

    uint8_t u8BootCount = shared_get_boot_count();
    uint32_t u32BootFlags = shared_get_boot_flags();

    printf("\r\nRAM Share Data:", u8BootCount);
    printf("\r\n - Boot count: %d", u8BootCount);
    printf("\r\n - Boot Status flags: 0x%08X", u32BootFlags);

    if ( (u8BootCount > SHARE_MAX_BOOT_COUNT) && !shared_get_boot_flag(SHARE_BOOT_FLAG_VALID_APP) )
    {
        printf("\r\nApplication Image not stable, wait in CLI mode");
        bRetval = false;
    }

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

    /* Update boot counter */
    if ( app_init_share() )
    {
        /* Scan input buffer for break character */
        if ( !app_scan_break_chr() )
        {
            Boot_start_app();
        }
    }

    /* Handle for CLI app */
    app_cli_loop();

    /* Not executed */
    while (1)
    {
    }
}

/* EOF */