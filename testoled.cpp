#include "ArduiPi_OLED_lib.h"
#include "Adafruit_GFX.h"
#include "ArduiPi_OLED.h"
#include "bmp180.h"
#include "core_temp.h"
#include <getopt.h>


//Instatiate the display
ArduiPi_OLED display;


int main()
{
	
	unsigned int temperature, pressure, altitude;
	double coretemp;

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
	coretemp = get_core_temp();

	



//select oled screen  and display	

	display.clearDisplay();
	display.setCursor(0,0);

//	bcm2835_i2c_setSlaveAddress(0x3c);

        display.printf("Core temp:%.3f\n",coretemp);
	display.drawVerticalBargraph(110,0,5,(int16_t)display.height(),1,(int)(((coretemp-25)/20)*100));

	display.printf("Sensor Temp:%0.1f\xB1\n",((double)temperature)/10);
	display.drawVerticalBargraph(116,0,5,(int16_t)display.height(),1,(int)((((double)(temperature)/10-25)/20)*100));
	display.drawVerticalBargraph(104,0,5,(int16_t)display.height(),1,(int)altitude-100);
//	printf("T:%f\n",(double)(temperature)/10);
	display.printf("Pressure:%0.2f\n",((double)pressure/100));
	display.printf("Altitude %d\n",((int)altitude));
	display.display();
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
