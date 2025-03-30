#ifndef BUTTON_H
#define BUTTON_H

#include <stdint.h>
#include <stdbool.h>


#ifdef __cplusplus

    extern "C" {

#endif

#define DEBOUNCE_INTERVAL 80

typedef struct button_type {
    volatile uint8_t *port; // the PORT register (i.e. &PORTD)
    volatile uint8_t *pinput;  // the PIN register (i.e. &PIND)
    volatile uint8_t *ddr;  // the DDR register (i.e. &DDRD)

    uint8_t pin;            // the pin number (i.e. PD2)
    uint8_t pcint_num;      // the pin change interrupt number (i.e. 18 not PCINT18)

    bool debounced_state;   // because pullup
    uint8_t state;          // the instantaneous state
    bool fell;
    bool rose;              // because pullup
} button_t;

void button_create( button_t *button,
                    volatile uint8_t *port,
                    volatile uint8_t *pinput,
                    volatile uint8_t *ddr,
                    uint8_t pin,
                    uint8_t pcint_num);

void button_interrupt_enable(button_t *button);

#ifdef __cplusplus

    }

#endif

#endif // BUTTON_H