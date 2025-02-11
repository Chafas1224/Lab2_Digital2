/*
 * UART.c
 *
 * Created: 4/02/2025 17:29:16
 *  Author: pablo
 */ 

#include "UART.h"

volatile char rxBuffer;  // Buffer para recepción
volatile uint8_t rxFlag = 0;  // Bandera de dato disponible

void UART_init(void) {
	// Configurar pines
	DDRD &= ~(1 << DDD0); // PD0 (RX) como entrada
	DDRD |= (1 << DDD1);  // PD1 (TX) como salida

	// Configurar Baud Rate
	UBRR0H = (uint8_t)(UBRR_VALUE >> 8);
	UBRR0L = (uint8_t)UBRR_VALUE;

	// Habilitar transmisión y recepción
	UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);

	// Configurar formato: 8 bits de datos, sin paridad, 1 bit de stop
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);

	//sei(); // Habilitar interrupciones globales
}

void UART_writeChar(char c) {
	while (!(UCSR0A & (1 << UDRE0))); // Esperar a que el buffer esté listo
	UDR0 = c; // Enviar carácter
}

void UART_writeText(const char *str) {
	if (str == NULL) return; // Evitar puntero nulo

	while (*str) {
		UART_writeChar(*str++);
	}
}

// Función para verificar si hay un dato disponible
uint8_t UART_available(void) {
	uint8_t available = rxFlag;
	rxFlag = 0;
	return available;
}


char UART_readChar(void) {
	return rxBuffer; // Retornar el carácter recibido
}

// Interrupción de recepción UART
ISR(USART_RX_vect) {
	rxBuffer = UDR0; // Leer dato recibido
	rxFlag = 1; // Marcar dato como disponible
}
