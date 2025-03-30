#ifndef BUZZER_H
#define BUZZER_H

//#include <avr/io.h>
#include <stdint.h>
#include <stdlib.h>

#ifdef __cplusplus

    extern "C" {

#endif

typedef struct buzzer_type {
    volatile uint8_t *port;
    uint8_t pin;
    float duty_cycle; // for volume control
  } buzzer_t;

void create_buzzer(buzzer_t *buzzer, uint8_t pin, volatile uint8_t *port);
void buzzer_play(buzzer_t* buzzer, float freq, uint8_t volume, double interval);
void buzzer_play_f(buzzer_t* buzzer, float freq, float volume, double interval);

#ifdef __cplusplus

    }

#endif

#endif // BUZZER_H