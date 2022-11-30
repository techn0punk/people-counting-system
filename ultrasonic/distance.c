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
#define TRIGGER "16"    // output
#define ECHO "12"       // input

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

/*
 * Until now, this code only measures the width
 * of the Puls in Microsecends of ECHO Pin
 * 
 * TODO: give 10us pulse on TRIGGER Pin
 * TODO: convert time to distance
 */
int main() {
    pinMode(ECHO, INPUT);
    printf("%i us\n", (int) getPulseUs(ECHO));

    cleanUp(ECHO);

    return 0;
}