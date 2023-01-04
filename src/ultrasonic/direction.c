#include <stdio.h>
#include "distance.h"

#define TRIGGER1 20
#define ECHO1 21
#define TRIGGER2 23
#define ECHO2 24
#define TRESHOLD 0.7f

int main(void) {
    printf("Calibrating sensors.\n");

    float d1_base_level = 0.0;
    float d2_base_level = 0.0;

    for (size_t i = 0; i < 10; i++)
    {
        d1_base_level += getDistanceCM(TRIGGER1, ECHO1);
        d2_base_level += getDistanceCM(TRIGGER2, ECHO2);
    }

    d1_base_level = d1_base_level / 10.0;
    d2_base_level = d2_base_level / 10.0;

    float d1_threshold = d1_base_level * TRESHOLD;
    float d2_threshold = d2_base_level * TRESHOLD;

    printf("D1: %.2f [%.2f]  D2: %.2f [%.2f]\n", d1_base_level, d1_threshold, d2_base_level, d2_threshold);
    printf("Calibration done\n");

    float d1, d2;

    while (1)
    {
        d1 = getDistanceCM(TRIGGER1, ECHO1);
        d2 = getDistanceCM(TRIGGER2, ECHO2);
        printf("D1: %.2f [%.2f]  D2: %.2f [%.2f]\n", d1, d1_threshold, d2, d2_threshold);

        if (d1 < d1_threshold)
        {
            printf("D1 sensed. Waiting for D2.\n");
            while (1)
            {
                d2 = getDistanceCM(TRIGGER2, ECHO2);
                printf("D2: %.2f [%.2f]\n", d2, d2_threshold);
                if (d2 < d2_threshold)
                {
                    printf("--- ltr -->\n");
                    delayMS(2000);
                    break;
                }
                delayMS(200);
                
            }
        }
        else if (d2 < d2_threshold)
        {
            printf("D2 sensed. Waiting for D1.\n");
            while (1)
            {
                d1 = getDistanceCM(TRIGGER1, ECHO1);
                printf("D1: %.2f [%.2f]\n", d1, d1_threshold);
                if (d1 < d1_threshold)
                {
                    printf("<-- rtl ---\n");
                    delayMS(2000);
                    break;
                }
                delayMS(200);
                
            }
            
        }
        
        delayMS(200);
        
    }
    
    

    return 0;
}
