#ifndef BITWISE_H
#define BITWISE_H

#define bitSet(reg, n) (reg |= 1 << n)
#define bitRead(reg, n) (reg >> n & 1)
#define bitClear(reg, n) (reg &= ~(1 << n))
#define bitInverse(reg, n) (reg ^= (1 << n))
#define bitCheck(reg, n) (reg >> n & 1)

#endif