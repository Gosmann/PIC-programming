# PIC-programming
Aggregates very simple yet handy pieces of code in C for PIC uControllers. 

### PIC16F887 related codes: 
- 01: input_output: describes how to setup input and output pins on PORTB and make them interact    
- 02: timer0_int: describes how to setup timer0 and generate interruptions from its overflow     
- 03: timer2_pwm: describes how to setup timer2 and generate a pwm
- 04: rb0_int: describes how to setup RB0/INT/AN12 to generate an interrupt from external rising or falling edge
- [PIC16F887 datasheet](http://ww1.microchip.com/downloads/en/DeviceDoc/41291D.pdf)    

#### 01: input_output    
   Describes how to setup input and output pins on PORTB and make them interact. TRISB and PORTB register are setup in such a way that if the RB7 is set to logic high, PORTB as a whole binary number will be decremented, otherwise, will be incremented. Important to notice the implementation of the portb_mask register, to avoid 'read-modify-write' problems on simulation. It is still disputable if I would bring problems in an actual circuit.
   
#### 02: timer0_int
   Describes how to setup the timer0 and generate interruptions from its overflow. Major part of code is setting up the hardware configuration registers.
   
   
   INTCON: INTERRUPT CONTROL REGISTER (pg. 31 PIC16F887 datasheet)    
   OPTION_REG: OPTION REGISTER (pg. 30 PIC16F887 datasheet)    
   TRISB: PORTB TRI-STATE REGISTER (pg. 48 PIC16F887 datasheet)
   
   
   Description:
   When using a 16MHz crystal, the instruction cycle clock equals to 4MHz. When using a prescaler set to 1:16, the hardware timer0 will be updated at a 250KHz frequency. The code shows that timer0 just counts from 6~256 (256-6=250), so the timer0 interrupt will be updated at a rate of 1KHz and period of 1ms. Setting up an external auxilliar variable to count each time 1ms has passed, and update the RB4_bit pin state, you end up with a precise hardware variable frequency output.  
   
   Timing (using a 16MHz crystal)    
   - 16MHz -> high speed crystal oscillator
   - 16MHz/4 = 4MHz -> internal instructions cycle clock
   - 4MHz/16 = 250KHz -> after prescaler, rate of increment on t0
   - 250KHz/250 = 1KHz = 1ms^-1 -> final overflow interrupt frequency    
   
   
#### 03: timer2_pwm
   Describes how to setup the timer2 to generate a PWM signal and change its duty cycle.
   
   T2CON: TIMER 2 CONTROL REGISTER (pg. 84 PIC16F887 datasheet)    
   CCP1CON: ENHANCED CCP1 CONTROL REGISTER (pg. 126 PIC16F887 datasheet)    
   PR2 - TIMER2 PERIOD REGISTER (pg.83 PIC16F887 datasheet)    
   CCPR1L - CAPTURE/COMPARE/PWM REGISTER 1 LOW BYTE    
   TRISC: PORTC TRI-STATE REGISTER (pg.53 PIC16F887 datasheet)    
   
   Description:    
   The clock input to the timer module is the system instruction clock (Fosc/4). This clock is fed into the timer2 prescaler (1:1, 1:4, 1:16) and the output is used to increment the TMR2 register. The value os TMR2 and PR2 are constantly compared to determine when they match. TMR2 will increment from 0x00 until it matches the value on PR2 and when it occurs TMR2 will reset back to 0x00. The register's setup are better explained in the code and in the datasheet, but It is important to emphasize that:    
   PR2 -> determines when the overflow will occur.    
   CCPR1L -> determines the duty cycle of the PWM signal.    
  
   Timing (using a 16MHz crystal)    
   - 16MHz -> high speed crystal oscillator
   - 16MHz/4 = 4MHz -> internal instructions cycle clock
   - 4MHz/256  = 15.625KHz -> final PWM output frequency


#### 04: rb0_int
   Describes how to setup RB0/INT/AN12 to generate an interrupt from external rising or falling edge. It can be very useful when dealing with any kind of external digital signal processing.   
   
   ANSELH - ANALOG SELECT HIGH REGISTER (pg. 48 PIC16F887 datasheet)
   PORTA and TRISA - PORTA AND TRISA REGISTERS (pg. 39 PIC16F887 datasheet)
   PORTB and TRISB - PORTB AND TRISB REGISTERS (pg. 47 PIC16F887 datasheet)
   OPTION_REG - OPTION REGISTER (pg. 30 PIC16F887 datasheet)    
   INTCON - INTERRUPT CONTROL REGISTER (pg. 31 PIC16F887 datasheet)    
   
   Description:
   When having to deal with any kind of external digital signal processing, It is a key tool being able to generate interrupts on rising or falling edge, because those are when things actually change. When reading signals from an encoder, for instance, it is important to be aware only when the transitions happen. In order to implement this ability, this code configures the ANSELH so that RB0/INT/AN12 is NOT set as an analog input. Configures PORTB and TRISB to ensure that RB0/INT/AN12 will be a digital input pin and PORTA and TRISA to ensure that RA0 and RA1 will be digital input pins. Configures OPTION_REG so that the interrupt happens on a rising edge and most importantly, configures INTCON to generate global interrupts, generate INT (external) interrupts and reset the INT interrupt flag. This way, when a rising edge is detected on RB0/INT/AN12 pin, and interrupt will toggle the logic state on both RA0 and RA1.
   
   
   References:     
   https://www.mikroe.com/ebooks/pic-microcontrollers-programming-in-c/timer-tmr0    
   https://www.youtube.com/watch?v=K81eMwKZYYw&list=PLZ8dBTV2_5HQ-LrS9r1dP30h8n9sh04gh&index=23    
   http://ww1.microchip.com/downloads/en/DeviceDoc/51702A.pdf    
   https://www.youtube.com/watch?v=TtYJtwj8ry8&list=PLZ8dBTV2_5HQ-LrS9r1dP30h8n9sh04gh&index=30
   https://electrosome.com/interrupt-pic-microcontroller/
   https://forum.mikroe.com/viewtopic.php?f=88&t=28287&p=138861
   https://www.youtube.com/watch?v=G68hsqPuU_Y 
   http://www.microchip.com/forums/m413754.aspx
      
 
 
