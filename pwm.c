 /*
 *
 *  pwm.c
 * Description: Source file for generating PWM from Timer0
 *
 */

#include <avr/io.h>
#include "pwm.h"
#include "gpio.h"


void Timer0_PWM_Init(uint8 duty_cycle)
{

	// Set Timer0 initial value to 0
	TCNT0 = 0;

	// Set the Compare value
	OCR0=(uint8)(((float32) duty_cycle/100)*255);


	// Configure OC0 Pin as output pin
	GPIO_setupPinDirection(PORTB_ID, PIN3_ID, PIN_OUTPUT);

	//Configure the timer control register
	TCCR0 |= ( 1 << WGM00 ) | ( 1 << WGM01 ) | ( 1 << COM01 ) | ( 1 << CS01 );
}
