#include "ArduiPi_OLED_lib.h"
#include "Adafruit_GFX.h"
#include "ArduiPi_OLED.h"
#include "bmp180.h"
#include "core_temp.h"
#include "dht.h"
#include <getopt.h>

#include <stdio.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>
//Instatiate the display
//
#define LOGO_HEIGHT 24 
#define LOGO_WIDTH 28
static unsigned char logobmp[] =
{
  0b00000000,0b00000111,0b10000000,0b00000000,
  0b00001100,0b00011111,0b11110000,0b00000000,
  0b00011100,0b00111111,0b11111000,0b00000000,
  0b00001110,0b00111111,0b11110000,0b00000000,
  0b00000110,0b00111111,0b11100000,0b00000000,
  0b00000011,0b01111111,0b11111100,0b00000000,
  0b00000001,0b11111111,0b11111111,0b10000000,
  0b00000000,0b11111111,0b11111111,0b11000000,
  0b00000000,0b01111111,0b11111111,0b11100000,
  0b11100111,0b11111111,0b11111111,0b11110000,
  0b01100010,0b11011111,0b11111111,0b11100000,
  0b01110010,0b11011111,0b11111111,0b11000000,
  0b01011010,0b11110111,0b11111111,0b10000000,
  0b01001110,0b11010011,0b11111100,0b00000000,
  0b01000110,0b11001001,0b11111111,0b00000000,
  0b11100111,0b11111000,0b11111111,0b10000000,
  0b00000000,0b00000000,0b01111111,0b10000000,
  0b00000001,0b11111011,0b11111111,0b11000000,
  0b00000000,0b11001101,0b10011111,0b11000000,
  0b00000000,0b11001101,0b10001111,0b11000000,
  0b00000000,0b11111000,0b11001111,0b11000000,
  0b00000000,0b11010000,0b11010011,0b11000000,
  0b00000000,0b11011100,0b11100001,0b10000000,
  0b0000001,0b11100111,0b00110000,0b010000000
};
//

ArduiPi_OLED display;

float tempA,preA,AltA;

void handler(int sig){
    FILE *filepointer;
    time_t t;
    filepointer=fopen("data.txt","a+");
    if(filepointer == NULL){
    printf("Could not open data.txt!\n");

    }
    fprintf(filepointer,"%.1f %.2f %.0f\n",tempA,preA,AltA);
    time(&t);
    fprintf(filepointer,"%s\n",ctime(&t));
    fclose(filepointer);
    alarm(1200);
    signal(SIGALRM,handler);
}


int main()
{
	
	unsigned int temperature, pressure, altitude;
    float t=0,h=0;
    signal(SIGALRM,handler);
    alarm(5);
	double coretemp;
//select oled screen  and display	

	display.clearDisplay();
	display.setCursor(0,0);

	display.init(OLED_I2C_RESET,6);
	display.begin();
	display.display();
	display.clearDisplay();
	display.setTextSize(1);
	display.setTextColor(WHITE);
	display.setCursor(0,0);



	
	while (1){

//calculate the temp&pressure	

	bmp085_Calibration();
    temperature = bmp085_GetTemperature(bmp085_ReadUT());
    pressure = bmp085_GetPressure(bmp085_ReadUP());
    altitude = bmp085_Altitude(pressure);
    tempA = (double)temperature/10;
    preA = (double)pressure/100;
    AltA = (double)altitude; 

    
    
//coretemp = get_core_temp();

//select oled screen  and display	

	display.clearDisplay();
	display.setCursor(0,0);

//	bcm2835_i2c_setSlaveAddress(0x3c);

// display.printf("Core temp:-\n");
	display.drawVerticalBargraph(112,0,5,(int16_t)display.height(),1,(int)(altitude-80));
	display.drawVerticalBargraph(118,0,5,(int16_t)display.height(),1,(int)((((double)(pressure)/100-980)/40)*100));

	display.drawVerticalBargraph(123,0,5,(int16_t)display.height(),1,(int)((((double)(temperature)/10-20)/20)*100));
//	printf("T:%f\n",(double)(temperature)/10);
	display.printf("SensorTemp:%0.1f%cC\n",((double)temperature)/10,247);
	display.printf("Pressure:%0.2f\n",((double)pressure/100));
	display.printf("Altitude %dm\n",((int)altitude));
    display.setCursor(40,24);
//    display.printf("DHT:T=%.1f\nH=%.1f\n",t,h);

    display.setCursor(66,56);
    display.printf("A%cP%cT",175,175);
    
    display.drawBitmap(0,32,logobmp,LOGO_WIDTH,LOGO_HEIGHT,WHITE);
	display.display();
//bcm2835_init();
 //   readDHT(22,4,&t,&h);

//	sleep(0.01);
}
//for(i=0;i<=100;i++)
//{
//	display.clearDisplay();
//	display.drawHorizontalBargraph(0,16,(int16_t)display.width(),3,1,i);
//	display.display();
//	sleep(1);
//}
}
