// description: When having to deal wiht any kind of external digital signal processing, It is a key tool being able to generate 
//              interrupts on rising or falling edge, because those are when things actually change. When reading signals from an 
//              encoder, for instance, it is important to be aware only when the transistions happen. In order to implement this 
//              ability, this code configures ANSELH, PORTX, TRISX, OPTION_REG and INTCON so that when a rising edge is detected
//              on RB0/INT/AN12 pin, and interrupt will toggle the logic state on both RA0 and RA1.
//              Configuring the ANSELH register is extremely important

unsigned short porta_mask = 0x00;         // creates a mask variable for PORTA register

void interrupt(){                         // an interrupt occured
     if(INTCON.INTF){                     // if the external interrupt flag is TRUE
          porta_mask = ~porta_mask;       // toogles the state of porta_mask variable
          INTCON.INTF = 0x00;             // clean the external interrupt flag
     } // end if external interrupt
} // end interrupt function

void main() {
     // config ANSELH - ANALOG SELECT HIGH REGISTER (pg. 48 PIC16F887 datasheet) 
     ANSELH.ANS12 = 0x00;      // configures RB0/INT/AN12 pin as NOT an analog input

     // config PORTB and TRISB - PORTB AND TRISB REGISTERS (pg. 47 PIC16F887 datasheet)
     // PORTB
     TRISB.RB0 = 0x01;         // configure RB0/INT/AN12 pin as digital input
     PORTB.RB0 = 0x00;         // configure RB0/INT/AN12 as LOW (good practice)

     // PORTA
     TRISA.RA0 = 0x00;         // configure RA0 pin as an output
     TRISA.RA1 = 0x00;         // configure RA1 pin as an output
     PORTA.RA0 = 0x00;         // configure RA0 as output LOW
     PORTA.RA1 = 0x00;         // configure RA1 as output LOW

     // config OPTION_REG - OPTION REGISTER (pg. 30 PIC16F887 datasheet)
     OPTION_REG.INTEDG = 0x01;     // interrupt on rising edge of INT pin

     // config INTCON - INTERRUPT CONTROL REGISTER (pg. 31 PIC16F887 datasheet)
     INTCON.GIE  = 0x01;          // enables global interrupt bit
     INTCON.PEIE = 0x00;          // disable peripheral interrupt bit
     INTCON.INTE = 0x01;          // enable external interrupt bit
     INTCON.INTF = 0x00;          // reset the external interrupt flag

     while(1){                    // infinite loop
          PORTA = porta_mask;     // sets the porta_mask value to actual PORTA register
     } // end while
} // end main
