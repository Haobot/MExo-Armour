/*
Board: Arduino Leonardo or mCookie Core USB
Micro Chip: ATmega32U4
I/O: 
Rotating Resistor => A0
Pin0 RX => Pin18 TX (Main board-Mega2560)
Pin1 TX => Pin19 RX (Main board-Mega2560)
*/

#include "U8glib.h"

// setup u8g object, please remove comment from one of the following constructor calls
// IMPORTANT NOTE: The complete list of supported devices is here: http://code.google.com/p/u8glib/wiki/device
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);	// HW SPI Com: CS = 10, A0 = 9 (Hardware Pins are  SCK = 13 and MOSI = 11)

uint8_t offset = 0;

int num = 0;  
int showAngle = 0;
char string[25];  

const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to

int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)

void draw(void) {
  // graphic commands to redraw the complete screen should be placed here  
  u8g.setFont(u8g_font_unifont);
  u8g.setRot90();
  u8g.drawStr( 0+15, 20+0, "Arm");
  u8g.drawStr( 0+15, 20+16, "Angle:");
  
  itoa(showAngle, string, 10); 
  u8g.setFont(u8g_font_osb21);
  u8g.drawStr( 0+15, 20+52, string);

}

void setup(void) {
    Serial.begin(115200);
    Serial1.begin(115200);
    
}


void loop(void) {

  // read the analog in value:
  sensorValue = analogRead(analogInPin);
  // map it to the range of the analog out:
  outputValue = map(sensorValue, 0, 1023, 0, 255);

 
  
// For Left Arm
// showAngle = 255-outputValue;
//Serial.print('$');
//Serial.print(showAngle);
//Serial.print(' ');
//Serial.print(num);
//Serial.print('\n');
//
//
//Serial1.print('$');
//Serial1.print(showAngle);
//Serial1.print(' ');
//Serial1.print(num);
//Serial1.print('\n');


// For Right Arm
showAngle = outputValue;
Serial.print('$');
Serial.print(num);
Serial.print(' ');
Serial.print(showAngle);
Serial.print('\n');


Serial1.print('$');
Serial1.print(num);
Serial1.print(' ');
Serial1.print(showAngle);
Serial1.print('\n');
  
  // picture loop
  u8g.firstPage();  
  do {
    draw();
  } while( u8g.nextPage() );
  
  // rebuild the picture after some delay
  delay(5);
}

