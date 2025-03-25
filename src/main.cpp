#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/interrupt.h>

#include "bitwise.h"
#include "usart.h"
#include "buzzer.h"
#include "button.h"
#include "alarm.h"

#define FCPU 16000000
// Pinout
#define PIN_BUZZER_P (PD2) 
#define PORT_BUZZER_P (&PORTD)
#define BUTTON_CASE1 (PD3)
#define BUTTON_CASE2 (PD4)

// Global Variables
button_t button_case1, button_case2;
buzzer_t buzzer;
alarm_t alarm;
int adc = 0;

// Interrupt Service Routines
ISR(PCINT2_vect)
{
  _delay_ms(DEBOUNCE_INTERVAL); // debounce
  button_case1.state = PIND >> BUTTON_CASE1 & 1;  // read the pin state

  if (button_case1.state) {                        // updates on rising edge
        alarm.volume = (alarm.volume + 1) % 2;
        usart_send_string(">case number:");
        usart_send_num(alarm.volume, 0, 0);
        usart_send_string("\n");
  }
}

ISR(ADC_vect){
  adc = ADC;
}

int main(void)
{
   /////////////////////////// PIN CONFIGURATION ///////////////////////////
    usart_init(9600);
    DDRD |= (1 << PIN_BUZZER_P);
    DDRD &= ~((1 << BUTTON_CASE1) | (1 << BUTTON_CASE2));
    PORTD |= ((1 << BUTTON_CASE1) | (1 << BUTTON_CASE2)); // set the bit to enable pullup

    /////////////////////////// INTERRUPT CONFIGURATION ///////////////////////////

    // Configure External Interrupt for CASE 1 button (INT1)
    EIMSK |= (1 << INT1);                 // enable INT1
    EICRA |= (1 << ISC11) | (1 << ISC10); // rising edge

    // Configure Pin Change Interrupt for CASE 2 button (PCINT20)
    PCICR |= (1 << PCIE2);          // enables the interrupts on PORTD
    PCMSK2 |= (1 << PCINT20);       // enables PCINT20
    /////////////////////////// CREATE OBJECTS ///////////////////////////
      // Create the buzzer, alarm and button objects
      create_button(&button_case1);
      create_button(&button_case2);
      usart_send_string("buttons created\n");
    
    while (1)
    {
        bitSet(ADMUX, REFS0);
        bitSet(ADMUX, MUX1); // 1 
        bitSet(ADMUX, MUX0); // 1 
        //since result is 11 therefore channel used is ADC3 since 11 = 3 in binary
        ADCSRA |= 0b111 < 0;
        bitSet(ADCSRA, ADIE);
        bitSet(ADCSRA, ADEN);
      
        sei();
      
        bitSet(ADCSRA, ADSC);
        _delay_ms(10);
      
        while(1){
          bitSet(ADCSRA, ADSC);
          usart_send_string(">adc:");
          usart_send_num(adc, 4, 0);
          usart_send_string("\n");
          _delay_ms(100);
        }
            //buzzer_play(&buzzer, alarm.frequency, alarm.volume, 100);
            switch ((int)adc){
              case 0 ... 400:
                buzzer_play(&buzzer, 220, alarm.volume, 50);
                break;
              case 401 ... 500:
                buzzer_play(&buzzer, 440, alarm.volume, 50);
                break;
              case 501 ... 600:
                buzzer_play(&buzzer, 880, alarm.volume, 50);
                break;
            }
          }
    return 0;
} // end main
