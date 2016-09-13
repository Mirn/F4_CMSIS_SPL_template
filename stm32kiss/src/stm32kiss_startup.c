#include "stm32kiss.h"

char __printf_buf[512];

void kiss_startup_init()
{
	//RCC_APB2PeriphClockCmd(RCC_AHB1Periph_AFIO, ENABLE);
	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE); //unlock B4 and etc pins
	//SystemCoreClockUpdate();

	ticks_init();
	delay_ms(750); //for ARMka terminal connection after SFU bootloader
}
