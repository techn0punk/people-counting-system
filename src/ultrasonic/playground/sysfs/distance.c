// this is a first test

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define INPUT "in"
#define OUTPUT "out"
#define LOW "0"
#define HIGH "1"

// HC-SR04 Pins
#define TRIGGER "23"    // output
#define ECHO "24"       // input

/**
 * @brief Sets Pin either to INPUT or OUTPUT
 * 
 * @param pin number as string, e.g. "23"
 * @param mode can be "in" or "out"
 */
void pinMode(char pin[], char mode[]) {
	FILE *sysfs_export;
	FILE *sysfs_direction;
	char path[40] = "";
	sysfs_export = fopen("/sys/class/gpio/export", "w");
	fwrite(pin, 1, sizeof(pin), sysfs_export);
	fclose(sysfs_export);
	
	strcpy(path, "/sys/class/gpio/gpio");
	strcat(path, pin);
	strcat(path, "/direction");

	sysfs_direction = fopen(path, "w");
	fwrite(mode, 1, sizeof(mode), sysfs_direction);
	fclose(sysfs_direction);
}

/**
 * @brief Sets given pin high (3.3V) or low (0V).
 * The pin must be set to OUTPUT with pinMode() beforehand.
 * 
 * @param pin number as string, e.g. "23"
 * @param value can be "0" for low and "1" for high
 */
void digitalWrite(char pin[], char value[]) {
	char path[40];
	FILE *sysfs_value;
	strcpy(path, "/sys/class/gpio/gpio");
	strcat(path, pin);
	strcat(path, "/value");

	sysfs_value = fopen(path, "w");
	fwrite(value, 1, sizeof(value), sysfs_value);
	fclose(sysfs_value);	
}

/**
 * @brief Returns the Voltage level of the given pin.
 * The pin must be set to INPUT with pinMode() beforehand.
 * 
 * @param pin number as string, e.g. "24"
 * @return char is '1' for high (3.3V) or '0' for low (0V).
 */
char digitalRead(char pin[]) {
    char path[40];
    FILE *sysfs_value;
	strcpy(path, "/sys/class/gpio/gpio");
	strcat(path, pin);
	strcat(path, "/value");

    char value;
    sysfs_value = fopen(path, "r");
    value = fgetc(sysfs_value);
    fclose(sysfs_value);

    return value;
}

/**
 * @brief Unexports the givien pin.
 * This will undo the effect of pinMode().
 * 
 * @param pin number as string, e.g. "24"
 */
void cleanUp(char pin[]) {
	FILE *sysfs_unexport;
	sysfs_unexport = fopen("/sys/class/gpio/unexport", "w");
	fwrite(pin, 1, sizeof(pin), sysfs_unexport);
	fclose(sysfs_unexport);
}

/**
 * @brief This measures the duration (in microseconds) 
 * of a high pulse on the given pin. This function is not very precise.
 * It can happen at any time that the scheduler suspends the execution
 * of the function and further corrupts the result.
 * The pin must be set to INPUT with pinMode() beforehand.
 * 
 * @param pin number as string, e.g. "24"
 * @return float microseconds
 */
float getPulseUs(char pin[]) {
    char baseLevel = digitalRead(pin);
    while (digitalRead(pin) == baseLevel);
    clock_t start = clock();
    while (digitalRead(pin) != baseLevel);
    clock_t end = clock();

    return (float)(end - start) /  (CLOCKS_PER_SEC / 1000000);
}

/**
 * @brief This puts a high pulse on the given pin for the given
 * amount of microseconds. This function is not very precise.
 * Depending on the clockspeed of the processor, the shortest
 * achievable pulse duration can be several hundred microseconds.
 * The pin must be set to OUTPUT with pinMode() beforehand.
 * 
 * @param pin number as string, e.g. "23"
 * @param us microseconds of pulse duration
 */
void putPulseUs(char pin[], int us) {
    const clock_t clocks_per_us = (clock_t) (CLOCKS_PER_SEC / 1000000);
    const clock_t cycles_to_wait = (clock_t) (us * clocks_per_us);
    digitalWrite(pin, HIGH);
    /* even without timing the pulse is at least 150us wide (on Raspberry Pi Zero) */
    clock_t start = clock();
    while (clock() < start + cycles_to_wait);
    digitalWrite(pin, LOW);

}

/* Most of the time the readings are somewhat accurate (+- 5mm).
 * But approx every 10th reading is off by ~10cm.
 * This is due to (expected) timing issues of unprivileged code.
 */
int main() {
    pinMode(TRIGGER, OUTPUT);
    pinMode(ECHO, INPUT);

    putPulseUs(TRIGGER, 10);
    printf("%.1f cm\n", getPulseUs(ECHO)/58);

    cleanUp(TRIGGER);
    cleanUp(ECHO);

    return 0;
}