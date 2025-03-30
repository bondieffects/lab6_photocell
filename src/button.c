#include "button.h"
#include <avr/io.h>
#include "usart.h"

/**
 * @brief Initialise a button.
 * @param button Pointer to button object.
 * @param port PORTx register (i.e. &PORTB)
 * @param pinput PINx register (i.e. &PINB)
 * @param ddr DDRx register (i.e. &DDRB)
 * @param pin Pin number register (i.e. PB0)
 * @param pcint_num The PCINT number for this pin (0-23)
 */
void button_create( button_t *button,
                    volatile uint8_t *port,
                    volatile uint8_t *pinput,
                    volatile uint8_t *ddr,
                    uint8_t pin,
                    uint8_t pcint_num)
{
  // Save pin and port information
  button->port = port;
  button->pinput = pinput;
  button->ddr = ddr;
  button->pin = pin;
  button->pcint_num = pcint_num;

  // Initialise state
  button->debounced_state = 1;  // Pull-up enabled
  button->state = 1;
  button->fell = 0;
  button->rose = 1;

  // Configure pin direction
  *button->ddr &= ~(1 << button->pin);  // Set as input
  *button->port |= (1 << button->pin);  // Enable pull-up
}

/*! @brief Enables the Pin Change interrupt for the selected pin */
void button_interrupt_enable(button_t *button)
{
    uint8_t pcint_group = button->pcint_num / 8;  // Get the group number (0-2)
    usart_send_string("pcint_group: ");
    usart_send_num(pcint_group, 1, 0);
    usart_send_string("\n\r");
    uint8_t pcint_bit = button->pcint_num % 8;    // Get the bit number
    usart_send_string("pcint_bit: ");
    usart_send_num(pcint_bit, 1, 0);
    usart_send_string("\n\r");

    PCICR |= _BV(pcint_group);  // Enable pin change interrupt for the group

    // Enable PCINT pin
    switch (pcint_group) {
        case 0:
            PCMSK0 |= _BV(pcint_bit);
            break;
        case 1:
            PCMSK1 |= _BV(pcint_bit);
            break;
        case 2:
            PCMSK2 |= _BV(pcint_bit);
            break;
        default:
            // Invalid PCINT group
            break;
    }
}