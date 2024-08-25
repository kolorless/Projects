#include <stdio.h>
#include <math.h>
// gcc -o trig trig.c -lm -O0 -Wall -g 
int main ( int argc, char* argv[] )
{
   double fortyFiveDegreesInRadians = M_PI / 4.0;
   printf(" %f %f\n",
          sin(fortyFiveDegreesInRadians),
          cos(fortyFiveDegreesInRadians));
   return 0;
}

// October Stringify