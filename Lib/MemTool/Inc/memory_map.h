/**
 * @file    memory_map.h
 * @author  Sebastián Del Moral (sebmorgal@gmail.com)
 * @brief   Linker address for app referencing.
 * @version 0.1
 * @date    2021-06-30
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef __MEMORY_MAP_H
#define __MEMORY_MAP_H

extern int __rom_boot_start__;  /*!< Bootloader start address */
extern int __rom_boot_size__;   /*!< Size available for bootloader */

extern int __rom_app_start__;   /*!< Application start address */
extern int __rom_app_size__;    /*!< Size available for app */

#endif /* __MEMORY_MAP_H */

/* EOF */