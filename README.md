# PIC-programming
Aggregates very simple yet handy pieces of code in C for PIC uControllers. 

### PIC16F887 related codes: 
- 01: timer0_int: describes how to setup the timer0 and generate interruptions from its overflow 
- 02:
- [PIC16F887 datasheet](http://ww1.microchip.com/downloads/en/DeviceDoc/41291D.pdf)


#### 01:timer0_int:
   Describes how to setup the timer0 and generate interruptions from its overflow. Major part of code is setting up the hardware configuration registers.
   
   
   INTCON: INTERRUPT CONTROL REGISTER (pg. 31 PIC16F887 datasheet)    
   OPTION_REG: OPTION REGISTER (pg. 30 PIC16F887 datasheet)    
   TRISB - PORTB TRI-STATE REGISTER (pg. 48 PIC16F887 datasheet)
   
   
   Description:
   When using a 16MHz cristal, the instruction cicle clock equals to 4MHz. When using a prescaler set to 1:16, the hardware timer0 will be updated at a 250KHz frequency. The code shows that timer0 just counts from 6~256 (256-6=250), so the timer0 interrup will be updated at a rate of 1KHz and period of 1ms. Setting up an external auxiliar variable to count each time 1ms has passed, and update the RB4_bit pin state, you end up with a precise hardware variable frequency output.  
   
   Timing:     
   - 16MHz/4 = 4MHz    
   - 4MHz/16 = 250KHz    
   - 250KHz/250 = 1KHz = 1ms^-1    
   
   
   References:     
   https://www.mikroe.com/ebooks/pic-microcontrollers-programming-in-c/timer-tmr0    
   https://www.youtube.com/watch?v=K81eMwKZYYw&list=PLZ8dBTV2_5HQ-LrS9r1dP30h8n9sh04gh&index=23    
   http://ww1.microchip.com/downloads/en/DeviceDoc/51702A.pdf    
      
