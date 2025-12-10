/* hts.h - Health Thermometer Service sample */

/*
 * Copyright (c) 2019 Aaron Tsui <aaron.tsui@outlook.com>
 * Copyright 2022 NXP
 * 
 * SPDX-License-Identifier: Apache-2.0
 */

#ifdef __cplusplus
extern "C" {
#endif


static uint8_t manufacturer_data[] = {0xFF,0XFF,0x03,0x09,0x0C,0x19,0x00,0x00,0x01};

/* Tx Power value (signed int8, -20 to +20 dBm) */
static int8_t tx_power_value = 0x04;  // +4 dBm example

/* Preferred connection interval range (Little-endian, unit = 1.25ms) */
static uint8_t conn_interval_range[4] = {
    0x06, 0x00,   /* Min: 6 × 1.25ms = 7.5ms */
    0x20, 0x00    /* Max: 32 × 1.25ms = 40ms */
};

/* Public target address (example random MAC) */
//static uint8_t target_addr[6] = {0xAA,0xBB,0xCC,0x11,0x22,0x33};


static uint8_t dynamic_target_addr[6] = {0};



/************ DEVICE INFO ************/
#define BT_SYSTEM_ID		"000000000"
#define BT_MODEL_NUM    	"00M_300"
#define BT_SERIAL_NUM   	"xxx"
#define BT_FIRMWARE_VER     "Vx.x.x.x"
#define BT_HARDWARE_VER     "x.x.x.x"
#define BT_SOFTWARE_VER     "x"
#define BT_MANUFACTION      "KMT"

#define BT_DIS_STR_MAX   (10U)


/************ Device Information Values ************/
static uint8_t system_id_string[BT_DIS_STR_MAX] = BT_SYSTEM_ID;
static uint8_t model_string[BT_DIS_STR_MAX] = BT_MODEL_NUM;
static uint8_t serial_string[BT_DIS_STR_MAX]  = BT_SERIAL_NUM;
static uint8_t firmware_string[BT_DIS_STR_MAX]    = BT_FIRMWARE_VER;
static uint8_t hardware_string[BT_DIS_STR_MAX] = BT_HARDWARE_VER;
static uint8_t software_string[BT_DIS_STR_MAX] = BT_SOFTWARE_VER;
static uint8_t manufacure_string[BT_DIS_STR_MAX]  = BT_MANUFACTION;




/*******************************************************************************
 * API
 ******************************************************************************/
void peripheral_ht_task(void *pvParameters);
#ifdef __cplusplus
}
#endif
