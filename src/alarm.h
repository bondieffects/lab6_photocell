#ifndef ALARM_H
#define ALARM_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus

    extern "C" {

#endif

typedef struct alarm_type {
    bool enabled;
    uint8_t volume;
    float frequency;
    bool playing;
  } alarm_t;

void create_alarm(alarm_t *alarm);

#ifdef __cplusplus

    }

#endif


#endif // ALARM_H