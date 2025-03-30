#include "utility.h"

/*! @brief Arduino map function */
long map(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

/*! @brief Linear map as taught in Introductory Embedded Systems.
    Works by:
    1. Calculate the slope [k] using (y2-y1)/(x2-x1)
    2. Applying the formula y = y1 + k*(x-x1)

    @param x The input value to be mapped.
    @param in_min The minimum value of the input range. [x1]
    @param in_max The maximum value of the input range. [x2]
    @param out_min The minimum value of the output range. [y1]
    @param out_max The maximum value of the output range. [y2]
    @return The mapped output value. [y]
*/
float linear_map(float x, float in_min, float in_max, float out_min, float out_max)
{
    // Check for divide by 0
    if (in_max == in_min) return out_min;

    // Calculate slope
    float k = (out_max - out_min) / (in_max - in_min);

    // Scale y = y1 + k*(x-x1)
    float y = out_min + (k * (x - in_min));

    // Clamp to output range
    if (y > out_max) y = out_max;
    if (y < out_min) y = out_min;

    return y;
}