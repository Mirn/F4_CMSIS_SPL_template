#include "stm32kiss.h"

void dac_on()
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

    pin_analog_output(PIN_A4);
    pin_analog_input(PIN_A5);

    DAC_InitTypeDef DAC_InitStructure =
    {
    		.DAC_Trigger        = DAC_Trigger_None,
    		.DAC_WaveGeneration = DAC_WaveGeneration_None,
    		.DAC_OutputBuffer   = DAC_OutputBuffer_Enable,
    		.DAC_LFSRUnmask_TriangleAmplitude = DAC_TriangleAmplitude_1
    };

    DAC_Init(DAC_Channel_1, &DAC_InitStructure);
    DAC_Init(DAC_Channel_2, &DAC_InitStructure);

    DAC_SoftwareTriggerCmd(DAC_Channel_1, ENABLE);
    DAC_SoftwareTriggerCmd(DAC_Channel_2, ENABLE);

    DAC_Cmd(DAC_Channel_1, ENABLE);
    DAC_Cmd(DAC_Channel_2, ENABLE);
}

void dac_off()
{
	dac_write_a(0x8000);
	//dac_write_b(0x8000);

	pin_analog_input(PIN_A4);
	pin_analog_input(PIN_A5);

    DAC_SoftwareTriggerCmd(DAC_Channel_1, DISABLE);
    DAC_SoftwareTriggerCmd(DAC_Channel_2, DISABLE);

    DAC_Cmd(DAC_Channel_1, DISABLE);
    DAC_Cmd(DAC_Channel_2, DISABLE);

    DAC_DeInit();
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, DISABLE);
}

