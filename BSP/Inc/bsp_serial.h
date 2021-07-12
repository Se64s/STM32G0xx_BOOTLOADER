/**
 * @file    bsp_serial.h
 * @author  Sebastián Del Moral (sebmorgal@gmail.com)
 * @brief   System support packet to handle serial interfaces using low level features.
 * @version 0.1
 * @date    2020-09-27
 * 
 * @copyright Copyright (c) 2020
 * 
 */

/* Define to prevent recursive inclusion ------------------------------------*/
#ifndef __BSP_SERIAL_H
#define __BSP_SERIAL_H

#ifdef __cplusplus
extern "C"
{
#endif

/* Exported includes --------------------------------------------------------*/
#include <stdint.h>

/* Exported defines ---------------------------------------------------------*/
/* Exported types -----------------------------------------------------------*/
/* Exported macro -----------------------------------------------------------*/
/* Exported functions prototypes --------------------------------------------*/

/**
 * @brief Init serial interface 0. BSP wrapper.
 * 
 */
void BSP_Serial0Init(void);

/**
 * @brief DeInit serial interface 0. BSP wrapper.
 * 
 */
void BSP_Serial0DeInit(void);

/**
 * @brief Send data over serial interface 0. BSP wrapper.
 * 
 * @param pu8buff buffer to send.
 * @param u32DataLen number of bytes to send.
 * @return uint32_t number of bytes sent.
 */
uint32_t BSP_Serial0Write(uint8_t* pu8buff, uint32_t u32DataLen);

/**
 * @brief Read data over serial interface 0. BSP wrapper.
 * 
 * @param buf buffer to where place read datasend
 * @param max number of bytes to read.
 * @return number of bytes copied into buff
 */
uint32_t BSP_Serial0Read(uint8_t* pu8buff, uint32_t u32DataMaxLen);

/**
 * @brief Get number of bytes in buffer
 * 
 * @return uint32_t number of bytes in buffer
 */
uint32_t BSP_Serial0GetRxCount(void);

/**
 * @brief Handler of serial 0 irq. BSP wrapper.
 * 
 */
void BSP_Serial0IrqHandler(void);

#ifdef __cplusplus
}
#endif

#endif /* __BSP_SERIAL_H */

/*EOF*/