void high_isr(void);
void low_isr(void);

#pragma code high_vector=0x08
void high_interrupt(void)
{
	_asm GOTO high_isr _endasm
}
#pragma code

#pragma interrupt high_isr
void high_isr(void)
{
	if (INTCONbits.TMR0IF)
	{
		TMR0L = 225;
  		INTCONbits.TMR0IF = 0;
		if (motor1_current_step == motor1_step_time)
		{
			if (number_of_steps_motor1 >= 200)
			{
				number_of_steps_motor1 = 0;
				number_of_turns_motor1++;
			} else number_of_steps_motor1++;
			motor1_current_step = 0;
			if (motor1_step_index > 3)
			{
				motor1_step_index = 0;
			}
			temp_motor = LATB & 0b11110000;
			LATB = steps1f[motor1_step_index] | temp_motor;
			motor1_step_index++;
		}
		else motor1_current_step++;

		if (motor2_current_step == motor2_step_time)
		{
			motor2_current_step = 0;
			round++;
			if (round > steps_per_coil_width)
			{
				round = 0;
				if (motor2_direction == forward) 
					motor2_direction = backward;
				else motor2_direction = forward;
				motor2_step_index = 0;
			}
			if (motor2_step_index > 3)
			{
				motor2_step_index = 0;
			}
			temp_motor = LATB & 0b00001111;
			if (motor2_direction == forward)
			{
				LATB = temp_motor | steps1f_motor2[motor2_step_index];
			}
			else LATB = temp_motor | steps1b_motor2[motor2_step_index];
			motor2_step_index++;
		}
		else motor2_current_step++;
    }
}

#pragma code low_vector=0x18
void low_interrupt(void)
{
	_asm GOTO low_isr _endasm
}
#pragma code
#pragma interruptlow low_isr
void low_isr (void)
 {
   	if (PIR1bits.RCIF)
	{
        t = RCREG;

		switch(t) 
		{
			case 'C' :
				usart_puts("Connection to winder is successful.\n");
			   	break;
			case 'Z' :
				rcbuf[rcindex] = 0;
	            rcindex = 0;
				string_to_int(rcbuf);
	            usart_puts("data received. winding started...\n");
				break;
			case 'P' :
				if (T0CONbits.TMR0ON == 1) 
				{
					stop_timer0();
					usart_puts("winding paused...\n");
				}
				else 
				{
					usart_puts("winding resumed...\n");
					start_timer0();
				}
			   	break;
			case 'S' :
			   	number_of_turns_motor1 = number_of_turns;
			   	break;
			default :
			   	rcbuf[rcindex] = t;
            	rcindex++;
   		}
	    PIR1bits.RCIF = 0;
	}
}
