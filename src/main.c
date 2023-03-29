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
int threshold_yellow;

typedef enum {
    STATE_CALIBRATION,
    STATE_SET_LIMIT,
    STATE_SET_LIMIT_10,
    STATE_COUNTING,
    STATE_RESET,
    STATE_ERROR
} state_t;

state_t stateMachine(state_t currentState, int buttonOKpressed, int buttonUPpressed);

int main(void) {
    state_t currentState = STATE_CALIBRATION;

    while(1) {
        if (count < 0) count = 0;
        int buttonOKpressed = buttonOK();
        int buttonUPpressed = buttonUP();

        #ifdef DEBUG
        if (buttonOKpressed == 1) printf("Button OK pressed [%ld]\n", clock());
        if (buttonUPpressed == 1) printf("Button UP pressed [%ld]\n", clock());
        #endif

        // Transition to next state
        currentState = stateMachine(currentState, buttonOKpressed, buttonUPpressed);
    }
    return 0;
}

state_t stateMachine(state_t currentState, int buttonOKpressed, int buttonUPpressed) {
    switch(currentState) {
        case STATE_CALIBRATION:
            lcdS1();
            delayMS(2000);
            turnOnGreen();
            turnOffYellow();
            turnOffRed();
            if (calibrate(THRESHOLD) == 0) {
                lcdS2(0, limit);
                return STATE_SET_LIMIT;
            }
            else {
                printf("Error calibrating sensors!\n");
                lcdSE("Ultrasonic");
                return STATE_ERROR;
            }
            break;
        case STATE_SET_LIMIT:
            if (buttonUPpressed == 1) {
                limit++;
                lcdS2(0, limit);
                return STATE_SET_LIMIT;
            }
            else if (buttonOKpressed == 1) {
                lcdS2(1, limit);
                return STATE_SET_LIMIT_10;
            }
            else {
                return STATE_SET_LIMIT;
            }
            break;
        case STATE_SET_LIMIT_10:
            if (buttonUPpressed == 1) {
                limit += 10;
                lcdS2(1, limit);
                return STATE_SET_LIMIT_10;
            }
            else if (buttonOKpressed == 1) {
                threshold_yellow = (int)(limit * 0.1 + 0.5); // +0.5 for rounding to next larger integer
                lcdS3(count, limit);
                return STATE_COUNTING;
            }
            else {
                return STATE_SET_LIMIT_10;
            }
            break;
        case STATE_COUNTING:
            if (last_count != count) {
                lcdS3(count, limit);
                if (count < limit - threshold_yellow) {
                    turnOffYellow();
                    turnOffRed();
                    turnOnGreen();
                }
                else if (count < limit) {
                    turnOffGreen();
                    turnOffRed();
                    turnOnYellow();
                }
                else if (count >= limit) {
                    turnOffGreen();
                    turnOffYellow();
                    turnOnRed();
                }
            }
            int newCount = updateCount();
            if (buttonOKpressed == 1 || buttonUPpressed == 1) {
                lcdS4();
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
            break;
        case STATE_RESET:
            if (buttonUPpressed == 1) {
                lcdS3(count, limit);
                return STATE_COUNTING;
            }
            else if (buttonOKpressed == 1) {
                count = 0;
                limit = 0;
                return STATE_CALIBRATION;
            }
            else {
                return STATE_RESET;
            }
            break;
        case STATE_ERROR:
            if (buttonOKpressed == 1 || buttonUPpressed == 1) {
                return STATE_RESET;
            }
            else {
                return STATE_ERROR;
            }
            break;
        default:
            return STATE_ERROR;
            break;
    }
}