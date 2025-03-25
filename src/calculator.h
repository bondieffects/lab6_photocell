#ifndef CALCULATOR_H
#define CALCULATOR_H

//#include <avr/io.h>
#include <stdint.h>
#include <stdlib.h>
#include "usart.h"
#include "string.h"

#ifdef __cplusplus

    extern "C" {

#endif

typedef enum {
    STATE_MENU,
    STATE_FIRST_NUM,
    STATE_SECOND_NUM,
    STATE_RESULT
} calc_state_t;

typedef enum {
    OP_ADD = 1,
    OP_SUB,
    OP_MUL,
    OP_DIV,
    OP_REM,
    OP_POW,
    OP_LOG,
    OP_SIN,
    OP_COS
} calc_op_t;

typedef struct {
    calc_state_t state;
    calc_op_t operation;
    float first_num;
    float second_num;
    float result;
} calc_t;

void calculator_init(calc_t *calc);
void calculator_input_handler(calc_t *calc, float data);
void calculator_prompt(calc_t *calc);
void calculator_do(calc_t *calc);

#ifdef __cplusplus

    }

#endif

#endif // CALCULATOR_H