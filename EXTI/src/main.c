/**
 ******************************************************************************
 * @file    main.c
 * @author  Ac6
 * @version V1.0
 * @date    01-December-2013
 * @brief   Default main function.
 ******************************************************************************
 */

#include "stm32f30x.h"

volatile uint32_t timer_ms = 0;

void SysTick_Handler() {
	if (timer_ms) {
		timer_ms--;
	}
}

void delay_ms(int time) {
	timer_ms = time;
	while (timer_ms) {
	};
}

void EXTI15_10_IRQHandler() {
	if (EXTI_GetITStatus(EXTI_Line13)) {
		if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13) == 0) {
			GPIO_SetBits(GPIOA, GPIO_Pin_5);
		} else {
			GPIO_ResetBits(GPIOA, GPIO_Pin_5);
		}
		EXTI_ClearITPendingBit(EXTI_Line13);
	}
}

int main(void) {

	GPIO_InitTypeDef gpio;
	EXTI_InitTypeDef exti;
	NVIC_InitTypeDef nvic;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	GPIO_StructInit(&gpio);
	gpio.GPIO_Pin = GPIO_Pin_5;
	gpio.GPIO_Mode = GPIO_Mode_OUT;
	gpio.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOA, &gpio);

	gpio.GPIO_Pin = GPIO_Pin_13;
	gpio.GPIO_Mode = GPIO_Mode_IN;
	gpio.GPIO_PuPd = GPIO_PuPd_UP;
	gpio.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOC, &gpio);

	GPIO_StructInit(&gpio);
	gpio.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 |
	GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 |
	GPIO_Pin_8 | GPIO_Pin_9;
	gpio.GPIO_Mode = GPIO_Mode_OUT;
	gpio.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOC, &gpio);

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource13); //via DM00073522 faq file, onboard button as trigger

	EXTI_StructInit(&exti);
	exti.EXTI_Line = EXTI_Line13; //GPIO can use lines 0-15
	exti.EXTI_Mode = EXTI_Mode_Interrupt;
	exti.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	exti.EXTI_LineCmd = ENABLE;
	EXTI_Init(&exti);

	nvic.NVIC_IRQChannel = EXTI15_10_IRQn; //to be found in stm32f30x.h, search 'external line'
	nvic.NVIC_IRQChannelPreemptionPriority = 0x00; //highest priority
	nvic.NVIC_IRQChannelSubPriority = 0x00; //-||-
	nvic.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic);

	//SysTick_Config(SystemCoreClock / 1000); //tick every 1ms

	//uint32_t led = 0;

	/*while (1) {
		GPIO_SetBits(GPIOC, 1 << led); //set bit
		delay_ms(150);
		GPIO_ResetBits(GPIOC, 1 << led); //reset bit
		if (++led >= 10) {
			led = 0;
		}
	}*/
}

