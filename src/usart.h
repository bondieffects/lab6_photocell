#ifndef USART_H
#define USART_H

#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>

#ifdef __cplusplus

    extern "C" {

#endif

#define BUFFER_SIZE (20)
#define ERR (0xFF)                  // Error value for if the buffer is empty

typedef struct {
    uint8_t write;                  // The write index of the buffer
    uint8_t read;                   // The read index of the buffer
    uint8_t buffer[BUFFER_SIZE];

    bool read_complete;                  // deprecated from non-interrupt example
} usart_t;

void usart_init(usart_t* usart, float baud);
void usart_send_byte(const unsigned char data);
void usart_send_string(const char *pstr);
void usart_send_num(float num, char num_int, char num_decimal);
void usart_read_string(usart_t* usart, char *ptr);
void usart_flush(void);
uint8_t usart_available(usart_t* usart);
uint8_t usart_read(usart_t* usart);

#ifdef __cplusplus

    }

#endif

#endif