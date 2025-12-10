//
//#include "fsl_spi.h"
//#include "fsl_debug_console.h"
//#include "fsl_common.h"
//#include "pin_mux.h"
//#include "clock_config.h"
//#include "board.h"
//#include "fsl_gpio.h"
//#include "fsl_io_mux.h"
//#include <string.h>
//#include <stdio.h>
//
///*******************************************************************************
// * Definitions
// ******************************************************************************/
//#define BUFFER_SIZE (64)
//
///* Use Flexcomm1 SPI */
//#define EXAMPLE_SPI_MASTER              SPI1
//#define EXAMPLE_SPI_MASTER_CLK_SRC      kCLOCK_Flexcomm1
//#define EXAMPLE_SPI_MASTER_CLK_FREQ     CLOCK_GetFlexCommClkFreq(1U)
//#define EXAMPLE_SPI_SPOL                kSPI_SpolActiveAllLow
//
///* Manual Chip Select GPIOs */
//#define CS1_GPIO_PORT  0U
//#define CS1_GPIO_PIN   4U   /* Flash #1 manual CS */
//#define CS2_GPIO_PORT  0U
//#define CS2_GPIO_PIN   6U   /* Flash #2 manual CS */
//
///* NAND Flash Commands */
//#define NAND_CMD_RESET       0xFF
//#define NAND_CMD_READ_ID     0x9F
//
///*******************************************************************************
// * Function Prototypes
// ******************************************************************************/
//void BOARD_InitPins_ManualSPI(void);
//void SPI_setup(void);
//void SPI_TxRx(uint8_t *tx, uint8_t *rx, size_t len);
//void Flash_CS_Init(void);
//void Flash_CS_Low(uint8_t cs_gpio_pin);
//void Flash_CS_High(uint8_t cs_gpio_pin);
//void NAND_Reset(uint8_t cs_gpio_pin);
//void NAND_ReadID(uint8_t *id_data, uint8_t cs_gpio_pin);
//
///*******************************************************************************
// * Variables
// ******************************************************************************/
//static uint8_t nandIdData1[4] = {0};
//static uint8_t nandIdData2[4] = {0};
//
///*******************************************************************************
// * BOARD PIN INITIALIZATION
// ******************************************************************************/
//void BOARD_InitPins_ManualSPI(void)
//{
//    /* --- Flexcomm1 SPI pin mux --- */
//
//    /* SCK -> GPIO_7 */
//    IO_MUX_SetPinMux(0x000003C0U, 0x00000000U,
//                     IO_MUX_GPIO_FC_MASK(0, 1, 0x008), IO_MUX_GPIO_FC_MASK(1, 1, 0x7F7),
//                     0x00000000U, 0x01000000U,
//                     IO_MUX_CTIMER_MASK(0, 0), IO_MUX_CTIMER_MASK(0, 0),
//                     IO_MUX_SCTIMER_MASK(0, 0), IO_MUX_SCTIMER_MASK(0, 0));
//
//    /* MISO -> GPIO_8 */
//    IO_MUX_SetPinMux(0x00000780U, 0x00000000U,
//                     IO_MUX_GPIO_FC_MASK(0, 1, 0x010), IO_MUX_GPIO_FC_MASK(1, 1, 0x7EF),
//                     0x00000000U, 0x02000000U,
//                     IO_MUX_CTIMER_MASK(0, 0), IO_MUX_CTIMER_MASK(0, 0),
//                     IO_MUX_SCTIMER_MASK(0, 0), IO_MUX_SCTIMER_MASK(0, 0));
//
//    /* MOSI -> GPIO_9 */
//    IO_MUX_SetPinMux(0x00000F00U, 0x00000000U,
//                     IO_MUX_GPIO_FC_MASK(0, 1, 0x020), IO_MUX_GPIO_FC_MASK(1, 1, 0x7DF),
//                     0x00000000U, 0x04000000U,
//                     IO_MUX_CTIMER_MASK(0, 0), IO_MUX_CTIMER_MASK(0, 0),
//                     IO_MUX_SCTIMER_MASK(0, 0), IO_MUX_SCTIMER_MASK(0, 0));
//
//    /* --- Manual Chip Selects (GPIO) --- */
//    /* CS1 -> GPIO_4 */
//    IO_MUX_SetPinMux(0x00000010U, 0x00000000U,
//                     IO_MUX_GPIO_FC_MASK(1, 0, 0), IO_MUX_GPIO_FC_MASK(0, 0, 0),
//                     0x00000000U, 0x00000000U,
//                     IO_MUX_CTIMER_MASK(0, 0), IO_MUX_CTIMER_MASK(0, 0),
//                     IO_MUX_SCTIMER_MASK(0, 0), IO_MUX_SCTIMER_MASK(0, 0));
//
//    /* CS2 -> GPIO_6 */
//    IO_MUX_SetPinMux(0x00000040U, 0x00000000U,
//                     IO_MUX_GPIO_FC_MASK(1, 0, 0), IO_MUX_GPIO_FC_MASK(0, 0, 0),
//                     0x00000000U, 0x00000000U,
//                     IO_MUX_CTIMER_MASK(0, 0), IO_MUX_CTIMER_MASK(0, 0),
//                     IO_MUX_SCTIMER_MASK(0, 0), IO_MUX_SCTIMER_MASK(0, 0));
//}
//
///*******************************************************************************
// * SPI + GPIO CS CONTROL
// ******************************************************************************/
//void Flash_CS_Init(void)
//{
//    gpio_pin_config_t cs_config = {kGPIO_DigitalOutput, 1U};
//
//    GPIO_PortInit(GPIO, CS1_GPIO_PORT);
//    GPIO_PortInit(GPIO, CS2_GPIO_PORT);
//
//    GPIO_PinInit(GPIO, CS1_GPIO_PORT, CS1_GPIO_PIN, &cs_config);
//    GPIO_PinInit(GPIO, CS2_GPIO_PORT, CS2_GPIO_PIN, &cs_config);
//
//    GPIO_PinWrite(GPIO, CS1_GPIO_PORT, CS1_GPIO_PIN, 1U);
//    GPIO_PinWrite(GPIO, CS2_GPIO_PORT, CS2_GPIO_PIN, 1U);
//}
//
//void Flash_CS_Low(uint8_t cs_gpio_pin)
//{
//    GPIO_PinWrite(GPIO, 0U, cs_gpio_pin, 0U);
//}
//
//void Flash_CS_High(uint8_t cs_gpio_pin)
//{
//    GPIO_PinWrite(GPIO, 0U, cs_gpio_pin, 1U);
//}
//
///*******************************************************************************
// * SPI MASTER INITIALIZATION
// ******************************************************************************/
//void SPI_setup(void)
//{
//    spi_master_config_t userConfig = {0};
//    uint32_t srcFreq;
//
//    SPI_MasterGetDefaultConfig(&userConfig);
//    userConfig.enableLoopback = false;
//    userConfig.sselNum = (spi_ssel_t)0xFF; // Disable hardware SSEL
//    userConfig.sselPol = EXAMPLE_SPI_SPOL;
//    userConfig.baudRate_Bps = 8000000U; // 8 MHz SPI clock
//
//    srcFreq = EXAMPLE_SPI_MASTER_CLK_FREQ;
//    SPI_MasterInit(EXAMPLE_SPI_MASTER, &userConfig, srcFreq);
//}
//
///*******************************************************************************
// * GENERIC SPI TRANSFER
// ******************************************************************************/
//void SPI_TxRx(uint8_t *tx, uint8_t *rx, size_t len)
//{
//    spi_transfer_t xfer = {0};
//    xfer.txData = tx;
//    xfer.rxData = rx;
//    xfer.dataSize = len;
//    xfer.configFlags = kSPI_FrameAssert;
//    SPI_MasterTransferBlocking(EXAMPLE_SPI_MASTER, &xfer);
//}
//
///*******************************************************************************
// * FLASH COMMAND FUNCTIONS
// ******************************************************************************/
//void NAND_Reset(uint8_t cs_gpio_pin)
//{
//    uint8_t tx[1] = {NAND_CMD_RESET};
//    uint8_t rx[1] = {0};
//
//    PRINTF("Sending NAND Reset on GPIO_%d...\r\n", cs_gpio_pin);
//    Flash_CS_Low(cs_gpio_pin);
//    SPI_TxRx(tx, rx, 1);
//    Flash_CS_High(cs_gpio_pin);
//
//    SDK_DelayAtLeastUs(1000, SystemCoreClock);
//    PRINTF("Reset done on GPIO_%d\r\n", cs_gpio_pin);
//}
//
//void NAND_ReadID(uint8_t *id_data, uint8_t cs_gpio_pin)
//{
//    uint8_t tx[5] = {NAND_CMD_READ_ID, 0, 0, 0, 0};
//    uint8_t rx[5] = {0};
//
//    PRINTF("Reading Flash ID on GPIO_%d...\r\n", cs_gpio_pin);
//    Flash_CS_Low(cs_gpio_pin);
//    SPI_TxRx(tx, rx, sizeof(tx));
//    Flash_CS_High(cs_gpio_pin);
//
//    memcpy(id_data, &rx[1], 4);
//
//    if ((id_data[0] == 0xFF && id_data[1] == 0xFF) ||
//        (id_data[0] == 0x00 && id_data[1] == 0x00))
//    {
//        PRINTF("⚠ No device detected on GPIO_%d\r\n", cs_gpio_pin);
//    }
//    else
//    {
//        PRINTF("Flash on GPIO_%d ID: %02X %02X %02X %02X\r\n",
//               cs_gpio_pin, id_data[0], id_data[1], id_data[2], id_data[3]);
//    }
//}
//
///*******************************************************************************
// * MAIN APPLICATION
// ******************************************************************************/
//int main(void)
//{
//    /* Initialize hardware */
//	CLOCK_AttachClk(kSFRO_to_FLEXCOMM1);
//    BOARD_InitBootPins();
//    BOARD_InitBootClocks();
//    BOARD_InitDebugConsole();
//
//    PRINTF("\r\n=========================================\r\n");
//    PRINTF(" RW612 Dual SPI NAND Flash (Flexcomm1) \r\n");
//    PRINTF(" Manual CS on GPIO_4 & GPIO_6 \r\n");
//    PRINTF("=========================================\r\n");
//
//    BOARD_InitPins_ManualSPI();
//    SPI_setup();
//    Flash_CS_Init();
//
//    /* Reset both flashes */
//    NAND_Reset(CS1_GPIO_PIN);
//    SDK_DelayAtLeastUs(5000, SystemCoreClock);
//    NAND_Reset(CS2_GPIO_PIN);
//    SDK_DelayAtLeastUs(5000, SystemCoreClock);
//
//    /* Read both IDs */
//    NAND_ReadID(nandIdData1, CS1_GPIO_PIN);
//    NAND_ReadID(nandIdData2, CS2_GPIO_PIN);
//
//    PRINTF("\r\n=========================================\r\n");
//    PRINTF("  NAND Flash Read ID Sequence Complete!  \r\n");
//    PRINTF("=========================================\r\n");
//
//    while (1)
//    {
//    }
//}
