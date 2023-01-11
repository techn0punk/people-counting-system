#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define OUTPUT "out"
#define LOW "0"
#define HIGH "1"

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

void cleanUp(char pin[]) {
	FILE *sysfs_unexport;
	sysfs_unexport = fopen("/sys/class/gpio/unexport", "w");
	fwrite(pin, 1, sizeof(pin), sysfs_unexport);
	fclose(sysfs_unexport);
}

int main() {

	pinMode("26", OUTPUT);
	pinMode("6",OUTPUT);
	pinMode("5",OUTPUT);

	for (size_t i = 0; i < 5; i++)
	{
		
		digitalWrite("26", HIGH);
		printf("GPIO26 on\n");
		sleep(1);
		digitalWrite("26", LOW);
		printf("GPIO26 off\n");
		sleep(1);
		digitalWrite("6", HIGH);
		printf("GPIO6 on\n");
		sleep(1);
		digitalWrite("6", LOW);
		printf("GPIO6 off\n");
		sleep(1);
		digitalWrite("5", HIGH);
		printf("GPIO5 on\n");
		sleep(1);
		digitalWrite("5", LOW);
		printf("GPIO5 off\n");
		sleep(1);
	}

	cleanUp("26");
	cleanUp("6");
	cleanUp("5");
	return 0;
}
