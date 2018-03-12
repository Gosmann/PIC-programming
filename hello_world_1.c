// description: Describes how to setup the timer0 and generate interruptions from its overflow.
//              Major part of code is setting up the hardware configuration registers.
//
//              source code: https://github.com/Gosmann/PIC-programming/blob/master/hello_world_1.c

int counter = 0x00;                 // starts in zero (0) auxiliar variable to count number of interruptions
int treshold = 30;                  //
unsigned short int value = 0x00;    // auxiliar variable to change RB4_bit state

// code for timer0 overflow interruption
void interrupt(){
     counter++;                     // increments timer count
     TMR0 = 0x06;                   // starts counter register in "6"
     T0IF_bit = 0x00;               // clean the timer0 overflow flag

     if(counter >= treshold){       // if counter variable is greater/equal to treshold value
         counter = 0;               // sets the counter variable back to zero
         value = ~value;            // inverts the state of variable "value"
     }
     
     PORTB = value;                 // refresh the state on PORTB
     
}    // end interrupt

// main code
void main() {
     // configuracao do OPTION_REG - OPTION REGISTER (pg. 30 PIC16F887 datasheet)
     OPTION_REG.NOT_RBPU = 0x01;        // disables pull-ups on PORTB
     OPTION_REG.T0CS = 0x00;            // sets internal instruction clock cicle to timer0 -> (Fosc/4)
     OPTION_REG.PSA = 0x00;             // prescaler é assinalado com o módulo do timer0
     PS2_bit      = 0x01;               // seta o prescaler em 1:256
     PS1_bit      = 0x01;               // seta o prescaler em 1:256
     PS0_bit      = 0x01;               // seta o prescaler em 1:256

     // configuracao do INTCON - INTERRUPT CONTROL REGISTER (pg. 31 PIC16F887 datasheet)
     INTCON.GIE = 0x01;                 // enables global interrupt
     INTCON.T0IE = 0x01;                // enables overflow interrupt on timer0
     
     TMR0 = 0x06;                       // starts timer register on "6"

     // configuracao do PORTB
     TRISB = 0x00;                      // enables whole PORTB as an output
     PORTB = 0x00;                      // define all PORTB as LOW

     while(1){                          // infinite loop

     } // end while()
} // end main()
