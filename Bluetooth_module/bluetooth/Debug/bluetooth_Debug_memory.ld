/*
 * GENERATED FILE - DO NOT EDIT
 * Copyright 2008-2013 Code Red Technologies Ltd,
 * Copyright 2013-2025 NXP
 * SPDX-License-Identifier: BSD-3-Clause
 * Generated linker script file for RW612
 * Created from memory.ldt by FMCreateLinkMemory
 * Using Freemarker v2.3.30
 * MCUXpresso IDE v25.6 [Build 136] [2025-06-27] on 10-Dec-2025, 11:13:08 am
 */

MEMORY
{
  /* Define each memory region */
  BOARD_FLASH (rx) : ORIGIN = 0x8000000, LENGTH = 0x200000 /* 2M bytes (alias Flash) */  
  LITTLEFS_FLASH_region (rx) : ORIGIN = 0xbe00000, LENGTH = 0x200000 /* 2M bytes (alias Flash2) */  
  SRAM (rwx) : ORIGIN = 0x20000000, LENGTH = 0x130000 /* 1216K bytes (alias RAM) */  
  m_mbox13 (rwx) : ORIGIN = 0x41380000, LENGTH = 0x488 /* 1160 bytes (alias RAM2) */  
  m_txq31 (rwx) : ORIGIN = 0x41380488, LENGTH = 0x1000 /* 4K bytes (alias RAM3) */  
  m_mbox23 (rwx) : ORIGIN = 0x443c0000, LENGTH = 0x488 /* 1160 bytes (alias RAM4) */  
  m_txq23 (rwx) : ORIGIN = 0x443c0488, LENGTH = 0x1080 /* 4224 bytes (alias RAM5) */  
  m_txq32 (rwx) : ORIGIN = 0x443c1508, LENGTH = 0x1080 /* 4224 bytes (alias RAM6) */  
}

  /* Define a symbol for the top of each memory region */
  __base_BOARD_FLASH = 0x8000000  ; /* BOARD_FLASH */  
  __base_Flash = 0x8000000 ; /* Flash */  
  __top_BOARD_FLASH = 0x8000000 + 0x200000 ; /* 2M bytes */  
  __top_Flash = 0x8000000 + 0x200000 ; /* 2M bytes */  
  __base_LITTLEFS_FLASH_region = 0xbe00000  ; /* LITTLEFS_FLASH_region */  
  __base_Flash2 = 0xbe00000 ; /* Flash2 */  
  __top_LITTLEFS_FLASH_region = 0xbe00000 + 0x200000 ; /* 2M bytes */  
  __top_Flash2 = 0xbe00000 + 0x200000 ; /* 2M bytes */  
  __base_SRAM = 0x20000000  ; /* SRAM */  
  __base_RAM = 0x20000000 ; /* RAM */  
  __top_SRAM = 0x20000000 + 0x130000 ; /* 1216K bytes */  
  __top_RAM = 0x20000000 + 0x130000 ; /* 1216K bytes */  
  __base_m_mbox13 = 0x41380000  ; /* m_mbox13 */  
  __base_RAM2 = 0x41380000 ; /* RAM2 */  
  __top_m_mbox13 = 0x41380000 + 0x488 ; /* 1160 bytes */  
  __top_RAM2 = 0x41380000 + 0x488 ; /* 1160 bytes */  
  __base_m_txq31 = 0x41380488  ; /* m_txq31 */  
  __base_RAM3 = 0x41380488 ; /* RAM3 */  
  __top_m_txq31 = 0x41380488 + 0x1000 ; /* 4K bytes */  
  __top_RAM3 = 0x41380488 + 0x1000 ; /* 4K bytes */  
  __base_m_mbox23 = 0x443c0000  ; /* m_mbox23 */  
  __base_RAM4 = 0x443c0000 ; /* RAM4 */  
  __top_m_mbox23 = 0x443c0000 + 0x488 ; /* 1160 bytes */  
  __top_RAM4 = 0x443c0000 + 0x488 ; /* 1160 bytes */  
  __base_m_txq23 = 0x443c0488  ; /* m_txq23 */  
  __base_RAM5 = 0x443c0488 ; /* RAM5 */  
  __top_m_txq23 = 0x443c0488 + 0x1080 ; /* 4224 bytes */  
  __top_RAM5 = 0x443c0488 + 0x1080 ; /* 4224 bytes */  
  __base_m_txq32 = 0x443c1508  ; /* m_txq32 */  
  __base_RAM6 = 0x443c1508 ; /* RAM6 */  
  __top_m_txq32 = 0x443c1508 + 0x1080 ; /* 4224 bytes */  
  __top_RAM6 = 0x443c1508 + 0x1080 ; /* 4224 bytes */  
