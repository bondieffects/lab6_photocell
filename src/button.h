#ifndef BUTTON_H
#define BUTTON_H

#include <stdint.h>
#include <stdbool.h>


#ifdef __cplusplus

    extern "C" {

#endif

#define DEBOUNCE_INTERVAL 80

typedef struct button_type {
    bool debounced_state;   // because pullup
    uint8_t state;             // the instantaneous state
    bool fell;
    bool rose;              // because pullup
} button_t;

void create_button(button_t *button);

#ifdef __cplusplus

    }

#endif

#endif // BUTTON_H