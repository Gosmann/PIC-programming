// description: describes how to setup a simple blink for entire PORTB register
//
// source code available on: https://github.com/Gosmann/PIC-programming/blob/master/hello_world.c

void main(){
     // config PORTB and TRISB - PORTB AND TRISB REGISTERS (pg. 47 PIC16F887 datasheet)
     // PORTB
     TRISB = 0x00;         // configure all PORTB as digital output
     PORTB = 0x00;         // configure all PORTB as LOW
     
     while(1){             // infinite loop
          PORTB = 0x00;    // sets all PORTB as LOW
          delay_ms(200);   // waits 200ms
          PORTB = 0xFF;    // sets all PORTB as HIGH
          delay_ms(200);   // waits 200ms

     } // end while
} // end main
