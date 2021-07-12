/**
 * @file    shell_usr_cmd.c
 * @author  Sebastián Del Moral Gallardo (sebmorgal@gmail.com).
 * @brief   CLI commands defined for shell library.
 * @version 0.1
 * @date    2021-07-05
 * 
 * @copyright Copyright (c) 2021
 * 
 */

/* Private includes --------------------------------------------------------*/

#include "shell.h"

#include <stddef.h>
#include <stdlib.h>

#include "memory_shared.h"
#include "boot.h"
#include "sys_mcu.h"

/* Private defines ---------------------------------------------------------*/

/* Fix respose strings */
#define STR_MSG_OK              "> OK"
#define STR_MSG_PARAM_ERROR     "> FAIL, 1"

#define MAX_SIZE_RET_STR        ( 16U )

/* Private typedef ---------------------------------------------------------*/

/* Defined shell retrun codes */
typedef enum 
{
    SHELL_RET_OK = 0x00,
    SHELL_RET_PARAM_ERROR = 0x01,
    SHELL_RET_NUM_RET_CODES
} eShellRetunrCode_t;

/* Private macro -----------------------------------------------------------*/

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

/* Private functions prototypes --------------------------------------------*/

int cli_cmd_jump_app(int argc, char *argv[]);
int cli_cmd_reset(int argc, char *argv[]);
int cli_cmd_read_boot_count(int argc, char *argv[]);
int cli_cmd_clear_boot_count(int argc, char *argv[]);

/* Private variable --------------------------------------------------------*/

/* List of commands implemented */
static const sShellCommand s_shell_commands[] = {
    { "jump_app", cli_cmd_jump_app, "Jump into application code" },
    { "reset", cli_cmd_reset, "Reset device" },
    { "read_boot_count", cli_cmd_read_boot_count, "Read boot counter" },
    { "clear_boot_count", cli_cmd_clear_boot_count, "Clear boot counter" },
    { "help", shell_help_handler, "Lists all commands" },
};

const sShellCommand *const g_shell_commands = s_shell_commands;

/* Number of commands used */
const size_t g_num_shell_commands = ARRAY_SIZE(s_shell_commands);

/* Private functions definition --------------------------------------------*/

/**
 * @brief Jump execution to main app
 * 
 * @param argc Number of arguments
 * @param argv List of arguments
 * @return int Status:  0, OK
 *                      !0, ERROR
 */
int cli_cmd_jump_app(int argc, char *argv[])
{
    int iRetCode = (int)SHELL_RET_OK;

    if ( argc != 1U )
    {
        shell_put_line(STR_MSG_PARAM_ERROR);
        iRetCode = SHELL_RET_PARAM_ERROR;
    }
    else
    {
        shell_put_line(STR_MSG_OK);
        Boot_start_app();
    }

    return iRetCode;
}

/**
 * @brief Force reset.
 * 
 * @param argc Number of arguments
 * @param argv List of arguments
 * @return int Status:  0, OK
 *                      !0, ERROR
 */
int cli_cmd_reset(int argc, char *argv[])
{
    int iRetCode = (int)SHELL_RET_OK;

    if ( argc != 1U )
    {
        shell_put_line(STR_MSG_PARAM_ERROR);
        iRetCode = SHELL_RET_PARAM_ERROR;
    }
    else
    {
        shell_put_line(STR_MSG_OK);
        Sys_Mcu_Reset();
    }

    return iRetCode;
}

/**
 * @brief Show boot counter.
 * 
 * @param argc Number of arguments
 * @param argv List of arguments
 * @return int return code
 */
int cli_cmd_read_boot_count(int argc, char *argv[])
{
    int iRetCode = (int)SHELL_RET_OK;

    if ( argc != 1U )
    {
        shell_put_line(STR_MSG_PARAM_ERROR);
        iRetCode = SHELL_RET_PARAM_ERROR;
    }
    else
    {
        char cRetStr[MAX_SIZE_RET_STR] = { 0U };
        uint8_t u8BootCount = shared_get_boot_count();

        (void)itoa(u8BootCount, cRetStr, 10U);

        shell_put_line(cRetStr);

        shell_put_line(STR_MSG_OK);
    }

    return iRetCode;
}

/**
 * @brief Clear boot counter.
 * 
 * @param argc Number of arguments
 * @param argv List of arguments
 * @return int return code
 */
int cli_cmd_clear_boot_count(int argc, char *argv[])
{
    int iRetCode = (int)SHELL_RET_OK;

    if ( argc != 1U )
    {
        shell_put_line(STR_MSG_PARAM_ERROR);
        iRetCode = SHELL_RET_PARAM_ERROR;
    }
    else
    {
        shell_put_line(STR_MSG_OK);
        shared_reset_boot_count();
    }

    return iRetCode;
}

/* Public definition -------------------------------------------------------*/

/* EOF */