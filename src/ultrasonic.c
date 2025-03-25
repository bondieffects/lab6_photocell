#include "ultrasonic.h"

// Public Implementation
void create_ultrasonic_sensor(ultrasonic_sensor_t *sensor, 
    uint8_t trigger_pin, volatile uint8_t *trigger_port, volatile uint8_t *trigger_ddr,
    uint8_t echo_pin, volatile uint8_t *echo_port, volatile uint8_t *echo_port_in, volatile uint8_t *echo_ddr) {

    sensor->trigger_pin = trigger_pin;
    sensor->trigger_port = trigger_port;
    sensor->trigger_ddr = trigger_ddr;

    sensor->echo_pin = echo_pin;
    sensor->echo_port = echo_port;
    sensor->echo_port_in = echo_port_in;
    sensor->echo_ddr = echo_ddr;

    sensor->echo_duration_us = 0; 
    sensor->timeout_us = 30000;     // default timeout ~5m maximum range
}