/*
 * UART.h
 *
 * Created: 4/02/2025 17:28:55
 *  Author: pablo
 */ 


#ifndef UART_H_
#define UART_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stddef.h>  

// Definiciones
#define F_CPU 16000000UL
#define BAUD 9600
#define UBRR_VALUE ((F_CPU / (16UL * BAUD)) - 1)

void UART_init(void);
void UART_writeChar(char c);
void UART_writeText(const char *str);
char UART_readChar(void);
uint8_t UART_available(void);

#endif /* UART_H_ */
