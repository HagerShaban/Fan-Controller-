/*
 * main.c
 * Created on: FEB 20, 2022
 * Author: Hager
 *[Description]: Design a temperature-controlled fan using ATmega16 Microcontroller
 * in which the fan is automatically turned ON or OFF according to the temperature.
 *
 */


#include "lcd.h"
#include "dc_motor.h"
#include "lm35_sensor.h"
#include "adc.h"

int main(void)
{

	 unsigned char temp;  //Variable to store the result from the temp sensor

	 //Initialize ADC Drive
	ADC_ConfigType configured_initialization = { INTERNAL, F_CPU_8 }; /* Create a configured structure to initialize ADC with */
	ADC_init(&configured_initialization); /* Initialize ADC by calling its init function */

	 // Initialize LCD Drive
	LCD_init();

	 //Initialize DC Motor Driver
	DcMotor_Init();

	 //Display ( Fan is .... ) only once at the first row of the LCD
	LCD_moveCursor(0,5);
	LCD_displayString("FAN is ");

	 //Display ( Temp = .... C ) only once at the first row of the LCD
	LCD_moveCursor(1,5);
	LCD_displayString("Temp =    C");


    while(1)
	{

		temp = LM35_getTemperature(); /* Get the temperature from the sensor */


		 //Display the temperature every time at the same location

		LCD_moveCursor(1,13); /* Move the cursor to the second row with suitable location */

		if( temp >= 100 )
		{
			LCD_intgerToString( temp );
		}
		else
		{
			LCD_intgerToString( temp );

			/* In case the temp is three, two, or one
			 * Print a space after the value to overwrite the previous digit in this location
			 */
			LCD_displayCharacter(' ');
		}

		LCD_moveCursor(0,12); /* Move the cursor to the first row with suitable location */

		if ( temp < 30 )
		{
            LCD_displayString("OFF");
			DcMotor_Rotate(OFF,0);      /* Turn off the motor and assign its speed to ZERO */
		}
		else if ( temp >= 30 && temp < 60 )
		{
			LCD_displayString("ON");
			LCD_displayCharacter(' ');
			DcMotor_Rotate(CW,25);      /* Turn on the motor with 25% of its speed */
		}
		else if ( temp >=60 && temp < 90 )
		{
			LCD_displayString("ON");
			DcMotor_Rotate(CW,50);      /* Turn on the motor with 50% of its speed */
		}
		else if ( temp >=90 && temp < 120 )
		{
			LCD_displayString("ON");
			DcMotor_Rotate(CW,75);      /* Turn on the motor with 75% of its speed */
		}
		else if ( temp >=120 )
		{
			LCD_displayString("ON");
			DcMotor_Rotate(CW,100);     /* Turn on the motor with 100% of its speed */
		}

	}
}
