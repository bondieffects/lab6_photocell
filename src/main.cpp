#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/interrupt.h>

#include "bitwise.h"
#include "usart.h"
#include "adc.h"
#include "buzzer.h"
#include "button.h"
#include "alarm.h"
#include "utility.h"

#define FCPU 16000000
// Pinout
#define PIN_BUZZER_P (PD7) 
#define PORT_BUZZER_P (&PORTD)

// Objects
usart_t debug;
button_t button;
adc_t adc;
photocell_t photocell;
buzzer_t buzzer;
alarm_t alarm;

// Global variables
bool tapped;  // button state
bool mode;    // mode state

inline bool button_tapped(void) {
  if (tapped) {
    tapped = 0;       // reset the flag
    return 1;         // return true
  } else return 0;         // return false
}

// Interrupt Service Routines
ISR(PCINT2_vect)
{
  _delay_ms(DEBOUNCE_INTERVAL); // debounce
  button.state = *(button.pinput) >> button.pin & 1;        // read the pin state

  if (button.state) {                         // updates on rising edge
    button.fell = 0;                          // reset the falling edge flag
    button.rose = 1;                          // set the rising edge flag
    tapped = 1;                               // set the tapped flag on the rising edge
    usart_send_string("Button released\n");
  } else {
    button.fell = 1;                          // set the falling edge flag
    button.rose = 0;                          // reset the rising edge flag
    usart_send_string("Button pressed\n");
  }
}

ISR(ADC_vect)
{
  adc.value = ADC;  // Read the ADC value
}

/*! @Questions:
  1. Where the adc channel is x%6, why %6?
      Because the Arduino has has 5 ADC channels broken out,
      my student ID last digit is 0, so its simple but if it was > 5,
      then % would give the remainder to select the appropriate channel.
  2. 


*/

int main(void)
{
  // Initialise the USART for debugging
  while(!usart_init(&debug, 9600));
  usart_send_string("USART initialised\n");


  // Initialise the button object
  button_create(&button,
    &PORTD,
    &PIND,
    &DDRD,
    PD2,
    18);  // PD2 PCINT18
  button_interrupt_enable(&button);
  usart_send_string("Button initialised\n");

  // Initialise the ADC object
  adc_init(&adc);
  usart_send_string("ADC initialised\n");
  photocell_init(&photocell);
  usart_send_string("Photocell initialised\n");

  create_buzzer(&buzzer, PIN_BUZZER_P, PORT_BUZZER_P);
  usart_send_string("Buzzer initialised\n");
  create_alarm(&alarm);
  usart_send_string("Alarm initialised\n");

  // Enable Interrupts
  sei();


  while (!photocell_calibrate(&photocell, &adc, button_tapped()));
  usart_send_string("Photocell calibration complete\n");

  // Enter the main loop
  while(1) {

    if (button_tapped()) mode = !mode;  // toggle the mode

    adc_start_conversion();
    _delay_ms(10); // for stability

    float volume;

    switch (mode) {
      case 0: // When the ambient light is weakest (photocell_min) the buzzer is loudest, when the ambient light is strongest (photocell_max) the buzzer is quietest.
        volume = linear_map((float)adc.value, (float)photocell.photocell_min, (float)photocell.photocell_max, 1.0f, 0.0f); // Map the ADC value to volume
        break;
      case 1: // When the ambient light is weakest (photocell_min) the buzzer is quietest, when the ambient light is strongest (photocell_max) the buzzer is loudest.
        volume = linear_map((float)adc.value, (float)photocell.photocell_min, (float)photocell.photocell_max, 0.0f, 1.0f); // Map the ADC value to volume
        break;
    }

    usart_send_string("ADC: ");
    usart_send_num(adc.value, 4, 0);
    usart_send_string(", Volume: ");
    usart_send_num(volume, 1, 2);
    usart_send_string("\n\r");
    buzzer_play_f(&buzzer, alarm.frequency, volume, 100);

  }

  return 0;
} // end main
