#ifndef ADC_H
#define ADC_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus

    extern "C" {

#endif

#define PHOTOCELL_MAX (890)
#define PHOTOCELL_MIN (449)

typedef struct {
    uint16_t value;      // Current ADC value
} adc_t;

typedef struct {
    uint16_t photocell_min;        // Minimum ADC value
    uint16_t photocell_max;        // Maximum ADC value
} photocell_t;

void adc_init(adc_t *adc);
void adc_start_conversion(void);

void photocell_init(photocell_t *photocell);
bool photocell_calibrate(photocell_t *photocell, adc_t *adc, bool input);

#ifdef __cplusplus

    }

#endif


#endif // ADC_H