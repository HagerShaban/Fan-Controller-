 /*
 *
 *  pwm.h
 * Description: header file for generating PWM from Timer0
 *
 */


#ifndef PWM_H_
#define PWM_H_

#include "std_types.h"

/* Description:
  Function responsible for starting PMW in timer 0
*/
void Timer0_PWM_Init(unsigned char duty_cycle);

#endif
