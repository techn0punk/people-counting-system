// this is a first test with interrupts and wiringPi

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <wiringPi.h>

// HC-SR04 Pins (WiringPi)
#define TRIGGER 4     // output GPIO 23
#define ECHOA 5       // input GPIO 24 (connected to ECHOB)
#define ECHOB 1       // input GPIO 18 (connected to ECHOA)
#define TIMEOUT 1000000 // 1 sec.

unsigned int start = 0; 
unsigned int end = 0;

void handle_rising(void) {
    start = micros();
}

void handle_falling(void) {
    end = micros();
}


int main(void) {
    wiringPiSetup();
    int prio = piHiPri(30);
    
    pinMode(TRIGGER, OUTPUT);

    /* For some reason it is not possible to register to interrupt handlers on 1 pin.
     * Setting the trigger to INT_EDGE_BOTH and differentiating int the handler 
     * doesn't work either. So the solution is to connect the echo pin to 2 BCM pins
     * and register seperate triggers on these pins */
    wiringPiISR(ECHOA, INT_EDGE_RISING, &handle_rising);
    wiringPiISR(ECHOB, INT_EDGE_FALLING, &handle_falling);

    /* Set the trigger pin high for 10us. The timing here isn't very accurate,
     * but the HC-SR04 module doesn't care. */
    digitalWrite(TRIGGER, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGGER, LOW);

    /* This loop does nothing. It ends if the handle_falling() ISR ran, or
     * the ellapsed time is over the TIMEOUT */
    while (end == 0 && micros() < TIMEOUT)
    {
        /* wait for falling edge */
    }

    /* If the programm times out, print it to STDOUT and return with error. */
    if (micros() >= TIMEOUT)
    {
        printf("TIMEOUT\n");
        return 1;
    }

    unsigned int pulse = end - start;
    float distance = (float) pulse / 58;
    // printf("Start: %d us\n", start);
    // printf("End: %d us\n", end);
    // printf("Pulse: %d us\n", pulse);
    printf("%.1f cm\n", distance);
    

    return 0;
}