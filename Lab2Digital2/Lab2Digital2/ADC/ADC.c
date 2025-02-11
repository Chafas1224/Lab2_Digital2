/*
 * ADC.c
 *
 * Created: 4/02/2025 15:49:06
 *  Author: pablo
 */ 

#include "ADC.h"

volatile uint16_t pot1 = 0, pot2 = 0; 
volatile uint8_t canal_adc = 0;       

void initADC(){
	ADMUX = 0;
	// REFERENCIA AVCC = 5V
	ADMUX |= (1 << REFS0);
	ADMUX &= ~(1 << REFS1);
	// JUSTIFICACION A LA IZQUIERDA
	ADMUX |= (1 << ADLAR);
	// PRESCALER 128
	ADCSRA = 0;
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
	// HABILITAR INTERRUPCIÓN DE ADC
	ADCSRA |= (1 << ADIE);
	// HABILITAR ADC
	ADCSRA |= (1 << ADEN);
}

void iniciarADC(uint8_t canal){
	ADMUX = (ADMUX & 0xF8) | (canal & 0x07); // Seleccionar canal
	ADCSRA |= (1 << ADSC);  // Iniciar conversión
}


ISR(ADC_vect){
	if (canal_adc == 0){
		pot1 = ADCH;  // Guardar el valor de ADC0
		canal_adc = 1;
		} else {
		pot2 = ADCH;  // Guardar el valor de ADC1
		canal_adc = 0;
	}
	iniciarADC(canal_adc); // Iniciar la siguiente conversión automáticamente
}
