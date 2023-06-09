#include "rpi.h"
#include "button.h"

clock_t last_UP_time = 0;
int last_UP_value = 0;

clock_t last_OK_time = 0;
int last_OK_value = 0;

const int debounce_MS = 200;
const clock_t clocks_per_ms = (clock_t) (CLOCKS_PER_SEC / 1000);
const clock_t cycles_to_wait = (clock_t) (debounce_MS * clocks_per_ms);

int buttonUP(void) {

    int button = digitalRead(27);
	if ((button != last_UP_value) && (clock() > last_UP_time + cycles_to_wait))
	{
		last_UP_time = clock();
		last_UP_value = button;
		return button;
	}
	else 
	{
		return -1;
	}
}

int buttonOK(void) {

	int button = digitalRead(17);
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