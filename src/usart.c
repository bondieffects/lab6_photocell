#include "usart.h"
#include <stdlib.h>
#include <math.h>
#include "bitwise.h"
#include <util/delay.h>
#include <string.h>

/*! @brief Initializes the USART communication
    @param baud: the baud rate of the communication
    @return 1 when success
*/
bool usart_init(usart_t* usart, float baud)
{
    UBRR0 = 103;                // Set baud rate to 9600
    UCSR0B |=   _BV(RXCIE0) |   // enable RX interrupt
                _BV(TXEN0) |    // enable TX
                _BV(RXEN0);     // enable RX

    // enable RX complete interrupt
    UCSR0A |= _BV(RXC0);

    // Set frame format: 8 data, 1 stop bit
    UCSR0C |= _BV(UCSZ01) | _BV(UCSZ00);

    // Initialize the usart object
    usart->write = 0;
    usart->read = 0;

    return 1;
}

/*! @brief Sends a byte over USART
    @param data: the byte to send
*/
void usart_send_byte(const unsigned char data)
{
    while (!bitCheck(UCSR0A, UDRE0))
    ;
    UDR0 = data;
}

/*! @brief Sends a string over USART
    @param pstr: the string to send
*/
void usart_send_string(const char *pstr)
{
    while (*pstr != '\0')
    {
    usart_send_byte(*pstr);
    pstr++;
    }
}

/*! @brief Prints a floating point number
    @param num: the number to print
    @param num_int: the number of integer places
    @param num_decimal: the number of decimal places
*/
void usart_send_num(float num, char num_int, char num_decimal)
{
    char str[20];
    if (num_decimal == 0)
    dtostrf(num, num_int, num_decimal, str);
    else
    dtostrf(num, num_int + num_decimal + 1, num_decimal, str);
    str[num_int + num_decimal + 1] = '\0';
    usart_send_string(str);
}

/*! @brief Reads a string from the USART without using interrupts
    @param ptr: the pointer to store the string
*/
void usart_read_string(usart_t* usart, char *ptr)
{
    char tmp;
    while (1)
    {
        while (!bitCheck(UCSR0A, RXC0));
        tmp = UDR0;
        if (tmp == '\r' || tmp == '\n')
        {
            *ptr = '\0';
            usart->read_complete = 1;
            return;
        }
        else
        {
            *ptr++ = tmp;
        }
    }
}

/*! @brief Flushes the USART buffer
*/
void usart_flush(void)
{
    while (bitCheck(UCSR0A, RXC0))
    {
        UDR0;
    }
}

/*! @brief Checks how many bytes are available in the buffer
    @param usart: the usart object
    @return the number of bytes available before overrun
*/
uint8_t usart_available(usart_t* usart)
{
    return (usart->write - usart->read) % BUFFER_SIZE;  // Calculates how many bytes in use,
                                                        // and gives the remainder (n available bytes)
}

/*! @brief pulls data from the buffer
    @param usart: the usart object
    @return the data from the buffer
*/
uint8_t usart_read(usart_t* usart)
{
    //usart_send_string("usart_read\n\r");
    _delay_ms(10);
    if (usart->write == usart->read) {
        usart->read_complete = 1; 
        return ERR;     // no delta between write and read
    }

    usart->read_complete = 0;                       // reset the read complete flag
    uint8_t data = usart->buffer[usart->read];      // pull the data from the buffer
    usart->read = (usart->read + 1) % BUFFER_SIZE;  // Increment the read and wraparound
    return data;
}