#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/interrupt.h>

#include "bitwise.h"
#include "usart.h"

#define FCPU 16000000

// Global Variables
usart_t debug_uart;

// Interrupt Service Routines
ISR(USART_RX_vect)
{
  // buffer the received data
  uint8_t data = UDR0;
  //usart_send_string("data received: ");
  //usart_send_byte(data);      // echo for debugging

  // increment the head and wraparound
  uint8_t write_head = (debug_uart.write + 1) % BUFFER_SIZE;

  // store the data if the buffer isn't full
  if (write_head != debug_uart.read) {
    debug_uart.buffer[debug_uart.write] = data;
    debug_uart.write = write_head;
  }
}

int main(void)
{
    /////////////////////////// CREATE OBJECTS ///////////////////////////
    usart_init(&debug_uart, 9600);

    sei();                          // enable global interrupts

    while (1)
    {
      // 
    }

    return 0;
} // end main

