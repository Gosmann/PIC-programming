int counter = 0x00;     // starts in zero (0) auxiliar variable to count number of interruptions
int treshold = 1;       // number of ms (miliseconds) to treshold -> treshold = period*2
int value;              // auxiliar variable to change RB4_bit state

    // code for timer0 overflow interruption
void interrupt(){
     counter++;                     // increments timer count
     TMR0 = 0x06;                   // starts counter register in "6"
     T0IF_bit = 0x00;               // clean the timer0 overflow flag

     if(counter >= treshold){       // if counter variable is greater/equal to treshold value
         counter = 0;               // sets the counter variable back to zero
         value = ~value;            // inverts the state of variable "value"
     }
}    // end interrupt

     // main code
void main() {
     // configuracao do OPTION_REG - OPTION REGISTER (pg. 30 PIC16F887 datasheet)
     NOT_RBPU_bit = 0x01;               // disables pull-ups on PORTb
     T0CS_bit     = 0x00;               // sets internal instruction clock cicle to timer0 -> (Fosc/4)
     PSA_bit      = 0x00;               // prescaler é assinalado com o módulo do timer0
     PS2_bit      = 0x00;               // seta o prescaler em 1:16
     PS1_bit      = 0x01;               // seta o prescaler em 1:16
     PS0_bit      = 0x01;               // seta o prescaler em 1:16

     // configuracao do INTCON - INTERRUPT CONTROL REGISTER (pg. 31 PIC16F887 datasheet)
     GIE_bit  = 0x01;                   // enables global interrupt
     T0IE_bit = 0x01;                   // enables overflow interrupt on timer0
     TMR0     = 0x06;                   // starts timer register on "6"

     // configuracao do PORTB
     TRISB = 0x00;                      // enables hole PORTB as an output
     PORTB = 0x00;                      // define o estado dessa saída como nível lógico baixo (0)

     while(1)                           // infinite loop
              RB4_bit = value;          // refresh RB4 pin state

     }        // end while(1)
     
}    // end main()