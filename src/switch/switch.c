#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#define HIGH 1
#define LOW 0
#define INPUT 1
#define OUTPUT 0

int inputPin = 26;
int outputPin = 6;

bool digitalPinMode(int pin, int mode){
  	FILE * fd;
  	char path [128];
  	if(( fd = fopen("/sys/class/gpio/export", "w")) == NULL) {
    	printf("Error: unable to export pin\n");
    	return false;
  	}
  	fprintf(fd, "%d\n", pin);
  	fclose(fd);

 	sprintf(path, "/sys/class/gpio/gpio%d/direction", pin);

  	if((fd = fopen(path, "w")) == NULL) {
    	printf("Error: can't open pin direction\n");
    	return false;
  	}

	if(mode == OUTPUT) {
    	fprintf(fd, "out\n");
  	}
	else {
   	 fprintf(fd, "in\n");
  	}
 	fclose(fd);
  	return true;
}

bool digitalWrite(int pin, int value) {

  	FILE * fd;
  	char path[128];
  	sprintf(path, "/sys/class/gpio/gpio%d/value", pin);
  	if((fd = fopen(path, "w")) == NULL) {
    	printf("Error: can't open pin value\n");
    	return false;
  	}
  	if(value == HIGH) {
    	fprintf(fd, "1\n");
  	}
	else {
    	fprintf(fd, "0\n");
  	}
  	fclose(fd);
  	return true;
}


int digitalRead(int pin) {
	FILE * fd;
 	char path[128];
 	char value[2];
 	sprintf(path, "/sys/class/gpio/gpio%d/value", pin);
	if((fd = fopen(path, "r")) == NULL) {
	printf("Error: can't open pin value\n");
   	return false;
 	 }
  	fgets(value, 2, fd);
  	fclose(fd);
  	return atoi(value);
}

int cleanUp(int pin) {
	FILE *fd;
        char path[128];
        sprintf(path, "/sys/class/gpio/gpio%d/unexport", pin);
        fprintf(fd, "%d\n", pin);
        fd = fopen(path, "w");
        fclose(fd);
}



int main(void) {

  while(1) {
    int tasterVal;
    tasterVal = digitalRead(inputPin);
    printf("tasterVal is %d\n", tasterVal);
    if(tasterVal==HIGH){
    digitalWrite(outputPin, HIGH);
    printf("LED on \n");
//    sleep(1);
    }
    else{
    digitalWrite(outputPin, LOW);
    printf("LED off \n");
  //  sleep(1);
    }
  }
  return 0;
}
