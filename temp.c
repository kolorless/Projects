// CSE 1106
// Lab Exercise using gdb
//
// Normal compile with assert enabled
//       gcc temp.c -Wall -O0 -g -o temp
//  Without assert
//       gcc temp.c -Wall -DNDEBUG -g -o temp

// This code requires an Rpi

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main (int argc, char* argv[])
{
   int n;               // number of samples
   int i;               // loop control

   // basic statistics on values
   double min = 9999;
   double max =-9999;
   double sum = 0.0;

   // store temp in different units
   double degs_c = 0.0;
   double degs_f = 0.0;

   // file descriptor
   int fd = 0;
   
   // open device
   fd = open ("/sys/class/thermal/thermal_zone0/temp",0);
   assert(fd);  // if the device opened, fd will be positive
  
   // read the temp 10 times
   i = 10;
   while (i)
   {
      // zero the read buffer
      // and read the value
      char b[16] = {0};
      lseek (fd,0,SEEK_SET);
      read (fd,&b,sizeof (b));

      // increment number of samples
      n++;

      // convert it into a double, and then into degrees F
      degs_c = strtod (b,NULL)/1000.0;
      degs_f = degs_c * (9.0/5.0) + 32.0;
      assert (degs_f > 0.0 && degs_f < 300.0);

      // calculate statistics
      sum = sum + degs_f;
      if (degs_f<min)
        min = degs_f;
      if (degs_f>max)
	     max = degs_f;

      // wait a second
      sleep(1);

      // next loop counter
      i--;
   }

   // display results
   printf ("Read %d values\n",n);
   printf ("Values in degrees F\n");
   assert ( n );
   assert ( min<=max );
   printf ("\tMin %f Max %f Avg %f\n",min,max,sum/n);
   return 0;
}
