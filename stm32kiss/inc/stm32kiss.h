#ifndef __STM32KISS_H__
#define __STM32KISS_H__

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "stm32f4xx.h"
#include "arm_math.h"
#include "misc.h"
#include "stm32f4xx_adc.h"
#include "stm32f4xx_can.h"
#include "stm32f4xx_cec.h"
#include "stm32f4xx_crc.h"
#include "stm32f4xx_dac.h"
#include "stm32f4xx_dbgmcu.h"
#include "stm32f4xx_dma.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_flash.h"
#include "stm32f4xx_fsmc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_i2c.h"
#include "stm32f4xx_iwdg.h"
#include "stm32f4xx_pwr.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_rtc.h"
#include "stm32f4xx_sdio.h"
#include "stm32f4xx_spi.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_wwdg.h"

typedef struct
{
	int32_t min;
	int32_t max;
} tLIMIT;

#define MIN(a,b)  (((a) < (b)) ? (a) : (b))
#define MAX(a,b)  (((a) > (b)) ? (a) : (b))
#define AVRG(a,b) (((a) + (b))/2)
#define DELTA(a,b, scale) ((MAX(a, b) - MIN(a, b))*scale) / AVRG(a, b)
#define IN_LIMIT(value, limit) (((limit).min <= (value)) && ((value) <= (limit).max))

#define MILLION 1000000.0

#define STRUCT_CLEAR(v) memset((void *)&v, 0, sizeof(v))
#define ZERO_MEMORY(v) STRUCT_CLEAR(v)
#define LENGTH(v) (sizeof(v) / sizeof(v[0]))
#define OPT_BARRIER() asm volatile ("": : :"memory")

//#define PI 3.1415926535897932384626433832795f

#define UNUSED __attribute__ ((unused))

#include "stm32kiss_adc.h"
#include "stm32kiss_dac.h"
#include "stm32kiss_gpio.h"
#include "stm32kiss_ticks.h"
#include "stm32kiss_button.h"
//#include "stm32kiss_fifo.h"
//#include "stm32kiss_dma_usarts.h"

#define PrintChar(c) PrintChar_fast(c)

static inline void PrintChar_fast(char c)
{
	while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);
	USART_SendData(USART3, (uint8_t) c);
}


static inline void usec_timer_init()
{
#ifdef USE_STDPERIPH_DRIVER
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);

	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure = {
			.TIM_Prescaler 		= ((SystemCoreClock / 1000000) / 2) - 1,
			.TIM_CounterMode 	= TIM_CounterMode_Up,
			.TIM_Period 		= 0xFFFFFFFF,
			.TIM_ClockDivision  = 0,
			.TIM_RepetitionCounter = 0,
	};

	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);
	TIM_Cmd(TIM5, ENABLE);
#endif
}

static inline uint32_t usec_timer_read()
{
	return TIM_GetCounter(TIM5);
}

static inline void usec_timer_start(uint32_t *time)
{
	*time = usec_timer_read();
}

static inline void usec_timer_report(const char *title, uint32_t time_start)
{
	uint32_t time = (usec_timer_read() - time_start);

	uint32_t time_us  = time % 1000000;
	uint32_t time_sec = time / 1000000;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat"
	printf("%s time\t%i.%06i\tSec\r\n", title, time_sec, time_us);
#pragma GCC diagnostic pop
}

#include "usart_mini.h"
extern char __printf_buf[512];
#define printf(format, ...) {snprintf(__printf_buf, sizeof(__printf_buf)-1, format, ##__VA_ARGS__); send_str(__printf_buf);}


#endif //#ifndef __STM32KISS_H__
