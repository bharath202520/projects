#include "ads1298.h"
#include "fsl_gpio.h"
#include "fsl_spi.h"
#include "fsl_debug_console.h"
#include "fsl_common.h"

/* ---- Pins (RW612) ---- */
#define CS_PORT      0U
#define CS_PIN       10U
#define RESET_PORT   0U
#define RESET_PIN    4U
#define START_PORT   0U
#define START_PIN    15U
#define DRDY_PORT    0U
#define DRDY_PIN     5U
#define PWDN_PORT    0U
#define PWDN_PIN     1U
#define CLKSEL_PORT  0U
#define CLKSEL_PIN   0U
#define ADS_SPI_BASE SPI1

volatile bool drdy_flag = false;

static inline void delay_ms(uint32_t ms)
{
    SDK_DelayAtLeastUs(ms * 1000U, CLOCK_GetFreq(kCLOCK_CoreSysClk));
}

static inline void CS_LOW(void)  { GPIO_PinWrite(GPIO, CS_PORT, CS_PIN, 0); }
static inline void CS_HIGH(void) { GPIO_PinWrite(GPIO, CS_PORT, CS_PIN, 1); }

void ADS_GPIO_Init(void)
{
    gpio_pin_config_t out = { kGPIO_DigitalOutput, 1 };
    gpio_pin_config_t in  = { kGPIO_DigitalInput,  0 };

    GPIO_PortInit(GPIO, CS_PORT);
    GPIO_PortInit(GPIO, RESET_PORT);
    GPIO_PortInit(GPIO, START_PORT);
    GPIO_PortInit(GPIO, PWDN_PORT);
    GPIO_PortInit(GPIO, CLKSEL_PORT);
    GPIO_PortInit(GPIO, DRDY_PORT);

    GPIO_PinInit(GPIO, CS_PORT, CS_PIN, &out);
    CS_HIGH();

    GPIO_PinInit(GPIO, RESET_PORT, RESET_PIN, &out);
    GPIO_PinInit(GPIO, START_PORT, START_PIN, &out);
    GPIO_PinInit(GPIO, PWDN_PORT, PWDN_PIN, &out);
    GPIO_PinInit(GPIO, CLKSEL_PORT, CLKSEL_PIN, &out);

    GPIO_PinWrite(GPIO, START_PORT, START_PIN, 0);
    GPIO_PinWrite(GPIO, PWDN_PORT, PWDN_PIN, 1);
    GPIO_PinWrite(GPIO, CLKSEL_PORT, CLKSEL_PIN, 1);

    GPIO_PinInit(GPIO, DRDY_PORT, DRDY_PIN, &in);
}

void ADS_SPI_Init(void)
{
    spi_master_config_t cfg;
    SPI_MasterGetDefaultConfig(&cfg);
    cfg.baudRate_Bps = 1000000U;        //1MHz
    cfg.polarity     = kSPI_ClockPolarityActiveHigh;
    cfg.phase        = kSPI_ClockPhaseSecondEdge;

    SPI_MasterInit(ADS_SPI_BASE, &cfg, CLOCK_GetFlexCommClkFreq(1));
}

void ADS_WriteCmd(uint8_t cmd)
{
    spi_transfer_t t = {0};
    t.txData = &cmd;
    t.dataSize = 1;
    CS_LOW(); SPI_MasterTransferBlocking(ADS_SPI_BASE, &t); CS_HIGH();
}

void ADS_WriteReg(uint8_t reg, uint8_t val)
{
    uint8_t tx[3] = { CMD_WREG | reg, 0x00, val };
    spi_transfer_t t = { .txData = tx, .dataSize = 3 };
    CS_LOW(); SPI_MasterTransferBlocking(ADS_SPI_BASE, &t); CS_HIGH();
}

uint8_t ADS_ReadReg(uint8_t reg)
{
    uint8_t tx[3] = { CMD_RREG | reg, 0x00, 0x00 };
    uint8_t rx[3];
    spi_transfer_t t = { .txData = tx, .rxData = rx, .dataSize = 3 };
    CS_LOW(); SPI_MasterTransferBlocking(ADS_SPI_BASE, &t); CS_HIGH();
    return rx[2];
}

void ADS_Reset(void)
{
    GPIO_PinWrite(GPIO, RESET_PORT, RESET_PIN, 0);
    delay_ms(5);
    GPIO_PinWrite(GPIO, RESET_PORT, RESET_PIN, 1);
    delay_ms(150);
}

void GPIO_INTA_IRQHandler(void)
{
    GPIO_PortClearInterruptFlags(GPIO, DRDY_PORT, 0U, (1U << DRDY_PIN));
    drdy_flag = true;
    SDK_ISR_EXIT_BARRIER;
}

void ADS_DRDY_InterruptInit(void)
{
    gpio_interrupt_config_t cfg = {
        .mode = kGPIO_PinIntEnableEdge,
        .polarity = kGPIO_PinIntEnableLowOrFall
    };
    GPIO_SetPinInterruptConfig(GPIO, DRDY_PORT, DRDY_PIN, &cfg);
    GPIO_PortEnableInterrupts(GPIO, DRDY_PORT, 0U, (1U << DRDY_PIN));
    EnableIRQ(GPIO_INTA_IRQn);
}

void ADS_ReadFrame(uint8_t *frame)
{
    uint8_t cmd = CMD_RDATA;
    spi_transfer_t t1 = { .txData = &cmd, .dataSize = 1 };
    spi_transfer_t t2 = { .rxData = frame, .dataSize = 27 };
    CS_LOW();
    SPI_MasterTransferBlocking(ADS_SPI_BASE, &t1);
    SPI_MasterTransferBlocking(ADS_SPI_BASE, &t2);
    CS_HIGH();
}

void ADS_ParseChannels(uint8_t *frame, int32_t *channels)
{
    frame += 3;
    for (int i = 0; i < 8; i++)
    {
        int32_t v = (frame[0] << 16) | (frame[1] << 8) | frame[2];
        if (v & 0x00800000) v |= 0xFF000000;
        channels[i] = v;
        frame += 3;
    }
}

void ADS_Configure(void)
{
    ADS_WriteCmd(CMD_SDATAC);
    ADS_WriteReg(CONFIG1, 0x06);
    ADS_WriteReg(CONFIG2, 0x00);
    ADS_WriteReg(CONFIG3, 0xDC);
    ADS_WriteReg(LOFF_SENSN, 0x00);
    ADS_WriteReg(LOFF_STATN, 0x00);
    ADS_WriteReg(CONFIG4, 0x00);
    ADS_WriteReg(WCT1, 0x0A);
    ADS_WriteReg(WCT2, 0xDC);

    for (uint8_t r = CH1SET; r <= CH8SET; r++)
        ADS_WriteReg(r, 0x00);
}

uint8_t ADS_ReadID(void)
{
    ADS_WriteCmd(CMD_SDATAC);
    ADS_WriteCmd(CMD_WAKEUP);
    delay_ms(5);
    return ADS_ReadReg(REG_ID);
}
