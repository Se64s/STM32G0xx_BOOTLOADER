/*
******************************************************************************
**
**  File        : sys_memory_map.ld
**  Author      : Sebastián Del Moral Gallardo
**  Abstract    : Memory MAP definition to allocate app and bootloader
**
*****************************************************************************
*/

/* Specify the memory areas */
MEMORY
{
    RAM_SHARE   (xrw) : ORIGIN = 0x20000000, LENGTH = 2K
    RAM         (xrw) : ORIGIN = 0x20000800, LENGTH = 34K
    ROM_BOOT    (rx)  : ORIGIN = 0x8000000, LENGTH = 16K
    ROM_APP     (rx)  : ORIGIN = 0x8004000, LENGTH = 112K
}

/* Define memory areas */
/* __ram_share_start__ = ORIGIN(ROM_APP); */
__ram_share_size__ = LENGTH(RAM_SHARE);
__rom_boot_start__ = ORIGIN(ROM_BOOT);
__rom_boot_size__ = LENGTH(ROM_BOOT);
/* __rom_app_start__ = ORIGIN(ROM_APP); */
__rom_app_size__ = LENGTH(ROM_APP);

/* Define sections */
SECTIONS
{
    /* Create a symbol with the start of the application block */
    ._app_code ORIGIN(ROM_APP) (NOLOAD) :
    {
        __rom_app_start__ = .;
    } > ROM_APP

    /* Define area for share data */
    ._share_data ORIGIN(RAM_SHARE) (NOLOAD) :
    {
        __ram_share_start__ = .;
    } > RAM_SHARE
}

/* EOF */