#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
//#include "board.h"
//#include "clock_config.h"
//#include "pin_mux.h"
#include "fsl_debug_console.h"
#include "ads1298.h"
#include "app.h"

/* ---- Millisecond timer ---- */
volatile uint32_t systemMillis = 0;

void SysTick_Handler(void) { systemMillis++; }
static void initMillisTimer(void) { SysTick_Config(SystemCoreClock / 1000U); }
static uint32_t millis(void) { return systemMillis; }

/* ---- MAIN ---- */
int main(void)
{
    BOARD_InitHardware();
    initMillisTimer();
    PRINTF("\r\n=== RW612 + ADS1298 ECG ===\r\n");

    ADS_GPIO_Init();
    ADS_SPI_Init();
    ADS_Reset();

    uint8_t id = ADS_ReadID();
    PRINTF("Device ID: 0x%02X\r\n", id);

    if ((id & 0x1F) != 0x12)
    {
        PRINTF("ERROR: ADS1298 NOT DETECTED!\r\n");
        while (1);
    }

    PRINTF("ADS1298 OK, configuring...\r\n");
    ADS_Configure();

    ADS_DRDY_InterruptInit();
    ADS_WriteCmd(CMD_START);

    uint8_t  frame[27];
    int32_t  ch[8];
    uint32_t lastTime = millis();
    uint32_t sampleCount = 0;
    PRINTF("ECG signal reading......\r\n");
    while (1)
    {
        if (drdy_flag)
        {
            drdy_flag = false;
            ADS_ReadFrame(frame);
            ADS_ParseChannels(frame, ch);
            sampleCount++;

            PRINTF("%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld\r\n",
                ch[0], ch[1], ch[2], ch[3], ch[4], ch[5], ch[6], ch[7]);
        }

//        if ((millis() - lastTime) >= 1000)
//        {
//            PRINTF("\n*** Samples in last 1s: %ld ***\r\n", sampleCount);
//            ADS_WriteCmd(CMD_STOP);
//            PRINTF("--- ACQUISITION STOPPED ---\r\n");
//            break;
//        }
    }

    while (1);
}
