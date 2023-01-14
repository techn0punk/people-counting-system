#include "rpi.h"

int turnOnGreen(void) {
if (!digitalWrite(26,1)){return -1;}
else {
    digitalWrite(26, 1);
    return 0;
     }
}

int turnOffGreen(void) {
if (!digitalWrite(26,1)){return -1;}
else {
    digitalWrite(26, 0);
    return 0;
     }
}
int turnOnYellow(void) {
if (!digitalWrite(26,1)){return -1;}
else {
    digitalWrite(6, 1);
    return 0;
     }
}

int turnOffYellow(void) {
 if (!digitalWrite(26,1)){return -1;}
else {
    digitalWrite(6, 0);
    return 0;
     }
}

int turnOnRed(void) {
if (!digitalWrite(26,1)){return -1;}
else {   
    digitalWrite(5, 1);
    return 0;
     }
}
int turnOffRed(void) {
if (!digitalWrite(26,1)){return -1;}
else {    
    digitalWrite(5, 0);
    return 0;
     }
}
