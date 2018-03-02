// description:

unsigned short int counter  = 0;

void main() {

    // TIMER2 REGISTERS
    // T2CON: TIMER 2 CONTROL REGISTER (pg. 84 PIC16F887 datasheet)
    T2CON = 0x00;            // TIMER2 has prescaler and prescaler set to 1:1
    T2CON.TMR2ON = 0x01;     // TIMER2 is turned ON
    
    // CCP1CON: ENHANCED CCP1 CONTROL REGISTER (pg. 126 PIC16F887 datasheet)
    CCP1CON = 0x00;          // TIMER2 is assigned as single output on P1A/RC4
                             // duty cicle least significant bits are set to low, going to use 8-bit resolution
    CCP1CON.CCP1M3 = 0x01;   // TIMER2 is set to PWM mode
    CCP1CON.CCP1M2 = 0x01;   // PWM on P1A/RC4 is set to active high

    // PR2 - TIMER2 PERIOD REGISTER (pg.83 PIC16F887 datasheet)
    PR2 = 0xFF;              // TIMER2 will count till this value to overflow

    // CCPR1L - CAPTURE/COMPARE/PWM REGISTER 1 LOW BYTE
    CCPR1L = 0;            // sets the duty cicle of the PWM (0~255)

    // REGISTRADORES GERAIS DO PORTC
    TRISC = 0x00;           // sets all PORTC to start as output
    PORTC = 0x00;           // starts all PORTC in LOW

    while(1){
             CCPR1L = counter;
             counter++;
             if(counter==256)counter=0;
             delay_ms(10);
             
    } // end while
    
} // end main