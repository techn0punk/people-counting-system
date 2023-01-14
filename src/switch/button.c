#include <time.h>
#include "rpi.h"
#include <stdio.h>

clock_t last_UP;
clock_t last_OK;
int debounce_MS;

int buttonUP(void) {

	struct timespec startTime, endTime;

	int buttonup;
	int buttoncount = 0;

	buttonup = digitalRead(17);	
	if(buttonup == 1){
	buttoncount++;
/*	clock_gettime(CLOCK_MONOTONIC, &startTime);
	}
	if(buttonup == 0){
	clock_gettime(CLOCK_MONOTONIC, &endTime);
	double pressTime = (endTime.tv_sec - startTime.tv_sec)+
	(endTime.tv_nsec -startTime.tv_nsec) / 1e9;
*/
	printf("button pressed %d times\n", buttoncount);
}

    return 0;
}


int buttonOK(void) {

	int tasterok;
	tasterok = digitalRead(27);
	if(tasterok == 1){
	printf("OK button pressed \n");
	}
	else{
	printf("button is not pressed \n");
	}
    return 0;
}

