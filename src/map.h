
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>


int32_t map_int(int32_t x, int32_t x1, int32_t x2, int32_t y1, int32_t y2) {
    // Handle the case where x1 equals x2 to avoid division by zero
    if (x1 == x2) {
        return y1;
    }

    // Perform the mapping with proper scaling to maintain precision
    // Using int64_t for intermediate calculation to prevent overflow
    int64_t scaled_value = (int64_t)(x - x1) * (y2 - y1);
    return (int32_t)(scaled_value / (x2 - x1) + y1);
}
