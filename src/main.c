#include <stdio.h>
#include <unistd.h>
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

#define LIMIT 10

int main(void) {

    // printf("%.2f\n", getDistanceCM(TRIGGER1, ECHO1));
    lcdS1();

    if (calibrate(THRESHOLD) == -1)
    {
        printf("Error calibrating sensors!\n");
        lcdSE("Ultrasonic");
        return 1;
    }
    
    turnOnGreen();
    lcdS3(count, LIMIT);

    while(1) {


        if (updateCount() == -999)
        {
            printf("Error updating count!\n");
            //lcdSE("Ultrasonic");
            continue;
        }
        
        if (last_count != count)
        {
            lcdS3(count, LIMIT);
            if (count < LIMIT -1)
            {
                turnOffYellow();
                turnOffRed();
                turnOnGreen();
            }
            else if (count < LIMIT)
            {
                turnOffGreen();
                turnOffRed();
                turnOnYellow();
            }
            else if (count >= LIMIT)
            {
                turnOffGreen();
                turnOffYellow();
                turnOnRed();
            }
            
            
            
        }
        

        #ifndef DEBUG
        printf("CNT: %d\n", count);
        #endif
        
    }
    
    return 0;
}