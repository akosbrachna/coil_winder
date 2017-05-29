volatile unsigned char tmp_TMR0L;

void init_timer0(void)
{
	T0CONbits.T08BIT = 1;	//8 BIT timer
	T0CONbits.T0CS = 0;
	T0CONbits.PSA = 1;  	// No prescale
	TMR0H = 0;
	TMR0L = 225;			// 50us @ 4MHz freq
  	INTCONbits.TMR0IF = 0;  //Clear timer0 overflow interrupt flag
  	INTCONbits.TMR0IE = 1;  //enable the timer0 by setting TRM0IE flag
	INTCON2bits.TMR0IP = 1;
	T0CONbits.TMR0ON = 1;
}

void stop_timer0(void)
{
	tmp_TMR0L = TMR0L;
  	//INTCONbits.TMR0IE = 0;
	T0CONbits.TMR0ON = 0;
}

void start_timer0(void)
{
	TMR0L = tmp_TMR0L;
  	//INTCONbits.TMR0IE = 1;
	T0CONbits.TMR0ON = 1;
}

void init_timer3(void)
{
	T3CONbits.RD16 = 0;		//8 BIT timer
	T3CONbits.T3CKPS0 = 0;	// no prescale
	T3CONbits.T3CKPS1 = 0;	// no prescale
	T3CONbits.TMR3CS = 0;	// internal clock source
	TMR3H = 0;
	TMR3L = 225;			// 50us @ 4MHz freq
  	PIR2bits.TMR3IF = 0;  	//Clear timer0 overflow interrupt flag
  	PIE2bits.TMR3IE = 1;  	//enable the timer0 by setting TRM0IE flag
	T3CONbits.TMR3ON = 1;
}
