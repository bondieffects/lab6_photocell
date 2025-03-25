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
#define BUTTON (PD3)


// Global Variables
button_t button;
buzzer_t buzzer;
alarm_t alarm;
int adc = 0;

// Interrupt Service Routines
ISR(INT1_vect)
{
  _delay_ms(DEBOUNCE_INTERVAL); // debounce
  button.state = PIND >> BUTTON & 1;        // read the pin state
  if (button.state) {                          // updates on rising edge
    alarm.enabled = !alarm.enabled;       // Toggle the alarm enable flag
    usart_send_string(">case number:");
    usart_send_num(alarm.enabled, 0, 0);
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
    DDRD &= ~((1 << BUTTON) | (1 << BUTTON));
    /////////////////////////// INTERRUPT CONFIGURATION ///////////////////////////
    // Configure External Interrupt for CASE 1 button (INT1)
    EIMSK |= (1 << INT1);                 // enable INT1
    EICRA |= (1 << ISC11) | (1 << ISC10); // rising edge
    /////////////////////////// CREATE OBJECTS ///////////////////////////
    // Create the buzzer, alarm and button objects
    create_buzzer(&buzzer, PIN_BUZZER_P, PORT_BUZZER_P);
    usart_send_string("buzzer created\n");
    create_button(&button);
    usart_send_string("button created\n");
    while (1){
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
