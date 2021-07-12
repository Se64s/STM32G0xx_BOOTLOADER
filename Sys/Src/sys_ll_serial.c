/**
 * @file    sys_ll_serial.c
 * @author  Sebastián Del Moral (sebmorgal@gmail.com)
 * @brief   System support packet to handle low level serial interfaces
 * @version 0.1
 * @date    2020-09-27
 * 
 * @copyright Copyright (c) 2020
 * 
 */

/* Private includes --------------------------------------------------------*/

#include "sys_ll_serial.h"
#include "bsp_serial.h"
#include "user_error.h"

/* Private defines ---------------------------------------------------------*/
/* Private variable --------------------------------------------------------*/
/* Private macro -----------------------------------------------------------*/
/* Private functions prototypes --------------------------------------------*/
/* Private functions definition --------------------------------------------*/
/* Public function definition ----------------------------------------------*/

sys_status_t SYS_LL_SerialInit(sys_ll_serial_port_t dev)
{
    ERR_ASSERT(dev < SYS_LL_SERIAL_MAX_DEV);

    sys_status_t eRetval = SYS_STATUS_FAIL;

    if (dev == SYS_LL_SERIAL_0)
    {
        BSP_Serial0Init();
        eRetval = SYS_STATUS_OK;
    }

    return eRetval;
}

sys_status_t SYS_LL_SerialDeInit(sys_ll_serial_port_t dev)
{
    ERR_ASSERT(dev < SYS_LL_SERIAL_MAX_DEV);

    sys_status_t eRetval = SYS_STATUS_FAIL;

    if (dev == SYS_LL_SERIAL_0)
    {
        BSP_Serial0DeInit();
        eRetval = SYS_STATUS_OK;
    }

    return eRetval;
}

uint32_t SYS_LL_SerialSend(sys_ll_serial_port_t dev, uint8_t* buf, uint8_t len)
{
    ERR_ASSERT(dev < SYS_LL_SERIAL_MAX_DEV);

    uint32_t u32SendCount = 0U;

    if (dev == SYS_LL_SERIAL_0)
    {
        u32SendCount = BSP_Serial0Write(buf, len);
    }

    return u32SendCount;
}

uint32_t SYS_LL_SerialRead(sys_ll_serial_port_t dev, uint8_t* buf, uint32_t len)
{
    ERR_ASSERT(dev < SYS_LL_SERIAL_MAX_DEV);
    uint32_t u32BytesRx = 0U;

    if (dev == SYS_LL_SERIAL_0)
    {
        u32BytesRx = BSP_Serial0Read(buf, len);
    }

    return u32BytesRx;
}

uint32_t SYS_LL_SerialGetRxCount(sys_ll_serial_port_t dev)
{
    return BSP_Serial0GetRxCount();
}

/* EOF */