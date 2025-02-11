/*
 * LCD.h
 *
 * Created: 4/02/2025 10:22:31
 *  Author: pablo
 */

#ifndef LCD_H_
#define LCD_H_

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h> 

void LCD_PORT(char a);
void LCD_CMD(uint8_t cmd);
void LCD_CURSOR(char x, char y);
void LCD_WRT(uint8_t data);
void LCD_STR(char *str);
void init_LCD(void);

#endif /* LCD_H_ */
