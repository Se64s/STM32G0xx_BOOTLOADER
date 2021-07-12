/**
 * @file    memory_image.h
 * @author  Sebastián Del Moral Gallardo (sebmorgal@gmail.com).
 * @brief   Metadata for FW images.
 * @version 0.1
 * @date    2021-07-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef __MEMORY_IMAGE_H
#define __MEMORY_IMAGE_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>

/* Private includes ----------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/

typedef struct __attribute__((packed))
{
    uint16_t image_magic;
    uint16_t image_hdr_version;
    uint32_t crc;
    uint32_t data_size;
    uint8_t image_type;
    uint8_t version_major;
    uint8_t version_minor;
    uint8_t version_patch;
    uint32_t vector_addr;
    uint32_t reserved;
    char git_sha[8];
} image_hdr_t;

/* Exported macro ------------------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __MEMORY_IMAGE_H */

/* EOF */