#include <buzzer.h>
#include <util/delay.h>
#include <avr/io.h>

static float volumes[10] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0};

/*! @brief Initialise the buzzer object
    @param buzzer The buzzer object
    @param pin The pin the buzzer is connected to
    @param port The port the buzzer is connected to
*/
void create_buzzer(buzzer_t *buzzer, uint8_t pin, volatile uint8_t *port, volatile uint8_t *ddr)
{
  buzzer->port = port;
  buzzer->pin = pin;
  buzzer->duty_cycle = 0.5f; // default 50% volume

  *ddr |= (1 << pin);  // Set the pin as output
  *port &= ~(1 << pin); // Set the pin low (off)
}

/*! @brief Plays a note on a buzzer a set frequency, amplitude and for a set interval
    @param buzzer The buzzer object
    @param freq The frequency of the note
    @param volume The volume of the note (0-9)
    @param interval The interval to play the note for
*/
void buzzer_play(buzzer_t* buzzer, float freq, uint8_t volume, double interval)
{
    float duty_cycle = volumes[volume];
    volatile float period = 1 / freq * 1e6;  // Period in microseconds
    volatile int t_on = duty_cycle * period;
    volatile int t_off = period - t_on;


  for (int j = 0; j < 2e5/ period; j++) {
    *(buzzer->port) |= _BV(buzzer->pin);  // Turn on buzzer
    for(int i = 0; i < t_on; i++) {
      _delay_us(1);
    }

    *(buzzer->port) &= ~_BV(buzzer->pin);  // Turn off buzzer
    for(int i = 0; i < t_off; i++) {
      _delay_us(1);
    }
  }

  // Small delay after sound
  for(int i = 0; i < interval; i++) {
      _delay_ms(1);
  }
}

/*! @brief Plays a note on a buzzer a set frequency, amplitude and for a set interval
    @param buzzer The buzzer object
    @param freq The frequency of the note
    @param volume The volume of the note (0-1)
    @param interval The interval to play the note for
*/
void buzzer_play_f(buzzer_t* buzzer, float freq, float volume, double interval)
{
    float duty_cycle = volume;
    volatile float period = 1 / freq * 1e6;  // Period in microseconds
    volatile int t_on = (int)(duty_cycle * period);
    volatile int t_off = period - t_on;


  for (int j = 0; j < 2e5/ period; j++) {
    *(buzzer->port) |= (1 << buzzer->pin);  // Turn on buzzer
    for(int i = 0; i < t_on; i++) {
      _delay_us(1);
    }

    *(buzzer->port) &= ~(1 << buzzer->pin);  // Turn off buzzer
    for(int i = 0; i < t_off; i++) {
      _delay_us(1);
    }
  }

  // Small delay after sound
  for(int i = 0; i < interval; i++) {
      _delay_ms(1);
  }
}