#include "stc15f.h"


#define MAIN_Fosc	35000000L

const u8 data[12] = {0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0x9B, 0x64, 0xAB, 0x54, 0x54, 0xAB};

void delay_ms(unsigned char ms)
{
	unsigned int i;
	do {
		i = MAIN_Fosc / 18000;
		while (--i);
	} while (--ms);
}

void delay_6000us(void)
{
	u32 i = 9700;
	while (i--);
}

void delay_7300us(void)
{
	u32 i = 11800;
	while (i--);
}

void delay_4500us(void)
{
	u32 i = 7150;
	while (i--);
}

void delay_560us_high(void)
{
	u32 i = 870;
	while (i--);
}

void delay_560us_low(void)
{
	u32 i = 870;
	while (i--);
}

void ZH_JT_03(u8 *data)
{
	int i;
	int j;

	INT_CLK0 = 0x01;
	delay_6000us();
	INT_CLK0 = 0x00;
	delay_7300us();
	for (i=0;i<12;i++) {
		for (j=0;j<8;j++) {
			INT_CLK0 = 0x01;
			delay_560us_high();
			INT_CLK0 = 0x00;
			delay_560us_low();
			if ((data[i]<<j)&0x80) {
				delay_560us_low();
				delay_560us_low();
			}
		}
	}
	delay_7300us();
	INT_CLK0 = 0x01;
	delay_560us_high();
	INT_CLK0 = 0x00;
}

void main(void)
{
	u8 data[12];

	P33 = 1;
	P35 = 0;

	Timer0_16bitAutoReload();
	Timer0_AsTimer();
	Timer0_1T();
	TL0 = (65535UL - 461) % 256; // 35MHz / 461 = 76KHz,  76KHz / 2 = 38KHz
	TH0 = (65535UL - 461) / 256;
	Timer0_InterruptDisable();

	EA = 1;

	Timer0_Run();

	while (1) {
		if (P32 == 0) {
			P33 = 1;
			ZH_JT_03(data);
			P33 = 0;
			delay_ms(200);
		}
	}
}
