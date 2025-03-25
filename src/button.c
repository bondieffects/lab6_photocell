#include "button.h"

void create_button(button_t *button) 
{
  button->debounced_state = 1;
  button->state = 0;
  button->fell = 0;
  button->rose = 1;
}