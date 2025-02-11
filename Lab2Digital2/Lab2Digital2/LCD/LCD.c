/*
 * LCD.c
 *
 * Created: 4/02/2025 10:22:42
 *  Author: pablo
 */ 
#include "LCD.h"

void LCD_PORT(char a){
	PORTD = (PORTD & 0x03) | ((a & 0x3F) << 2); 
	PORTB = (PORTB & 0xFC) | ((a >> 6) & 0x03); 
	_delay_ms(20);
}

void LCD_CMD(uint8_t cmd){
	PORTB &= ~(1 << PB2);
	LCD_PORT(cmd);
	//Hace que el LCD pueda recolectar datos 
	PORTB |= (1 << PB3);
	_delay_ms(6);
	//Termina que el LCD pueda recolectar datos 
	PORTB &= ~(1 << PB3);
}

void LCD_CURSOR(char x, char y){
	char pos = (y == 0) ? (0x80 + x) : (0xC0 + x);
	LCD_CMD(pos);
}

void LCD_WRT(uint8_t data){
	//Para datos y no comandos
	PORTB |= (1 << PB2);
	LCD_PORT(data);
	//Hace que el LCD pueda recolectar datos 
	PORTB |= (1 << PB3);
	_delay_ms(4);
	//Termina que el LCD pueda recolectar datos 
	PORTB &= ~(1 << PB3);
}

void LCD_STR(char *str){
	while (*str) {
		LCD_WRT(*str);
		str++;
	}
}

void init_LCD(){
	// DECLARACION DE PINES DE SALIDA DE PANTALLA 
	DDRD |= (1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7);
	DDRB |= (1 << PB0) | (1 << PB1) | (1 << PB2) | (1 << PB3);
	_delay_ms(50);
	
	// 8 bits
	LCD_CMD(0x38);	// 0011 1000
	_delay_ms(5);	
	// Encender la pantalla, ocultar cursor
	LCD_CMD(0x0C);	// 0000 1100 
	_delay_ms(5);
	// 	Modo de entrada: Incrementar cursor después de escribir
	LCD_CMD(0x06);	// 0000 0110 
	_delay_ms(5);
	// Borrar pantalla
	LCD_CMD(0x01);	// 0000 0001
	_delay_ms(5);
	
	
}