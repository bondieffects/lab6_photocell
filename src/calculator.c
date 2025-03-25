#include "calculator.h"
#include <math.h>

void calculator_init(calc_t *calc)
{
    calc->state = STATE_MENU;
    calc->operation = OP_ADD;
    calc->first_num = 0.0f;
    calc->second_num = 0.0f;
    calc->result = 0.0f;

    calculator_prompt(calc);
}


void calculator_input_handler(calc_t *calc, float cmd)
{
    // Process the input based on current state
    switch (calc->state) {
        case STATE_MENU:
            if (cmd >= 1 && cmd <= 9) {
                calc->operation = (calc_op_t)cmd;
                calc->state = STATE_FIRST_NUM;
                calculator_prompt(calc);
            } else {
                usart_send_string("Invalid operation! Please select 1-9.\r\n");
                calculator_prompt(calc);
            }
            break;

        case STATE_FIRST_NUM:
            calc->first_num = cmd;

            // For log, sin and cos, we only need one parameter
            if (calc->operation > OP_POW) {
                calc->state = STATE_RESULT;
                calculator_do(calc);
            } else {
                calc->state = STATE_SECOND_NUM;
            }
            calculator_prompt(calc);
            break;

        case STATE_SECOND_NUM:
            calc->second_num = cmd;
            calc->state = STATE_RESULT;
            calculator_do(calc);
            calculator_prompt(calc);
            calc->state = STATE_MENU;
            calculator_prompt(calc);
            break;

        default:
            calculator_prompt(calc);
            break;
    }
}

/*! Displays the calculator prompts */
void calculator_prompt(calc_t *calc) 
{
    switch (calc->state) {
        case STATE_MENU:
            usart_send_string("\r\nCalculator Options:\r\n");
            usart_send_string("1. Addition\r\n");
            usart_send_string("2. Subtraction\r\n");
            usart_send_string("3. Multiplication\r\n");
            usart_send_string("4. Division\r\n");
            usart_send_string("5. Remainder\r\n");
            usart_send_string("6. Power\r\n");
            usart_send_string("7. Log\r\n");
            usart_send_string("8. Sin\r\n");
            usart_send_string("9. Cos\r\n");
            usart_send_string("Select an operation (1-9):\n");
            break;

        case STATE_FIRST_NUM:
            usart_send_string("Enter first number: ");
            break;

        case STATE_SECOND_NUM:
            usart_send_string("Enter second number: ");
            break;

        case STATE_RESULT:
            usart_send_string("Result: ");
            usart_send_num(calc->result, 3, 3);
            usart_send_string("\r\n");
            break;
        default:
            usart_send_string("Invalid state!\r\n");
            break;
    }
}

void calculator_do(calc_t *calc)
{
    switch (calc->operation) {
        case OP_ADD:
            calc->result = calc->first_num + calc->second_num;
            break;
        case OP_SUB:
            calc->result = calc->first_num - calc->second_num;
            break;
        case OP_MUL:
            calc->result = calc->first_num * calc->second_num;
            break;
        case OP_DIV:
            calc->result = calc->first_num / calc->second_num;
            break;
        case OP_REM:
            calc->result = (int)calc->first_num % (int)calc->second_num;
            break;
        case OP_POW:
            calc->result = pow(calc->first_num, calc->second_num);
            break;
        case OP_LOG:
            calc->result = log(calc->first_num);
            break;
        case OP_SIN:
            calc->result = sin((int)calc->first_num);
            break;
        case OP_COS:
            calc->result = cos(calc->first_num);
            break;
        default:
            usart_send_string("Invalid operation!\r\n");
            break;
    }
}