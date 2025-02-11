/*
 * Lab2Digital2.c
 *
 * Created: 4/02/2025 10:16:38
 * Author : Pablo
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>  
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>


#include "LCD/LCD.h"
#include "ADC/ADC.h"
#include "UART/UART.h"

//------------------ Variables -------------------------------------------
char buffer[16]; 
volatile int16_t contador = 0;


void iniciarADC(uint8_t canal);
void procesarUART(char comando);
float convertirV(uint16_t valorADC);

int main(void) {
    initADC();
    init_LCD();
    UART_init();
    sei();  // Habilita interrupciones globales

    // Mensaje en la LCD (fila superior)
    LCD_CURSOR(1, 0);
    LCD_STR("V1:");
    LCD_CURSOR(7, 0);
    LCD_STR("V2:");
    LCD_CURSOR(13, 0);
    LCD_STR("S3:");

    iniciarADC(0);  // Iniciar la primera conversión del ADC

    while (1) {
        // Convertir valores ADC a voltaje
        float volt1 = convertirV(pot1);
        float volt2 = convertirV(pot2);

        // Mostrar voltajes en la LCD
        LCD_CURSOR(0, 1);
        dtostrf(volt1, 4, 1, buffer);
        LCD_STR(buffer);
        LCD_STR("V");

        LCD_CURSOR(6, 1);
        dtostrf(volt2, 4, 1, buffer);
        LCD_STR(buffer);
        LCD_STR("V");

        // Mostrar contador en la LCD
        LCD_CURSOR(13, 1);
        itoa(contador, buffer, 10);
        LCD_STR(buffer);
        LCD_STR("   ");

        // Verificar voltaje
//         UART_writeText("V1: ");
//         dtostrf(volt1, 4, 0, buffer);
//         UART_writeText(buffer);
//         UART_writeText("V\r\n");
// 
//         UART_writeText("V2: ");
//         dtostrf(volt2, 4, 0, buffer);
//         UART_writeText(buffer);
//         UART_writeText("V\r\n");
// 
//         UART_writeText("S3: ");
//         itoa(contador, buffer, 10);
//         UART_writeText(buffer);
//         UART_writeText("\r\n");

        _delay_ms(250);

        // Manejo de comandos UART
        if (UART_available()) {
            procesarUART(UART_readChar());
        }
    }
}

//------------------ Funciones -----------------------

// Convertir ADC a Voltaje 
float convertirV(uint16_t valorADC){
    return (valorADC * 5.00) / 255.0;
}

// Procesar comandos UART (+ y -)
void procesarUART(char comando) {
    if (comando == '+') {
        contador++; // Incrementar contador
    } else if (comando == '-') {
        contador--; // Decrementar contador
    }
}
