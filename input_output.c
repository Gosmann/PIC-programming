// description: Describes how to setup input and output pins on PORTB and make them interact. 
//              TRISB and PORTB register are setup in such a way that if the RB7 is set to HIGH,
//              PORTB as a whole binary number will be decremented, otherwise, will be incremented.
//              Important to notice the implementation of the portb_mask register, to avoid 'read-
//              modify-write' problems on simulation.

unsigned short portb_mask = 0x00;   // auxiliar variable atached to PORTB state
                                    // very important to avoid 'read-modify-write' problem in simulation
                                    
void main() {
    // GENERAL PORTB REGISTERS - PORTB AND TRISB REGISTER (pg. 47 PIC16F887 datasheet)
    TRISB = 0x00;           // sets all PORTB register as OUTPUT
    TRISB.RB7 = 0x01;       // configures RB7 pin as an INPUT

    PORTB = 0x00;           // sets all PORTB pins as LOW
    portb_mask = 0x00;      // sets all PORTB register mask as low

    while(1){
        if(PORTB.RB7)portb_mask--;      // if logic level on RB7 pin is HIGH
                                        // then portb_mask will be decremented
        else portb_mask++;              // if logic level on RB7 pin is LOW
                                        // then portb_mask will be incremented

        PORTB = portb_mask;             // sets the value on mask to the actual value on PORTB
        delay_ms(250);                  // waits a little, could be implemented on an interrupt

    } // end while
} // end main
