#include "lcd_b"

int main(){
    exportPin_UP(17);
    setPinDirection_UP(17,"in");
exportPin_OK(27);
    setPinDirection_OK(27,"in");


	 if ((fd = open("/dev/i2c-1", O_RDWR)) < 0) return -1 ; // Check interface for device
  if (ioctl(fd, I2C_SLAVE, I2C_ADDR) < 0) return -1 ;

	lcd_init();  
	
    while(1) {
//        if(readPinValue_UP(17) && readPinValue_OK(27)){
  //          printf("1\n");
	//	int lcdS1();
		int result = lcdS4();
		sleep(2);
		ClrLcd();
		sleep(1);
        if (result == -1) {
         	printf("Fehler\n");   // Fehlerbehandlung, z.B. Ausgabe einer Fehlermeldung
        }  
//     lcdLoc(Line0); typeln("1");	
  //      }
    //    else{
//	lcdLoc(Line0); typeln("0");            
//printf("0\n");
      //  }
    } 
    return 0;
}
