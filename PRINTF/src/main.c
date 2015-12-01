/**
  ******************************************************************************
	* @file    main.c
  * @author  Konrad
  * @version V1.0
  * @date    11-11-2015
  * @brief   UART PRINTF.
  ******************************************************************************
*/


#include "stm32f30x.h"

void send_char(char c)
{
	while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
	USART_SendData(USART2, c);
}

//implementation of __io_putchar for printf, to be used with STM's UART line
int __io_putchar(int c)
{
	if (c=='\n')
		send_char('\r') //carriage return to remove starirs effect
	send_char(c);
	return c;
}

int main(void)
{
	GPIO_InitTypeDef gpio;
	USART_InitTypeDef uart;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB | RCC_AHBPeriph_GPIOC | RCC_AHBPeriph_GPIOD, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	GPIO_StructInit(&gpio):
	gpio.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
	gpio.GPIO_Mode_AF; //Alternate function 7 for UART
	gpio.GPIO_OType = GPIO_OType.PP;
	gpio.GPIO_PuPd = GPIO_PuPd_PP;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpio);//UART pins init

	USART_StructInit(&uart);
	uart.USART_BaudRate = 115200;
	USART_Init(USART2, &uart);

	USART_Cmd(USART2, ENABLE);

	while (1)
	{
		printf("Hello World!\n");
	}
}
