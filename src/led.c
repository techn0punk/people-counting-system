#include "rpi.h"
#include "led.h"

int turnOnGreen(void) {

    return digitalWrite(GREEN, 1);
}

int turnOffGreen(void) {

    return digitalWrite(GREEN, 0);
}

int turnOnYellow(void) {

    return digitalWrite(YELLOW, 1);
}

int turnOffYellow(void) {

    return digitalWrite(YELLOW, 0);
}

int turnOnRed(void) {

    return digitalWrite(RED, 1);
}

int turnOffRed(void) {

    return digitalWrite(RED, 0);
}