unsigned int wire_thickness = 0;
unsigned int coil_width = 0;
unsigned int number_of_turns = 0;
unsigned int rotation_speed = 0;

unsigned int turn_counter = 0;
unsigned char counter[7];

volatile unsigned int steps_per_coil_width;
volatile unsigned int round = 0;

volatile unsigned char rcbuf[25];
volatile unsigned char rcindex = 0;
volatile unsigned char t;

#include <p18f2550.h>
#include <delays.h>
#include <stdlib.h>
#include "config4.h"
#include "std_lib.h"
#include "timers.h"
#include "serial.h"
#include "stepper.h"
#include "interrupt.h"

void main(void)
{
    TRISB = 0x00;
	LATB = 0;
	CMCON = 0x07;  // turn off comparators
	ADCON1 = 0x06; // turn off analog to digital converters

	reset_array(rcbuf, 12);

    usart_init();
    usart_puts("Connection to winder is successful.\n");

	RCONbits.IPEN = 1;
	IPR1bits.RCIP = 0;
	IPR1bits.TXIP = 0;
	INTCON2bits.TMR0IP = 1;
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;

	while (number_of_turns == 0);

	//disable_serial_port();
	if (rotation_speed > 5 && rotation_speed < 40)
	{
		motor1_step_time = (unsigned int)(1000.0/((float)rotation_speed));
	}
	else motor1_step_time = 100;
	motor2_step_time = (unsigned int)((float)motor1_step_time*(float)(1250.0/(float)wire_thickness));
	steps_per_coil_width = (unsigned int)(200*coil_width/1.25);
	
	init_timer0();

	while(1)
	{
		if (number_of_turns_motor1 >= number_of_turns)
		{
			stop_timer0();
			if (turn_counter != number_of_turns_motor1)
			{
				int_to_string(number_of_turns_motor1, counter);
				usart_put_array(counter);
			}
			usart_puts(" turns...job finished.\n");
			INTCONbits.PEIE = 0;
    		INTCONbits.GIE = 0;
			LATB = 0;
			number_of_turns_motor1 = 0;
		}
		else
		{
			if (number_of_turns_motor1 > turn_counter)
			{
				turn_counter = number_of_turns_motor1;
				int_to_string(turn_counter, counter);
				usart_put_array(counter);
			}
		}
	}
}
