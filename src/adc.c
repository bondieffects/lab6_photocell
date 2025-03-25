#include "adc.h"
#include <avr/io.h>
#include "util/delay.h"

/*! @brief Configures the ADC 
*/
void adc_init(void)
{
    ADMUX |= (  _BV(REFS0) |    // Reference AVCC
                _BV(MUX1) |     // Select ADC channel 3
                _BV(MUX0));     // Clear all MUX bits for channel 0
    ADCSRA |= ( _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0) |  // Prescaler of 128 for 125kHz ADC clock
                _BV(ADIE) |     // Enable interrupts
                _BV(ADEN));     // Enable the ADC
    // ADCSRB = 0 for free-running mode
}

/*! @brief Triggers the start conversion
*/
void adc_start_conversion(void)
{
    ADCSRA |= _BV(ADSC); // trigger the start conversion 
    _delay_ms(10);
}