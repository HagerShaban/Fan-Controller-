 /*
 * adc.c
 * Description: Source file for the ATmega16 ADC driver
 *
 */

#include <avr/io.h>
#include "adc.h"
#include "common_macros.h"

void ADC_init(const ADC_ConfigType * Config_Ptr)
{
	/* ADMUX Register Bits Description:
	 * Insert voltage reference at the last two bits of the register ( REFS1, REFS0 )
	 */
	ADMUX = (ADMUX & 0x3F) | ( ( Config_Ptr -> ref_volt ) << 6 );

	/* ADMUX Register Bits Description:
	 * ADLAR   = 0 right adjusted
	 * MUX4:0  = 00000 to choose channel 0 as initialization
	 */
	ADMUX = (ADMUX & 0xE0);

	/* ADCSRA Register Bits Description:
	 * Insert prescaler at the first three bits of the register ( ADPS2, ADPS1, ADPS0 )
	 * ADPS2:0 = 011 to choose ADC_Clock=F_CPU/8=1Mhz/8=125Khz --> ADC must operate in range 50-200Khz
	 */
	ADCSRA = ( ADCSRA & 0xF8 ) | ( Config_Ptr -> prescaler );

	/* ADCSRA Register Bits Description:
	 * ADEN    = 1 Enable ADC
	 * ADIE    = 0 Disable ADC Interrupt
	 * ADATE   = 0 Disable Auto Trigger
	 */
	ADCSRA = (1<<ADEN);
}

uint16 ADC_readChannel(uint8 channel_num)
{
	// Input channel number must be from 0 to 7
	channel_num &= 0x07;
	//Clear first 5 bits in the ADMUX
	ADMUX &= 0xE0;
	//Choose the correct channel
	ADMUX = ADMUX | channel_num;
	//Start conversion
	SET_BIT(ADCSRA,ADSC);
	 //Wait for conversion to complete
	while(BIT_IS_CLEAR(ADCSRA,ADIF));
	SET_BIT(ADCSRA,ADIF);
	return ADC;
}
