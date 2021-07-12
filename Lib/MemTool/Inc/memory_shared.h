/**
 * @file    memory_shared.h
 * @author  Sebastián Del Moral Gallardo (sebmorgal@gmail.com).
 * @brief   Module to share data between bootloader and app.
 * @version 0.1
 * @date    2021-07-07
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef __MEMORY_SHARED_H
#define __MEMORY_SHARED_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>

/* Private includes ----------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/

/** Defined Bootloader status flags */
typedef enum {
    SHARE_BOOT_FLAG_VALID_APP = 0U,   /*!< Flag to indicate that application image is valid */
    SHARE_BOOT_FLAG_ALL = 32U         /*!< All flags */
} eMemShareBootFlags_t;

/* Exported constants --------------------------------------------------------*/

#define SHARE_MAX_BOOT_COUNT    ( 10U ) /*!< Maximun number of boots without validate image */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------------*/

/**
 * @brief Check for initial magic number int shared RAM.
 * 
 */
void shared_init_struct(void);

/**
 * @brief   Get current boot counter.
 * 
 * @return uint8_t boot counter value (0-254).
 */
uint8_t shared_get_boot_count(void);

/**
 * @brief   Increment boot counter, max value 254
 * 
 */
void shared_increment_boot_count(void);

/**
 * @brief   Reset boot counter to 0.
 * 
 */
void shared_reset_boot_count(void);

/**
 * @brief Set boot flag.
 * 
 * @param eFlag flag to set.
 */
void shared_set_boot_flag(eMemShareBootFlags_t eFlag);

/**
 * @brief Reset boot flag.
 * 
 * @param eFlag flag to reset.
 */
void shared_reset_boot_flag(eMemShareBootFlags_t eFlag);

/**
 * @brief Get boot flag
 * 
 * @param eFlag flag to get.
 */
bool shared_get_boot_flag(eMemShareBootFlags_t eFlag);

/**
 * @brief Get boot all boot flags
 * 
 */
uint32_t shared_get_boot_flags(void);

#ifdef __cplusplus
}
#endif

#endif /* __MEMORY_SHARED_H */

/* EOF */