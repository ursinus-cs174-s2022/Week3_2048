/**
 * @file randutils.cpp
 * @author Chris Tralie (chris.tralie@gmail.com)
 * 
 * @copyright Copyright (c) 2022
 * 
 * Purpose: To create a random number generator seeded by
 * the system clock
 * 
 */

#include <sys/time.h>
#include <stdio.h>
#include "randutils.h"

/**
 * Return the number of microseconds currently on
 * the system clock
 */
int getMicroseconds() {
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return (int)tv.tv_usec;
}


float RAND_A = 49;
float RAND_C = 17;
float RAND_M = 97;

float x = ((float)(getMicroseconds()%1000))/1000;

/**
 * @brief Return a random number between 0 and 1
 * 
 * @return float 
 */
float randfloat() {
    float ret = RAND_A*x + RAND_C;
    float fac = (float)((int)(ret/RAND_M));
    x = ret - fac*RAND_M;
    return x/100;
}
