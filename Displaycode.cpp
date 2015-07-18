#include "ArduiPi_OLED_lib.h"
#include "Adafruit_GFX.h"
#include "ArduiPi_OLED.h"
#include <stdio.h>

//Instatiate the display
ArduiPi_OLED display;


int main()
{
	
	display.init(OLED_I2C_RESET,6);
	display.begin();
	display.display();
	display.clearDisplay();
	display.setTextSize(1);
	display.setTextColor(WHITE);
	display.setCursor(0,0);

	int w=0xE0;
	int i=0;
	for(i=0;i<100;i++){
        display.printf("%c%d",w+i,w+i);
	printf("%c",w+i);
	display.display();
	}
}
