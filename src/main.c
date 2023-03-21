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

int limit = 0;

typedef enum {
    STATE_CALIBRATION,
    STATE_SET_LIMIT,
    STATE_COUNTING,
    STATE_RESET,
    STATE_ERROR
} state_t;

state_t stateMachine(state_t currentState, int buttonOKpressed, int buttonUPpressed);
void simpleCounting(void);

int main(void) {
    turnOnGreen();
    state_t currentState = STATE_CALIBRATION;

    while(1) {
        int buttonOKpressed = buttonOK();
        int buttonUPpressed = buttonUP();
        printf("Current state: %d\n", currentState);

        // Transition to next state
        currentState = stateMachine(currentState, buttonOKpressed, buttonUPpressed);
    }
    return 0;
}

state_t stateMachine(state_t currentState, int buttonOKpressed, int buttonUPpressed) {
    switch(currentState) {
        case STATE_CALIBRATION:
            lcdS1();
            if (calibrate(THRESHOLD) == 0) {
                return STATE_SET_LIMIT;
            }
            else {
                printf("Error calibrating sensors!\n");
                lcdSE("Ultrasonic");
                return STATE_ERROR;
            }
            break;
        case STATE_SET_LIMIT:
            lcdS2(0, limit);
            if (buttonUPpressed == 1) {
                limit++;
                return STATE_SET_LIMIT;
            }
            else if (buttonOKpressed == 1) {
                lcdS3(count, limit);
                return STATE_COUNTING;
            }
            else {
                printf("Error setting limit!\n");
                lcdSE("setting limit");
                return STATE_ERROR;
            }
            break;
        case STATE_COUNTING:
            if (last_count != count) {
                lcdS3(count, LIMIT);
                if (count < LIMIT -1) {
                    turnOffYellow();
                    turnOffRed();
                    turnOnGreen();
                }
                else if (count < LIMIT) {
                    turnOffGreen();
                    turnOffRed();
                    turnOnYellow();
                }
                else if (count >= LIMIT) {
                    turnOffGreen();
                    turnOffYellow();
                    turnOnRed();
                }
            }
            int newCount = updateCount();
            if (buttonOKpressed == 1 || buttonUPpressed == 1) {
                return STATE_RESET;
            }
            else if (newCount == -999){
                printf("Error updating count!\n");
                lcdSE("Counting");
                return STATE_ERROR;
            }
            else {
                count = newCount;
                return STATE_COUNTING;
            }
            break; // WIP
        case STATE_RESET:
            // Perform actions for STATE_RESET
            return STATE_CALIBRATION;
            break;
        case STATE_ERROR:
            // Perform actions for STATE_ERROR
            return STATE_ERROR;
            break;
        default:
            return STATE_ERROR;
            break;
    }
}

void simpleCounting(void) {

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
        
    }
}