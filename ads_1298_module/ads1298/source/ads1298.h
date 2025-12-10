#ifndef ADS1298_H
#define ADS1298_H

#include <stdint.h>
#include <stdbool.h>

/* ---- ADS1298 Commands ---- */
#define CMD_WAKEUP   0x02
#define CMD_STANDBY  0x04
#define CMD_RESET    0x06
#define CMD_START    0x08
#define CMD_STOP     0x0A
#define CMD_RDATAC   0x10
#define CMD_SDATAC   0x11
#define CMD_RDATA    0x12
#define CMD_RREG     0x20
#define CMD_WREG     0x40

/* ---- Registers ---- */
#define REG_ID       0x00
#define CONFIG1      0x01
#define CONFIG2      0x02
#define CONFIG3      0x03
#define LOFF_SENSN   0x10
#define LOFF_STATN   0x13
#define CONFIG4      0x17
#define WCT1         0x18
#define WCT2         0x19

#define CH1SET       0x05
#define CH8SET       0x0C

extern volatile bool drdy_flag;

void ADS_GPIO_Init(void);
void ADS_SPI_Init(void);
void ADS_Reset(void);
void ADS_DRDY_InterruptInit(void);
void ADS_WriteCmd(uint8_t cmd);
void ADS_WriteReg(uint8_t reg, uint8_t val);
uint8_t ADS_ReadReg(uint8_t reg);
uint8_t ADS_ReadID(void);
void ADS_ReadFrame(uint8_t *frame);
void ADS_ParseChannels(uint8_t *frame, int32_t *channels);
void ADS_Configure(void);

#endif
