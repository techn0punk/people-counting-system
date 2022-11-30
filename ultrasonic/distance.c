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

void cleanUp(char pin[]) {
	FILE *sysfs_unexport;
	sysfs_unexport = fopen("/sys/class/gpio/unexport", "w");
	fwrite(pin, 1, sizeof(pin), sysfs_unexport);
	fclose(sysfs_unexport);
}

float getPulseUs(char pin[]) {
    char baseLevel = digitalRead(pin);
    while (digitalRead(pin) == baseLevel);
    clock_t start = clock();
    while (digitalRead(pin) != baseLevel);
    clock_t end = clock();

    return (float)(end - start) /  (CLOCKS_PER_SEC / 1000000);
}

void putPulseUs(char pin[], int us) {
    const clock_t clocks_per_us = (clock_t) (CLOCKS_PER_SEC / 1000000);
    const clock_t cycles_to_wait = (clock_t) (us * clocks_per_us);
    digitalWrite(pin, HIGH);
    /* even without timing the pulse we can get is at least 150us wide */
    //clock_t start = clock();
    //while (clock() < start + cycles_to_wait);
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