#include "adc.h"
#include <avr/io.h>
#include "util/delay.h"
#include "usart.h"

/*! @brief Configures the ADC 
*/
void adc_init(adc_t *adc)
{
    ADMUX |= _BV(REFS0);                                // Clear all MUX bits for channel 0
    ADCSRA |= ( _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0) |  // Prescaler of 128 for 125kHz ADC clock
                _BV(ADIE) |                             // Enable interrupts
                _BV(ADEN));                             // Enable the ADC
    // ADCSRB = 0 for free-running mode

    adc->value = 0;         // Initialise to 0
}

/*! @brief Triggers the start conversion
*/
void adc_start_conversion(void)
{
    ADCSRA |= _BV(ADSC); // trigger the start conversion 
    _delay_ms(10);
}

/*! @brief Initialise the photocell values */
void photocell_init(photocell_t *photocell)
{
    photocell->photocell_min = 1023; // Set high so can calibrate down
    photocell->photocell_max = 0;    // Set low so can calibrate up
}

/*! @brief Automatically calibrate the photocell min and max values
    @param photocell: the photocell object
    @note Should be called after the ADC is initialised and the ADC interrupt is enabled.
*/
bool photocell_calibrate(photocell_t *photocell, adc_t *adc, bool input)
{
    adc_start_conversion();
    _delay_ms(10); // Wait for the ADC to settle

    if (adc->value < photocell->photocell_min) {
        photocell->photocell_min = adc->value; // Set the minimum value
        usart_send_string("photocell_min: ");
        usart_send_num(photocell->photocell_min, 3, 0);
        usart_send_string("\n\r");
    }
    if (adc->value > photocell->photocell_max) {
        photocell->photocell_max = adc->value; // Set the maximum value
        usart_send_string("photocell_max: ");
        usart_send_num(photocell->photocell_max, 4, 0);
        usart_send_string("\n\r");
    }
    if (input) return 1;    // escape when the button is pressed
    else return 0;
}



