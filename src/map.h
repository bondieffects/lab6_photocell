

    #include <avr/io.h>
    #include <util/delay.h>
    #include <stdlib.h>


    int32_t map_(int32_t x, int32_t x1, int32_t x2, int32_t y1, int32_t y2){
        // Using int64_t for intermediate calculation to prevent overflow
        int64_t scaled_value = (x - x1) * (y2 - y1);
    //(y2 - y1) total difference in height from starting point y1 to highest point y2
    //(x-x1) how far x has moved from the starting point
    //multiplying these two gets us the scaled value for dividing by (x2-x1)
        return (scaled_value / (x2 - x1) + y1);
    //divided by (x2-x1) in order to get a proportional change
    // then +y1 to get final position of 
    }
