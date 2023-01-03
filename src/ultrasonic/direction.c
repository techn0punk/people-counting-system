#include <stdio.h>
#include "distance.h"

#define TRIGGER1 20
#define ECHO1 21
#define TRIGGER2 23
#define ECHO2 24

int main(void) {
    float d1;
    float d2;

    for (size_t i = 0; i < 10; i++)
    {
        d1 = getDistanceCM(TRIGGER1, ECHO1);
        d2 = getDistanceCM(TRIGGER2, ECHO2);
        printf("Dist1: %.2f cm \tDist2: %.2f cm\n", d1, d2);
    }
    

    return 0;
}