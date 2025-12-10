/*
 * BLE Peripheral HT + Manufacturer Data
 * RW612 / MCUXpresso / Edgefast BLE Stack
 */

#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <errno/errno.h>
#include <toolchain.h>
#include <porting.h>
#include <fsl_debug_console.h>
#include <sys/byteorder.h>
#include <stdlib.h>

#include <bluetooth/bluetooth.h>
#include <bluetooth/uuid.h>
#include <bluetooth/gatt.h>
#include <bluetooth/services/hts.h>
#include <peripheral_ht.h>


static bool cccd_written;


/************ Characteristics Storage ************/
static uint8_t chr_2a1c_val[8] = "0";
static uint8_t chr_2a1d_val[8] = "0";
static uint8_t chr_2a1e_val[8] = "0";

/************ PROTOTYPES ************/
static void htmc_ccc_cfg_changed(const struct bt_gatt_attr *attr, uint16_t value);
static ssize_t read_str(struct bt_conn *conn, const struct bt_gatt_attr *attr,
                        void *buf, uint16_t len, uint16_t offset);
static ssize_t read_char(struct bt_conn *conn, const struct bt_gatt_attr *attr,
                         void *buf, uint16_t len, uint16_t offset);
static ssize_t write_char(struct bt_conn *conn, const struct bt_gatt_attr *attr,
                          const void *buf, uint16_t len,
                          uint16_t offset, uint8_t flags);



/************ Device Information GATT SERVICES ************/
static BT_GATT_SERVICE_DEFINE(dev_info,
	//main service 0x180A Device Information Service
    BT_GATT_PRIMARY_SERVICE(BT_UUID_DIS),
	//Device Information -> main service -> sub-Characteristic 0x2A23 System ID
    BT_GATT_CHARACTERISTIC(BT_UUID_DIS_SYSTEM_ID,
                           BT_GATT_CHRC_READ, BT_GATT_PERM_READ,
                           read_str, NULL,system_id_string),
	//Device Information -> main service -> sub-Characteristic 0x2A24 Model Number String
    BT_GATT_CHARACTERISTIC(BT_UUID_DIS_MODEL_NUMBER,
                           BT_GATT_CHRC_READ, BT_GATT_PERM_READ,
                           read_str, NULL, model_string),
	//Device Information -> main service -> sub-Characteristic 0x2A25 Serial Number String
    BT_GATT_CHARACTERISTIC(BT_UUID_DIS_SERIAL_NUMBER,
                           BT_GATT_CHRC_READ, BT_GATT_PERM_READ,
                           read_str, NULL, serial_string),
	//Device Information -> main service -> sub-Characteristic 0x2A26 Firmware Revision String
    BT_GATT_CHARACTERISTIC(BT_UUID_DIS_FIRMWARE_REVISION,
                           BT_GATT_CHRC_READ, BT_GATT_PERM_READ,
						   read_str, NULL, firmware_string),
    //Device Information -> main service -> sub-Characteristic 0x2A27 Hardware Revision String
	BT_GATT_CHARACTERISTIC(BT_UUID_DIS_HARDWARE_REVISION,
						   BT_GATT_CHRC_READ, BT_GATT_PERM_READ,
						   read_str, NULL,hardware_string),
    //Device Information -> main service -> sub-Characteristic 0x2A28 Software Revision String
    BT_GATT_CHARACTERISTIC(BT_UUID_DIS_SOFTWARE_REVISION,
						   BT_GATT_CHRC_READ, BT_GATT_PERM_READ,
						   read_str, NULL,software_string),
    //Device Information -> main service -> sub-Characteristic 0x2A29 Manufacturer Name String
    BT_GATT_CHARACTERISTIC(BT_UUID_DIS_MANUFACTURER_NAME,
					       BT_GATT_CHRC_READ, BT_GATT_PERM_READ,
					       read_str, NULL,manufacure_string),
////2A2A software string
// BT_GATT_CHARACTERISTIC(BT_UUID_DIS_SERIAL_NUMBER,
//		 	 	 	 	 BT_GATT_CHRC_READ, BT_GATT_PERM_READ,
//						 read_str, NULL, sn),
////2A29 software string
// BT_GATT_CHARACTERISTIC(BT_UUID_DIS_SERIAL_NUMBER,
//						BT_GATT_CHRC_READ, BT_GATT_PERM_READ,
//						read_str, NULL, sn),
);

/**************Heart Rate GATT SERVICES **************/
static BT_GATT_SERVICE_DEFINE(hts_svc,
	//main service 0x180d Heart Rate Service
    BT_GATT_PRIMARY_SERVICE(BT_UUID_HRS),
	//Heart Rate -> main service -> sub-Characteristic 0x1801 Generic Attribute
    BT_GATT_CHARACTERISTIC(BT_UUID_GATT,
                           BT_GATT_CHRC_READ | BT_GATT_CHRC_WRITE | BT_GATT_CHRC_NOTIFY,
                           BT_GATT_PERM_READ | BT_GATT_PERM_WRITE,
                           read_char, write_char, chr_2a1c_val),
	BT_GATT_CCC(htmc_ccc_cfg_changed, BT_GATT_PERM_READ | BT_GATT_PERM_WRITE),
	//Heart Rate -> main service -> sub-Characteristic 0x1802 Immediate Alert Service
    BT_GATT_CHARACTERISTIC(BT_UUID_IAS,
                           BT_GATT_CHRC_READ | BT_GATT_CHRC_WRITE | BT_GATT_CHRC_NOTIFY,
                           BT_GATT_PERM_READ | BT_GATT_PERM_WRITE,
                           read_char, write_char, chr_2a1d_val),
    BT_GATT_CCC(htmc_ccc_cfg_changed, BT_GATT_PERM_READ | BT_GATT_PERM_WRITE),
	//Heart Rate -> main service -> sub-Characteristic 0x1807 Next DST Change Service
    BT_GATT_CHARACTERISTIC(BT_UUID_NDSTS,
                           BT_GATT_CHRC_READ | BT_GATT_CHRC_WRITE | BT_GATT_CHRC_NOTIFY,
                           BT_GATT_PERM_READ | BT_GATT_PERM_WRITE,
                           read_char, write_char, chr_2a1e_val),
    BT_GATT_CCC(htmc_ccc_cfg_changed, BT_GATT_PERM_READ | BT_GATT_PERM_WRITE)
);

/************ CCC CALLBACK ************/
static void htmc_ccc_cfg_changed(const struct bt_gatt_attr *attr, uint16_t value)
{
    cccd_written = (value == BT_GATT_CCC_NOTIFY);
}

/************ READ HANDLERS ************/
static ssize_t read_str(struct bt_conn *conn, const struct bt_gatt_attr *attr,
                        void *buf, uint16_t len, uint16_t offset)
{
    return bt_gatt_attr_read(conn, attr, buf, len, offset,
                             attr->user_data, strlen((char *)attr->user_data));
}

static ssize_t read_char(struct bt_conn *conn, const struct bt_gatt_attr *attr,
                         void *buf, uint16_t len, uint16_t offset)
{
    return bt_gatt_attr_read(conn, attr, buf, len, offset,
                             attr->user_data, strlen((char *)attr->user_data));
}

/************ WRITE HANDLER ************/
static ssize_t write_char(struct bt_conn *conn, const struct bt_gatt_attr *attr,
                          const void *buf, uint16_t len,
                          uint16_t offset, uint8_t flags)
{
    uint8_t *dst = (uint8_t *)attr->user_data;

    if (offset + len >= 8) {
        len = 7 - offset;
    }

    memcpy(dst + offset, buf, len);
    dst[offset + len] = '\0';

    PRINTF("WRITE CHAR → %s\r\n", dst);
    return len;
}

/************ this is the information if the  255 dummy data pass bluettoth  ************/
//void bt_hts_indicate(void)
//{
//    static uint8_t buffer[255];
//    static bool init = false;
//
//    if (!cccd_written)
//        return;
//
//    if (!init)
//    {
//        for (int i = 0; i < 255; i++)
//            buffer[i] = i;
//        init = true;
//    }
//
//    int ret = bt_gatt_notify(NULL, &hts_svc.attrs[2], buffer, sizeof(buffer));
//
//    if (ret == 0)
//        PRINTF("Sent 255-byte Notification.\r\n");
//    else
//        PRINTF("Notify error %d (MTU too small)\r\n", ret);
//}








void bt_hts_indicate(void)
{
    static uint8_t buffer1[255];
    static uint8_t buffer2[255];
    static uint8_t buffer3[255];
    static bool init = false;

    if (!cccd_written)
        return;

    if (!init)
    {
        for (int i = 0; i < 255; i++)
        {
            buffer1[i] = 'A';           // Data for characteristic 1
            buffer2[i] = 'B';     // Data for characteristic 2
            buffer3[i] = 'C';     // Data for characteristic 3
        }
        init = true;
    }

//    int ret1 = bt_gatt_notify(NULL, &hts_svc.attrs[2], buffer1, sizeof(buffer1));
//    int ret2 = bt_gatt_notify(NULL, &hts_svc.attrs[5], buffer2, sizeof(buffer2));
    int ret3 = bt_gatt_notify(NULL, &hts_svc.attrs[8], buffer3, sizeof(buffer3));

//    if (ret1 == 0 || ret2 == 0 || ret3 == 0)
    if (ret3 == 0)
    {
        PRINTF("Sent 255 bytes on ALL 3 characteristics.\r\n");
    }
    else
    {
//        PRINTF("Notify error: 2A1C=%d 2A1D=%d 2A1E=%d (Check MTU?)\r\n",
//                ret1, ret2, ret3);
    	 PRINTF("Notify error: 2A1C=%d(Check MTU?)\r\n",ret3);
    }
}


