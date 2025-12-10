/*
 * GENERATED FILE - DO NOT EDIT
 * Copyright 2008-2013 Code Red Technologies Ltd,
 * Copyright 2013-2025 NXP
 * SPDX-License-Identifier: BSD-3-Clause
 * Generated linker script file for RW612
 * Created from linkscript.ldt by FMCreateLinkLibraries
 * Using Freemarker v2.3.30
 * MCUXpresso IDE v25.6 [Build 136] [2025-06-27] on 10-Dec-2025, 11:13:08 am
 */

INCLUDE "bluetooth_Debug_library.ld"
INCLUDE "bluetooth_Debug_memory.ld"

ENTRY(ResetISR)

SECTIONS
{
     .text_Flash2 : ALIGN(4)
    {
       FILL(0xff)
        *(.text_Flash2) /* for compatibility with previous releases */
        *(.text_LITTLEFS_FLASH_region) /* for compatibility with previous releases */
        *(.text.$Flash2)
        *(.text.$LITTLEFS_FLASH_region)
        *(.text_Flash2.*) /* for compatibility with previous releases */
        *(.text_LITTLEFS_FLASH_region.*) /* for compatibility with previous releases */
        *(.text.$Flash2.*)
        *(.text.$LITTLEFS_FLASH_region.*)
        *(.rodata.$Flash2)
        *(.rodata.$LITTLEFS_FLASH_region)
        *(.rodata.$Flash2.*)
        *(.rodata.$LITTLEFS_FLASH_region.*)            } > LITTLEFS_FLASH_region

    /* Offset .text by 0x1000 bytes, which whill be added by the image tool*/
    .boot_hdr : ALIGN(4)
    {
        FILL(0xFF)
        . = 0x400;
        __FLASH_BASE = .;
        KEEP(*(.flash_conf))
        . = 0x1000;
    } > BOARD_FLASH

    /* MAIN TEXT SECTION */
    .text : ALIGN(4)
    {
        FILL(0xff)
        __vectors_start__ = ABSOLUTE(.) ;
        KEEP(*(.isr_vector))
        /* Global Section Table */
        . = ALIGN(4) ;
        __section_table_start = .;
        __data_section_table = .;
        LONG(LOADADDR(.data));
        LONG(    ADDR(.data));
        LONG(  SIZEOF(.data));
        LONG(LOADADDR(.data_RAM2));
        LONG(    ADDR(.data_RAM2));
        LONG(  SIZEOF(.data_RAM2));
        LONG(LOADADDR(.data_RAM3));
        LONG(    ADDR(.data_RAM3));
        LONG(  SIZEOF(.data_RAM3));
        LONG(LOADADDR(.data_RAM4));
        LONG(    ADDR(.data_RAM4));
        LONG(  SIZEOF(.data_RAM4));
        LONG(LOADADDR(.data_RAM5));
        LONG(    ADDR(.data_RAM5));
        LONG(  SIZEOF(.data_RAM5));
        LONG(LOADADDR(.data_RAM6));
        LONG(    ADDR(.data_RAM6));
        LONG(  SIZEOF(.data_RAM6));
        __data_section_table_end = .;
        __bss_section_table = .;
        LONG(    ADDR(.bss));
        LONG(  SIZEOF(.bss));
        LONG(    ADDR(.bss_RAM2));
        LONG(  SIZEOF(.bss_RAM2));
        LONG(    ADDR(.bss_RAM3));
        LONG(  SIZEOF(.bss_RAM3));
        LONG(    ADDR(.bss_RAM4));
        LONG(  SIZEOF(.bss_RAM4));
        LONG(    ADDR(.bss_RAM5));
        LONG(  SIZEOF(.bss_RAM5));
        LONG(    ADDR(.bss_RAM6));
        LONG(  SIZEOF(.bss_RAM6));
        __bss_section_table_end = .;
        __section_table_end = . ;
        /* End of Global Section Table */

        *(.after_vectors*)

*(EXCLUDE_FILE(*fsl_adapter_flexspi_nor_flash.o *fsl_flexspi.o *mflash_drv.o) .text*)       KEEP(*freertos*/tasks.o(.rodata*)) /* FreeRTOS Debug Config */
       *(.rodata .rodata.* .constdata .constdata.*)
       . = ALIGN(4);
    } > BOARD_FLASH
    /*
     * for exception handling/unwind - some Newlib functions (in common
     * with C++ and STDC++) use this.
     */
    .ARM.extab : ALIGN(4)
    {
        *(.ARM.extab* .gnu.linkonce.armextab.*)
    } > BOARD_FLASH

    .ARM.exidx : ALIGN(4)
    {
        __exidx_start = .;
        *(.ARM.exidx* .gnu.linkonce.armexidx.*)
        __exidx_end = .;
    } > BOARD_FLASH
 

  ._bt_settings_area :
  {
    . = ALIGN(4);
    _bt_settings_start = .;
    KEEP(*(SORT(._bt_settings.static.*)))
    _bt_settings_end = .;
    . = ALIGN(4);
  } > BOARD_FLASH

  ._settings_handler_static :
  {
    . = ALIGN(4);
    _settings_handler_static_list_start = .;
    KEEP(*(SORT(._settings_handler_static.static.*)))
    _settings_handler_static_list_end = .;
    . = ALIGN(4);
  } > BOARD_FLASH

  ._bt_conn_cb :
  {
    . = ALIGN(4);
    _bt_conn_cb_list_start = .;
    KEEP(*(SORT(._bt_conn_cb.static.*)))
    _bt_conn_cb_list_end = .;
    . = ALIGN(4);
  } > BOARD_FLASH

  ._bt_ias_cb :
  {
    . = ALIGN(4);
    _bt_ias_cb_list_start = .;
    KEEP(*(SORT(._bt_ias_cb.static.*)))
    _bt_ias_cb_list_end = .;
    . = ALIGN(4);
  } > BOARD_FLASH

  ._bt_gatt_service_static :
  {
    . = ALIGN(4);
    _bt_gatt_service_static_list_start = .;
    KEEP(*(SORT(._bt_gatt_service_static.static.*)))
    _bt_gatt_service_static_list_end = .;
    . = ALIGN(4);
  } > BOARD_FLASH

  ._bt_l2cap_fixed_chan :
  {
    . = ALIGN(4);
    _bt_l2cap_fixed_chan_list_start = .;
    KEEP(*(SORT(._bt_l2cap_fixed_chan.static.*)))
    _bt_l2cap_fixed_chan_list_end = .;
    . = ALIGN(4);
  } > BOARD_FLASH

  ._bt_l2cap_br_fixed_chan :
  {
    . = ALIGN(4);
    _bt_l2cap_br_fixed_chan_list_start = .;
    KEEP(*(SORT(._bt_l2cap_br_fixed_chan.static.*)))
    _bt_l2cap_br_fixed_chan_list_end = .;
    . = ALIGN(4);
  } > BOARD_FLASH

    _etext = .;

  .LITTLEFS_FLASH_region :
  {
    . = ORIGIN(LITTLEFS_FLASH_region) + LENGTH(LITTLEFS_FLASH_region) - 1;
  } > LITTLEFS_FLASH_region


    /* Reserve and place Stack within memory map */
    _StackSize = 0x1000;
    .stack (NOLOAD) :  ALIGN(4)
    {
        _vStackBase = .;
        . += _StackSize;
        . = ALIGN(4);
        _vStackTop = .;
    } > SRAM
    /* DATA section for m_mbox13 */

    .data_RAM2 : ALIGN(4)
    {
        FILL(0xff)
        PROVIDE(__start_data_RAM2 = .) ;
        PROVIDE(__start_data_m_mbox13 = .) ;
        *(.ramfunc.$RAM2)
        *(.ramfunc.$m_mbox13)
        *(.data.$RAM2)
        *(.data.$m_mbox13)
        *(.data.$RAM2.*)
        *(.data.$m_mbox13.*)
        . = ALIGN(4) ;
        PROVIDE(__end_data_RAM2 = .) ;
        PROVIDE(__end_data_m_mbox13 = .) ;
     } > m_mbox13 AT>BOARD_FLASH

    /* DATA section for m_txq31 */

    .data_RAM3 : ALIGN(4)
    {
        FILL(0xff)
        PROVIDE(__start_data_RAM3 = .) ;
        PROVIDE(__start_data_m_txq31 = .) ;
        *(.ramfunc.$RAM3)
        *(.ramfunc.$m_txq31)
        *(.data.$RAM3)
        *(.data.$m_txq31)
        *(.data.$RAM3.*)
        *(.data.$m_txq31.*)
        . = ALIGN(4) ;
        PROVIDE(__end_data_RAM3 = .) ;
        PROVIDE(__end_data_m_txq31 = .) ;
     } > m_txq31 AT>BOARD_FLASH

    /* DATA section for m_mbox23 */

    .data_RAM4 : ALIGN(4)
    {
        FILL(0xff)
        PROVIDE(__start_data_RAM4 = .) ;
        PROVIDE(__start_data_m_mbox23 = .) ;
        *(.ramfunc.$RAM4)
        *(.ramfunc.$m_mbox23)
        *(.data.$RAM4)
        *(.data.$m_mbox23)
        *(.data.$RAM4.*)
        *(.data.$m_mbox23.*)
        . = ALIGN(4) ;
        PROVIDE(__end_data_RAM4 = .) ;
        PROVIDE(__end_data_m_mbox23 = .) ;
     } > m_mbox23 AT>BOARD_FLASH

    /* DATA section for m_txq23 */

    .data_RAM5 : ALIGN(4)
    {
        FILL(0xff)
        PROVIDE(__start_data_RAM5 = .) ;
        PROVIDE(__start_data_m_txq23 = .) ;
        *(.ramfunc.$RAM5)
        *(.ramfunc.$m_txq23)
        *(.data.$RAM5)
        *(.data.$m_txq23)
        *(.data.$RAM5.*)
        *(.data.$m_txq23.*)
        . = ALIGN(4) ;
        PROVIDE(__end_data_RAM5 = .) ;
        PROVIDE(__end_data_m_txq23 = .) ;
     } > m_txq23 AT>BOARD_FLASH

    /* DATA section for m_txq32 */

    .data_RAM6 : ALIGN(4)
    {
        FILL(0xff)
        PROVIDE(__start_data_RAM6 = .) ;
        PROVIDE(__start_data_m_txq32 = .) ;
        *(.ramfunc.$RAM6)
        *(.ramfunc.$m_txq32)
        *(.data.$RAM6)
        *(.data.$m_txq32)
        *(.data.$RAM6.*)
        *(.data.$m_txq32.*)
        . = ALIGN(4) ;
        PROVIDE(__end_data_RAM6 = .) ;
        PROVIDE(__end_data_m_txq32 = .) ;
     } > m_txq32 AT>BOARD_FLASH

    /* MAIN DATA SECTION */
    .uninit_RESERVED (NOLOAD) : ALIGN(4)
    {
        _start_uninit_RESERVED = .;
        KEEP(*(.bss.$RESERVED*))
       . = ALIGN(4) ;
        _end_uninit_RESERVED = .;
    } > SRAM AT> SRAM

    /* Main DATA section (SRAM) */
    .data : ALIGN(4)
    {
       FILL(0xff)
       _data = . ;
       PROVIDE(__start_data_RAM = .) ;
       PROVIDE(__start_data_SRAM = .) ;
       *(vtable)
       *(.ramfunc*)
       KEEP(*(CodeQuickAccess))
       KEEP(*(DataQuickAccess))
       *(RamFunction)
        
        *fsl_adapter_flexspi_nor_flash.o(.text*)
        *fsl_flexspi.o(.text*)
        *mflash_drv.o(.text*)
        *(.data*)
        . = ALIGN(4);
        _net_buf_pool_list_start = .;
        KEEP(*(SORT(._net_buf_pool*)))
        _net_buf_pool_list_end = .;
        . = ALIGN(4);
        _k_mem_slab_list_start = .;
        KEEP(*(SORT(._k_mem_slab*)))
        _k_mem_slab_list_end = .;
        . = ALIGN(4);
       . = ALIGN(4) ;
       _edata = . ;
       PROVIDE(__end_data_RAM = .) ;
       PROVIDE(__end_data_SRAM = .) ;
    } > SRAM AT>BOARD_FLASH

    /* BSS section for m_mbox13 */
    .bss_RAM2 (NOLOAD) : ALIGN(4)
    {
       PROVIDE(__start_bss_RAM2 = .) ;
       PROVIDE(__start_bss_m_mbox13 = .) ;
       *(.bss.$RAM2)
       *(.bss.$m_mbox13)
       *(.bss.$RAM2.*)
       *(.bss.$m_mbox13.*)
       . = ALIGN (. != 0 ? 4 : 1) ; /* avoid empty segment */
       PROVIDE(__end_bss_RAM2 = .) ;
       PROVIDE(__end_bss_m_mbox13 = .) ;
    } > m_mbox13 AT> m_mbox13

    /* BSS section for m_txq31 */
    .bss_RAM3 (NOLOAD) : ALIGN(4)
    {
       PROVIDE(__start_bss_RAM3 = .) ;
       PROVIDE(__start_bss_m_txq31 = .) ;
       *(.bss.$RAM3)
       *(.bss.$m_txq31)
       *(.bss.$RAM3.*)
       *(.bss.$m_txq31.*)
       . = ALIGN (. != 0 ? 4 : 1) ; /* avoid empty segment */
       PROVIDE(__end_bss_RAM3 = .) ;
       PROVIDE(__end_bss_m_txq31 = .) ;
    } > m_txq31 AT> m_txq31

    /* BSS section for m_mbox23 */
    .bss_RAM4 (NOLOAD) : ALIGN(4)
    {
       PROVIDE(__start_bss_RAM4 = .) ;
       PROVIDE(__start_bss_m_mbox23 = .) ;
       *(.bss.$RAM4)
       *(.bss.$m_mbox23)
       *(.bss.$RAM4.*)
       *(.bss.$m_mbox23.*)
       . = ALIGN (. != 0 ? 4 : 1) ; /* avoid empty segment */
       PROVIDE(__end_bss_RAM4 = .) ;
       PROVIDE(__end_bss_m_mbox23 = .) ;
    } > m_mbox23 AT> m_mbox23

    /* BSS section for m_txq23 */
    .bss_RAM5 (NOLOAD) : ALIGN(4)
    {
       PROVIDE(__start_bss_RAM5 = .) ;
       PROVIDE(__start_bss_m_txq23 = .) ;
       *(.bss.$RAM5)
       *(.bss.$m_txq23)
       *(.bss.$RAM5.*)
       *(.bss.$m_txq23.*)
       . = ALIGN (. != 0 ? 4 : 1) ; /* avoid empty segment */
       PROVIDE(__end_bss_RAM5 = .) ;
       PROVIDE(__end_bss_m_txq23 = .) ;
    } > m_txq23 AT> m_txq23

    /* BSS section for m_txq32 */
    .bss_RAM6 (NOLOAD) : ALIGN(4)
    {
       PROVIDE(__start_bss_RAM6 = .) ;
       PROVIDE(__start_bss_m_txq32 = .) ;
       *(.bss.$RAM6)
       *(.bss.$m_txq32)
       *(.bss.$RAM6.*)
       *(.bss.$m_txq32.*)
       . = ALIGN (. != 0 ? 4 : 1) ; /* avoid empty segment */
       PROVIDE(__end_bss_RAM6 = .) ;
       PROVIDE(__end_bss_m_txq32 = .) ;
    } > m_txq32 AT> m_txq32

    /* MAIN BSS SECTION */
    .bss (NOLOAD) : ALIGN(4)
    {
        _bss = .;
        PROVIDE(__start_bss_RAM = .) ;
        PROVIDE(__start_bss_SRAM = .) ;
        *(.bss*)
        *(COMMON)
        . = ALIGN(4) ;
        _ebss = .;
        PROVIDE(__end_bss_RAM = .) ;
        PROVIDE(__end_bss_SRAM = .) ;
        PROVIDE(end = .);
    } > SRAM AT> SRAM

    /* NOINIT section for m_mbox13 */
    .noinit_RAM2 (NOLOAD) : ALIGN(4)
    {
       PROVIDE(__start_noinit_RAM2 = .) ;
       PROVIDE(__start_noinit_m_mbox13 = .) ;
       *(.smu_cpu13_mbox)
       *(.noinit.$RAM2)
       *(.noinit.$m_mbox13)
       *(.noinit.$RAM2.*)
       *(.noinit.$m_mbox13.*)
       . = ALIGN(4) ;
       PROVIDE(__end_noinit_RAM2 = .) ;
       PROVIDE(__end_noinit_m_mbox13 = .) ;
    } > m_mbox13 AT> m_mbox13

    /* NOINIT section for m_txq31 */
    .noinit_RAM3 (NOLOAD) : ALIGN(4)
    {
       PROVIDE(__start_noinit_RAM3 = .) ;
       PROVIDE(__start_noinit_m_txq31 = .) ;
       *(.smu_cpu31_txq)
       *(.noinit.$RAM3)
       *(.noinit.$m_txq31)
       *(.noinit.$RAM3.*)
       *(.noinit.$m_txq31.*)
       . = ALIGN(4) ;
       PROVIDE(__end_noinit_RAM3 = .) ;
       PROVIDE(__end_noinit_m_txq31 = .) ;
    } > m_txq31 AT> m_txq31

    /* NOINIT section for m_mbox23 */
    .noinit_RAM4 (NOLOAD) : ALIGN(4)
    {
       PROVIDE(__start_noinit_RAM4 = .) ;
       PROVIDE(__start_noinit_m_mbox23 = .) ;
       *(.smu_cpu23_mbox)
       *(.noinit.$RAM4)
       *(.noinit.$m_mbox23)
       *(.noinit.$RAM4.*)
       *(.noinit.$m_mbox23.*)
       . = ALIGN(4) ;
       PROVIDE(__end_noinit_RAM4 = .) ;
       PROVIDE(__end_noinit_m_mbox23 = .) ;
    } > m_mbox23 AT> m_mbox23

    /* NOINIT section for m_txq23 */
    .noinit_RAM5 (NOLOAD) : ALIGN(4)
    {
       PROVIDE(__start_noinit_RAM5 = .) ;
       PROVIDE(__start_noinit_m_txq23 = .) ;
       *(.noinit.$RAM5)
       *(.noinit.$m_txq23)
       *(.noinit.$RAM5.*)
       *(.noinit.$m_txq23.*)
       . = ALIGN(4) ;
       PROVIDE(__end_noinit_RAM5 = .) ;
       PROVIDE(__end_noinit_m_txq23 = .) ;
    } > m_txq23 AT> m_txq23

    /* NOINIT section for m_txq32 */
    .noinit_RAM6 (NOLOAD) : ALIGN(4)
    {
       PROVIDE(__start_noinit_RAM6 = .) ;
       PROVIDE(__start_noinit_m_txq32 = .) ;
       *(.smu_cpu32_txq)
       *(.noinit.$RAM6)
       *(.noinit.$m_txq32)
       *(.noinit.$RAM6.*)
       *(.noinit.$m_txq32.*)
       . = ALIGN(4) ;
       PROVIDE(__end_noinit_RAM6 = .) ;
       PROVIDE(__end_noinit_m_txq32 = .) ;
    } > m_txq32 AT> m_txq32

    /* DEFAULT NOINIT SECTION */
    .noinit (NOLOAD): ALIGN(4)
    {
        _noinit = .;
        PROVIDE(__start_noinit_RAM = .) ;
        PROVIDE(__start_noinit_SRAM = .) ;
        *(.noinit*)
         . = ALIGN(4) ;
        _end_noinit = .;
       PROVIDE(__end_noinit_RAM = .) ;
       PROVIDE(__end_noinit_SRAM = .) ;        
    } > SRAM AT> SRAM

    /* Reserve and place Heap within memory map */
    _HeapSize = 0x1000;
    .heap (NOLOAD) :  ALIGN(4)
    {
        _pvHeapStart = .;
        . += _HeapSize;
        . = ALIGN(4);
        _pvHeapLimit = .;
    } > SRAM

    /* Provide basic symbols giving location and size of main text
     * block, including initial values of RW data sections. Note that
     * these will need extending to give a complete picture with
     * complex images (e.g multiple Flash banks).
     */
    _image_start = LOADADDR(.text);
    _image_end = LOADADDR(.data) + SIZEOF(.data);
    _image_size = _image_end - _image_start;


    /*** littleFS configuration Start ***/
    EDGEFAST_BT_LITTLEFS_STORAGE_START_ADDRESS = __base_LITTLEFS_FLASH_region;
    EDGEFAST_BT_LITTLEFS_STORAGE_SECTOR_SIZE = 0x1000;  /* 4k flash sector size */
    EDGEFAST_BT_LITTLEFS_STORAGE_MAX_SECTORS = (__top_LITTLEFS_FLASH_region - EDGEFAST_BT_LITTLEFS_STORAGE_START_ADDRESS) / EDGEFAST_BT_LITTLEFS_STORAGE_SECTOR_SIZE;
    /*** littleFS configuration End ***/
}