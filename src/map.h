

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>


int32_t map_increase(float x, float x1, float x2, float y1, float y2){
    float k = (y2-y1)/(x2-x1); //since y2>y1 therefore increasing
    // since y increases with x we use the formula below
    return y1+k*(x-x1);
    // maps the x value to the corresponding y value
    //(x-x1) gives the distance from value from starting point (x1)
    // slope (k) then used to scale the distance between x and x1
    // y1+k as it shifts the linear mapping to start at the correct pt due to previous (y2-y1) which gives the total height 
    // increased from y1 therefore y1+k
}

int32_t map_decrease(float x, float x1, float x2, float y1, float y2){
    float k = (y1-y2)/(x2-x1);//since y1>y2 therefore decreasing
    // since y decreases with x we use the formula below
    return y1-k*(x-x1);
    // maps the x value to the corresponding y value
    //(x-x1) gives the distance from value from starting point (x1)
    // slope (k) then used to scale the distance between x and x1 
    // y1-k as it shifts the linear mapping to start at the correct pt due to previous (y1-y2) which gives the total height
    // started at y1 and decreased therefore y1-k
} 
