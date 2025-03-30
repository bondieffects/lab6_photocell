#ifndef UTILITY_H
#define UTILITY_H

/*! @brief Arduino map function, works by 

*/
long map(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

#endif // UTILITY_H