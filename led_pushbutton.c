#include <pigpio.h>
#include <stdio.h>
#define PIN 4
#define SWITCH 14
int main(void){
	gpioInitialise();
	gpioSetMode(PIN, PI_OUTPUT);
	gpioSetMode(SWITCH, PI_INPUT);
	gpioSetPullUpDown(SWITCH, PI_PUD_UP);
	
	gpioWrite(PIN,1);
	while(gpioRead(SWITCH));
	gpioWrite(PIN, 0);
	
	gpioTerminate();
	return 0;
}
