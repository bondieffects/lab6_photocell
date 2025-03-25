#ifndef ADC_H
#define ADC_H

#ifdef __cplusplus

    extern "C" {

#endif

#define PHOTOCELL_MAX (519)
#define PHOTOCELL_MIN (287)

typedef struct {

} adc_t;

void adc_init(void);
void adc_start_conversion(void);


#ifdef __cplusplus

    }

#endif


#endif // ADC_H