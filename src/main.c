#include <stdio.h>
#include "display.h"
#include "ultrasonic.h"
#include "button.h"
#include "led.h"
#include "rpi.h"

#define TRIGGER1 23
#define ECHO1 24
#define TRIGGER2 25
#define ECHO2 16
#define THRESHOLD 0.7f



int main(void) {

    if (calibrate(THRESHOLD) == -1)
    {
        printf("Error calibrating sensors!\n");
        return 1;
    }
    
    while(1) {

        if (updateCount() == -999)
        {
            printf("Error updating count!\n");
            return 1;
        }

        #ifndef DEBUG
        printf("CNT: %d\n", count);
        #endif
        
    }
    
    return 0;
}