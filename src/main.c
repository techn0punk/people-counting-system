#include <stdio.h>
#include "display.h"
#include "ultrasonic.h"
#include "button.h"
#include "led.h"

#define TRIGGER1 23
#define ECHO1 24
#define TRIGGER2 25
#define ECHO2 16
#define TRESHOLD 0.7f

int main(void) {

    float d1 = getDistanceCM(TRIGGER1, ECHO1);
    float d2 = getDistanceCM(TRIGGER2, ECHO2);
    printf("D1: %.2f  D2: %.2f\n", d1, d2);
    
    return 0;
}