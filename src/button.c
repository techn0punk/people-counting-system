#include <time.h>
#include "rpi.h"

clock_t last_UP_time = 0;
int last_UP_value = 0;

clock_t last_OK_time = 0;
int last_OK_value = 0;

const int debounce_MS = 500;
const clock_t clocks_per_ms = (clock_t) (CLOCKS_PER_SEC / 1000);
const clock_t cycles_to_wait = (clock_t) (debounce_MS * clocks_per_ms);

int buttonUP(void) {
    
    return 0;
}

int buttonOK(void) {

	/**
	 * button = DR(27)
	 * if (button != last_OK_value) && (clock() > last_OK_time + cycles_to_wait):
	 * 		last_OK_time = clock();
	 * 		last_OK_value = button;
	 * 		return button;
	 * else:
	 * 		return !button
	 * 
	 */

	int button = digitalRead(27);
	if ((button != last_OK_value) && (clock() > last_OK_time + cycles_to_wait))
	{
		last_OK_time = clock();
		last_OK_value = button;
		return button;
	}
	else 
	{
		return -1;
	}
	
}