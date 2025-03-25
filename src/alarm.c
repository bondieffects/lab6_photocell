#include "alarm.h"

void create_alarm(alarm_t *alarm)
{
  alarm->enabled = 0;
  alarm->volume = 2;
  alarm->frequency = 523.25;
  alarm->playing = 0;
}