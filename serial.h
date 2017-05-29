void usart_init(void)
{
	BAUDCONbits.BRG16 = 0;

    TXSTAbits.TXEN = 1;
    TXSTAbits.BRGH = 1;
    RCSTAbits.CREN = 1;

    TRISCbits.TRISC7 = 1;
    TRISCbits.TRISC6 = 1;

    SPBRG = 25;  // 4MHz crystal, 9600 baud rate

    PIE1bits.RCIE = 1;
    RCSTAbits.SPEN = 1;
}

void disable_serial_port(void)
{
	PIE1bits.RCIE = 0;
    RCSTAbits.SPEN = 0;
	RCSTAbits.CREN = 0;
}

void usart_putc(unsigned char c)
{
    while(!TXSTAbits.TRMT);
    TXREG = c;
}

void usart_puts(rom char *Message)
{
	rom char *Pos = Message;

    while(*Pos!=0)
        usart_putc(*Pos++);
}

void usart_put_array(unsigned char m[])
{
	unsigned char Pos = 0;

    while(m[Pos]!=0)
	{
        usart_putc(m[Pos]);
		Pos++;
	}
}
