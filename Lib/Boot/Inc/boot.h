/**
 * @file    boot.h
 * @author  Sebastián Del Moral (sebmorgal@gmail.com)
 * @brief   Set of functions to handle bootloader execution jumps.
 * @version 0.1
 * @date    2021-07-01
 * 
 * @copyright Copyright (c) 2021
 * 
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BOOT_H
#define __BOOT_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <inttypes.h>

/* Private includes ----------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------------*/

void Boot_start_app(void);

#ifdef __cplusplus
}
#endif

#endif /* __BOOT_H */

/* EOF */