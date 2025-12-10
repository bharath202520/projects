/*
 * Copyright (c) 2015-2016 Intel Corporation
 * Copyright 2021-2023 NXP
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <errno/errno.h>
#include <toolchain.h>
#include <porting.h>

#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/conn.h>
#include <bluetooth/uuid.h>
#include <bluetooth/gatt.h>
#include <bluetooth/services/hts.h>
#include <fsl_debug_console.h>
#include <host_msd_fatfs.h>

#if defined(APP_LOWPOWER_ENABLED) && (APP_LOWPOWER_ENABLED > 0)
#include "PWR_Interface.h"
#include "fwk_platform_lowpower.h"
#endif /* APP_LOWPOWER_ENABLED */

#if defined(APP_MEM_POWER_OPT) && (APP_MEM_POWER_OPT > 0)
#include "fsl_mmc.h"
#include "sdmmc_config.h"
#endif /* APP_MEM_POWER_OPT */

#include <peripheral_ht.h>

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void connected(struct bt_conn *conn, uint8_t err);
static void disconnected(struct bt_conn *conn, uint8_t reason);
static void bt_ready(int err);

/*******************************************************************************
 * Variables
 ******************************************************************************/
struct bt_conn *default_conn;

/* Advertising:
 *  - Flags
 *  - Primary Service 0x180D (Heart Rate style – our custom "HT" service)
 *  - Device Information Service 0x180A
 */
// this information it will visible in main page
static const struct bt_data ad[] = {
		/**< AD flags */
    BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
    /* Appearance (Heart Rate Sensor 0x0340) */
    BT_DATA_BYTES(BT_DATA_GAP_APPEARANCE, 0x40, 0x03),
    /* TX Power */
    BT_DATA(BT_DATA_TX_POWER, &tx_power_value, sizeof(tx_power_value)),
};
/* Scan Response (extra space - safe for name + manufacturer) */
static const struct bt_data sd[] = {
		/**< Complete name */
    BT_DATA(BT_DATA_NAME_COMPLETE, CONFIG_BT_DEVICE_NAME,
            sizeof(CONFIG_BT_DEVICE_NAME) - 1),
    /*  Add manufacturer ID here */
    BT_DATA(BT_DATA_MANUFACTURER_DATA,
            manufacturer_data,
            sizeof(manufacturer_data)),
	    /* Public Target Address */
	BT_DATA(BT_DATA_PUB_TARGET_ADDR, dynamic_target_addr,
			sizeof(dynamic_target_addr)),
};


static void att_mtu_updated(struct bt_conn *conn, uint16_t tx, uint16_t rx)
{
    PRINTF("\n===== MTU UPDATED =====\r\n");
    PRINTF("TX=%d  RX=%d\r\n", tx, rx);
}
static struct bt_gatt_cb gatt_callbacks = {
    .att_mtu_updated = att_mtu_updated,
};

#if CONFIG_BT_SMP
static void security_changed(struct bt_conn *conn, bt_security_t level,
                             enum bt_security_err err)
{
    char addr[BT_ADDR_LE_STR_LEN];

    bt_addr_le_to_str(bt_conn_get_dst(conn), addr, sizeof(addr));

    PRINTF("Security changed: %s level %u (error %d)\r\n", addr, level, err);
}

static void auth_passkey_display(struct bt_conn *conn, unsigned int passkey)
{
    char addr[BT_ADDR_LE_STR_LEN];

    bt_addr_le_to_str(bt_conn_get_dst(conn), addr, sizeof(addr));

    PRINTF("Passkey for %s: %06u\r\n", addr, passkey);
}

static void auth_cancel(struct bt_conn *conn)
{
    char addr[BT_ADDR_LE_STR_LEN];

    bt_addr_le_to_str(bt_conn_get_dst(conn), addr, sizeof(addr));

    PRINTF("Pairing cancelled: %s\r\n", addr);
}

static struct bt_conn_auth_cb auth_cb_display = {
    .passkey_display = auth_passkey_display,
    .passkey_entry   = NULL,
    .cancel          = auth_cancel,
};
#endif

static struct bt_conn_cb conn_callbacks = {
    .connected    = connected,
    .disconnected = disconnected,
#if CONFIG_BT_SMP
    .security_changed = security_changed,
#endif
};

#if defined(APP_MEM_POWER_OPT) && (APP_MEM_POWER_OPT > 0)
extern mmc_card_t g_mmc;
#endif /* APP_MEM_POWER_OPT */


//static void connected(struct bt_conn *conn, uint8_t err)
//{
//    char addr[BT_ADDR_LE_STR_LEN];
//    bt_addr_le_to_str(bt_conn_get_dst(conn), addr, sizeof(addr));
//
//    if (err) {
//        PRINTF("Failed to connect to %s (err %u)\r\n", addr, err);
//        return;
//    }
//    PRINTF("Connected to peer: %s\r\n", addr);
//    default_conn = bt_conn_ref(conn);
//    bt_gatt_cb_register(&gatt_callbacks);
//#if CONFIG_BT_SMP
//    if (bt_conn_set_security(conn, BT_SECURITY_L2))
//    {
//        PRINTF("Failed to set security\r\n");
//    }
//#endif
//}

static void connected(struct bt_conn *conn, uint8_t err)
{
    char addr[BT_ADDR_LE_STR_LEN];
    const bt_addr_le_t *peer = bt_conn_get_dst(conn);

    bt_addr_le_to_str(peer, addr, sizeof(addr));

    if (err) {
        PRINTF("Failed to connect to %s (err %u)\r\n", addr, err);
        return;
    }

    PRINTF("Connected to peer: %s\r\n", addr);

    default_conn = bt_conn_ref(conn);

    // ------------------------------
    // Update Advertisement Target MAC
    // ------------------------------
    for (int i = 0; i < 6; i++)
    {
        dynamic_target_addr[i] = peer->a.val[i]; // copy phone MAC
    }

    PRINTF("Updated Target Address for next advertising.\r\n");

    // Restart advertising with updated target MAC
    bt_le_adv_stop();
    bt_le_adv_start(BT_LE_ADV_CONN, ad, ARRAY_SIZE(ad), sd, ARRAY_SIZE(sd));
    PRINTF("Advertising restarted with updated target address.\r\n");

    // ------------------------------------
    // Force pairing (security enable)
    // ------------------------------------
    int sec_err = bt_conn_set_security(conn, BT_SECURITY_L2);
    if (sec_err) {
        PRINTF("Security request failed (%d)\r\n", sec_err);
    } else {
        PRINTF("Pairing Requested...\r\n");
    }
}





static void disconnected(struct bt_conn *conn, uint8_t reason)
{
    PRINTF("Disconnected (reason 0x%02x)\r\n", reason);

    if (default_conn) {
        bt_conn_unref(default_conn);
        default_conn = NULL;
    }
}

static void bt_ready(int err)
{
    if (err)
    {
        PRINTF("Bluetooth init failed (err %d)\r\n", err);
        return;
    }

#if (defined(CONFIG_BT_SETTINGS) && (CONFIG_BT_SETTINGS > 0))
    settings_load();
#endif /* CONFIG_BT_SETTINGS */

    PRINTF("Bluetooth initialized\r\n");

    bt_conn_cb_register(&conn_callbacks);// this sit eh connect or not disconnect is will checking this
        bt_gatt_cb_register(&gatt_callbacks);

#if CONFIG_BT_SMP
    bt_conn_auth_cb_register(&auth_cb_display);
#endif

#if defined(APP_LOWPOWER_ENABLED) && (APP_LOWPOWER_ENABLED > 0) && (!defined(RW612_SERIES))
    /* Initialize and configure the lowpower feature of controller. */
    PLATFORM_ControllerLowPowerInit();
#endif /* APP_LOWPOWER_ENABLED */

    err = bt_le_adv_start(BT_LE_ADV_CONN, ad, ARRAY_SIZE(ad), sd, ARRAY_SIZE(sd));
    if (err)
    {
        PRINTF("Advertising failed to start (err %d)\r\n", err);
        return;
    }

    PRINTF("Advertising successfully started\r\n");

#if defined(APP_LOWPOWER_ENABLED) && (APP_LOWPOWER_ENABLED > 0)
    /* Release the WFI constraint, and allow the device to go to DeepSleep to allow for better power saving. */
    PWR_ReleaseLowPowerModeConstraint(PWR_WFI);
    PWR_SetLowPowerModeConstraint(APP_LOW_POWER_MODE);
#endif /* APP_LOWPOWER_ENABLED */
}

void peripheral_ht_task(void *pvParameters)
{
    int err;

#if defined(APP_MEM_POWER_OPT) && (APP_MEM_POWER_OPT > 0)
    MMC_Init(&g_mmc);
#endif /* APP_MEM_POWER_OPT */

    PRINTF("BLE Peripheral HT demo start...\r\n");

    err = bt_enable(bt_ready);//
    if (err)
    {
        PRINTF("Bluetooth init failed (err %d)\r\n", err);
        while (1)
        {
            vTaskDelay(2000);
        }
    }

    while (1)
    {
        vTaskDelay(100);
        bt_hts_indicate();
    }
}
