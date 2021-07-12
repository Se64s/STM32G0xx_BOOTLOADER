/**
 * @file    memory_shared.c
 * @author  Sebastián Del Moral Gallardo (sebmorgal@gmail.com).
 * @brief   Module to share data between bootloader and app.
 * @version 0.1
 * @date    2021-07-07
 * 
 * @copyright Copyright (c) 2021
 * 
 */

/* Includes ------------------------------------------------------------------*/
#include "memory_shared.h"

/* Private includes ----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/

/* Data structure with shared data */
#pragma pack (push)
typedef struct SharedData {
    uint32_t u32MagicInit;
    uint32_t u32BootFlags;
    uint8_t u8BootCount;
} SharedData_t;
#pragma pack (pop)

/* Private define ------------------------------------------------------------*/

/* Maximun number of boot counts to prevent overflow */
#define MAX_BOOT    ( 254U )

/* Magic value to detect write data */
#define MAGIC_VALUE ( 0xBEEFBABE )

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Start of shared data in RAM */
extern int __ram_share_start__;

/* Data structure with shared data */
SharedData_t *pxSharedData = (SharedData_t *)&__ram_share_start__;

/* Private function prototypes -----------------------------------------------*/
/* Private function ----------------------------------------------------------*/
/* Public function -----------------------------------------------------------*/

void shared_init_struct(void)
{
    if ( pxSharedData->u32MagicInit != MAGIC_VALUE )
    {
        pxSharedData->u32MagicInit = MAGIC_VALUE;
        pxSharedData->u32BootFlags = 0U;
        pxSharedData->u8BootCount = 0U;
    }
}

uint8_t shared_get_boot_count(void)
{
    return pxSharedData->u8BootCount;
}

void shared_increment_boot_count(void)
{
    if ( pxSharedData->u8BootCount < MAX_BOOT)
    {
        pxSharedData->u8BootCount++;
    }
}

void shared_reset_boot_count(void)
{
    pxSharedData->u8BootCount = 0U;
}

void shared_set_boot_flag(eMemShareBootFlags_t eFlag)
{
    if ( eFlag == SHARE_BOOT_FLAG_ALL )
    {
        pxSharedData->u32BootFlags = 0xFFFFFFFF;
    }
    else if ( eFlag < SHARE_BOOT_FLAG_ALL )
    {
        pxSharedData->u32BootFlags |= ( 1U << (uint32_t)eFlag );
    }
}

void shared_reset_boot_flag(eMemShareBootFlags_t eFlag)
{
    if ( eFlag == SHARE_BOOT_FLAG_ALL )
    {
        pxSharedData->u32BootFlags = 0U;
    }
    else if ( eFlag < SHARE_BOOT_FLAG_ALL )
    {
        pxSharedData->u32BootFlags &= ~( 1U << (uint32_t)eFlag );
    }
}

bool shared_get_boot_flag(eMemShareBootFlags_t eFlag)
{
    bool bFlagValue = false;

    if ( eFlag < SHARE_BOOT_FLAG_ALL )
    {
        uint32_t u32FlagMask = ( 1U << (uint32_t)eFlag );

        bFlagValue = (pxSharedData->u32BootFlags & u32FlagMask) == u32FlagMask;
    }

    return bFlagValue;
}

uint32_t shared_get_boot_flags(void)
{
    return pxSharedData->u32BootFlags;
}

/* EOF */