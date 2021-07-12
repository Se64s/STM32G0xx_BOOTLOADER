/**
 * @file    sys_ll_serial.h
 * @author  Sebastián Del Moral (sebmorgal@gmail.com)
 * @brief   System support packet to handle serial interfaces using low level features.
 * @version 0.1
 * @date    2020-09-27
 * 
 * @copyright Copyright (c) 2020
 * 
 */

/* Define to prevent recursive inclusion ------------------------------------*/
#ifndef __SYS_LL_SERIAL_H
#define __SYS_LL_SERIAL_H

#ifdef __cplusplus
extern "C"
{
#endif

/* Exported includes --------------------------------------------------------*/

#include "sys_def.h"

/* Exported defines ---------------------------------------------------------*/
/* Exported types -----------------------------------------------------------*/

/** List of serial devices*/
typedef enum
{
    SYS_LL_SERIAL_0 = 0U,
    SYS_LL_SERIAL_MAX_DEV,
} sys_ll_serial_port_t;

/* Exported macro -----------------------------------------------------------*/
/* Exported functions prototypes --------------------------------------------*/

/**
 * @brief Init low level uart.
 * 
 * @param dev defined serial interface.
 * @return sys_ll_serial_status_t operation status, SYS_LL_SERIAL_STATUS_OK (success)
 *         SYS_LL_SERIAL_STATUS_ERROR (error).
 */
sys_status_t SYS_LL_SerialInit(sys_ll_serial_port_t dev);

/**
 * @brief De-init low level uart.
 * 
 * @param dev defined serial interface.
 * @return sys_status_t operation status, SYS_LL_SERIAL_STATUS_OK (success)
 *         SYS_LL_SERIAL_STATUS_ERROR (error).
 */
sys_status_t SYS_LL_SerialDeInit(sys_ll_serial_port_t dev);

/**
 * @brief Blocking send action over defined serial interface
 * 
 * @param dev defined serial interface
 * @param buf buffer data to send
 * @param len number of bytes to send
 * @return number of bytes sent.
 */
uint32_t SYS_LL_SerialSend(sys_ll_serial_port_t dev, uint8_t* buf, uint8_t len);

/**
 * @brief Read serial buffer.
 * 
 * @param dev serial interface id to read.
 * @param buf buffer where place data read.
 * @param len max number of bytes to read.
 * @return number of bytes read.
 */
uint32_t SYS_LL_SerialRead(sys_ll_serial_port_t dev, uint8_t* buf, uint32_t len);

/**
 * @brief Gat number of bytes in reception buffer
 * 
 * @param dev serial interface id to read.
 * @return uint32_t Number of bytes in buffer.
 */
uint32_t SYS_LL_SerialGetRxCount(sys_ll_serial_port_t dev);

#ifdef __cplusplus
}
#endif

#endif /* __SYS_LL_SERIAL_H */

/* EOF */