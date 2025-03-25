#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>

#include "bitwise.h"

#ifdef __cplusplus

    extern "C" {

#endif

#define SOUND_VELOCITY (343)
#define ALARM_THRESHOLD (60)

typedef struct ultrasonic_sensor_type {
    // Pin configuration
    uint8_t trigger_pin;
    volatile uint8_t *trigger_port;
    volatile uint8_t *trigger_ddr;

    uint8_t echo_pin;
    volatile uint8_t *echo_port;
    volatile uint8_t *echo_port_in;
    volatile uint8_t *echo_ddr;

    // Measurement properties
    uint32_t echo_duration_us;
    uint16_t timeout_us;
} ultrasonic_sensor_t;

// Function prototypes
void create_ultrasonic_sensor(ultrasonic_sensor_t *sensor, 
                         uint8_t trigger_pin, volatile uint8_t *trigger_port, volatile uint8_t *trigger_ddr,
                         uint8_t echo_pin, volatile uint8_t *echo_port, volatile uint8_t *echo_port_in, volatile uint8_t *echo_ddr);

#ifdef __cplusplus

    }

#endif

#endif