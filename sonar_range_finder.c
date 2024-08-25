#include <pigpio.h>
#include <stdio.h>
#include <unistd.h>

#define TRIGGER 17
#define ECHO 18
#define SPEED 34300

int main(void)
{
	gpioInitialise();
	gpioSetMode(TRIGGER, PI_OUTPUT);
	gpioSetMode(ECHO, PI_INPUT);
	gpioSetPullUpDown(ECHO, PI_PUD_UP);
	
	while(1)
	{
		gpioWrite(TRIGGER,1);
		sleep(1);
		gpioWrite(TRIGGER,0);
		int count = 0;
		
		while (gpioRead(ECHO) != 1){
			
		}
		
		uint32_t start_time = gpioTick();
		
		while (gpioRead(ECHO) != 0){
			count++;
		}
		uint32_t end_time = gpioTick();
		
		uint32_t elapsed_time = end_time - start_time;
		printf("Count: %d\n", count);
		printf("Elapsed Time: %u micro seconds\n", elapsed_time);
		
		float distance_cm = ((float)elapsed_time / 100000) * (SPEED / 2);
		float distance_inch = distance_cm / 2.54;
		
		printf("Distance: %.2f cm, %.2f inches\n", distance_cm, distance_inch);
		sleep(1);
	}
	
	gpioTerminate();
	return 0;
}

