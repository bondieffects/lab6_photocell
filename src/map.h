

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>


int32_t map_int(int32_t x, int32_t x1, int32_t x2, int32_t y1, int32_t y2) {
    // Using int64_t for intermediate calculation to prevent overflow
    int64_t scaled_value = (x - x1) * (y2 - y1);
//(y2 - y1) height difference between 2 points 
//(x-x1) how far x has moved from the starting point
//multiplying these two 
    return (scaled_value / (x2 - x1) + y1);
//
    
}
