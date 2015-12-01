/**
 ******************************************************************************
 * @file    main.c
 * @author  Konrad
 * @version V1.0
 * @date    11-11-2015
 * @brief   UART I/O with send_char().
 ******************************************************************************
 */

#include "stm32f30x.h"
#include <string.h>
#include <stdlib.h>

char my_buffer[5] = "";

void send_char(char c) {
	while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET)
		;
	USART_SendData(USART2, c);
}

void send_string(const char* s) {
	while (*s)
		send_char(*s++);
}

/* test
char *strnstr(const char *haystack, const char *needle, size_t len) {
	int i;
	size_t needle_len;

	/* segfault here if needle is not NULL terminated
	if (0 == (needle_len = strlen(needle)))
		return (char *) haystack;

	for (i = 0; i <= (int) (len - needle_len); i++) {
		if ((haystack[0] == needle[0])
				&& (0 == strncmp(haystack, needle, needle_len)))
			return (char *) haystack;

		haystack++;
	}
	return NULL;
}
*/

int main(void) {
	GPIO_InitTypeDef gpio;
	USART_InitTypeDef uart;

	RCC_AHBPeriphClockCmd(
			RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB | RCC_AHBPeriph_GPIOC
					| RCC_AHBPeriph_GPIOD, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE); //UART clock

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_7); //RX, via M00118585.pdf
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_7); //TX, via M00118585.pdf

	GPIO_StructInit(&gpio);
	gpio.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
	gpio.GPIO_Mode = GPIO_Mode_AF; //Alternate function for UART
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_PuPd = GPIO_PuPd_UP;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpio); //UART init

	gpio.GPIO_Pin = GPIO_Pin_5; //pin 5 port A - onboard LED
	gpio.GPIO_Mode = GPIO_Mode_OUT;
	gpio.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOA, &gpio);

	USART_StructInit(&uart);
	uart.USART_BaudRate = 115200;
	USART_Init(USART2, &uart);

	USART_Cmd(USART2, ENABLE);

	int my_buffer_size = 5; //size of my buffer
	//char *my_buffer; //dm alloc
	//my_buffer = malloc(sizeof(char) * my_buffer_size);
	//memset(my_buffer, 0, sizeof(char) * my_buffer_size);//fill with zeros
	int buffer_index = 0;

	while (1) {
		if (USART_GetFlagStatus(USART2, USART_FLAG_RXNE)) {
			char c = USART_ReceiveData(USART2);
			my_buffer[buffer_index] = c;
			buffer_index++;

			if (buffer_index == my_buffer_size || c == '\r' || c == '\n') {
				if (!strncmp(my_buffer, "on\r", 3) || !strncmp(my_buffer, "on\n", 3)) {
					send_string("Power on onboard LED.\r\n");
					GPIO_SetBits(GPIOA, GPIO_Pin_5);
				} else if (!strncmp(my_buffer, "off\r", 4) || !strncmp(my_buffer, "off\n", 4)) {
					send_string("Power off onboard LED.\r\n");
					GPIO_ResetBits(GPIOA, GPIO_Pin_5);
				} else {
					send_string("Not recognized command.\r\n");
				}
				memset(my_buffer, 0, my_buffer_size);
				buffer_index = 0;
			}

			/*            switch (c) {
			 case 'b':
			 send_string("Odebrano komunikat B!\r\n");
			 GPIO_SetBits(GPIOA, GPIO_Pin_5); //set bit
			 break;
			 case 'a':
			 send_string("Odebrano komunikat A!\r\n");
			 GPIO_ResetBits(GPIOA, GPIO_Pin_5); //reset bit
			 break;
			 default:
			 send_string("Nieznany komunikat!\r\n");
			 break;
			 }*/
		}
	}
}
