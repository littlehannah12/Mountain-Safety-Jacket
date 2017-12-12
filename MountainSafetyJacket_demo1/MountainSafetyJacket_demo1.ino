//Hannah Rudin 11.28.2017
//Making Studio Final Project: Mountain Safety Jacket draft1

//PURPOSE: allow wearer to adjust through several light settings using single analog soft-button.
// Use vibration switch (fast sensor) to read user's motion: if wearer is motionless for more than 10s,
// lights will begin blinking endlessly until circuit is reset. (This timer will last longer on the actual
// product, but is short for demo purposes.)

#include <Adafruit_NeoPixel.h>

//Output Pins
#define PIXEL_PIN_L 6
#define PIXEL_PIN_R 1
#define PIXEL_PIN_H 9
#define BOARD_PIXEL 8

//Input Pins
//#define BUTTON1 A11;
//#define VIBE1 1;

#define BRIGHTNESS 50

//neopixel on FLORA board
Adafruit_NeoPixel floraboard = Adafruit_NeoPixel(1, BOARD_PIXEL, NEO_GRB + NEO_KHZ800);

// pixel strips
Adafruit_NeoPixel leftstrip = Adafruit_NeoPixel(4, PIXEL_PIN_L, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel rightstrip = Adafruit_NeoPixel(4, PIXEL_PIN_R, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel headstrip = Adafruit_NeoPixel(4, PIXEL_PIN_H, NEO_GRB + NEO_KHZ800);

Adafruit_NeoPixel strip[] = {floraboard,leftstrip,rightstrip,headstrip};
int numPix[] = {floraboard.numPixels(),leftstrip.numPixels(),rightstrip.numPixels(),headstrip.numPixels()};
#define NUMSTRIPS 4

// timer 10s (~1000 counts of 10ms)
//#define TIMER_MAX_COUNT 1000;
//int timercount = 0;

// toggle settings
//#define THRESHOLD 10;
int setting = 0;

//initialize integers
//int buttonSample = 0;
//int vibeRead = 0;

void setup() 
{
  Serial.begin(9600);
//  pinMode(VIBE1,INPUT);

// initialize strips to off
for(int n = 0; n < NUMSTRIPS; n++)
{
    strip[n].setBrightness(BRIGHTNESS);
    strip[n].begin();
    strip[n].show();
}
}

void loop() 
{
  //analog button
//  buttonSample = analogRead(BUTTON1);
//  if(buttonSample < threshold)
//  {
//    setting += 1;
//    toggleLights(setting);
//  }
Serial.println(setting);
toggleLights(setting);
delay(5000);
setting += 1;

if(setting > 4)
{
  setting = 0;
}
  //vibration sensor
 // vibeRead = digitalRead(VIBE1);
  //if person is not moving
//  if(vibeRead == LOW)
//  {
//    timercount += 1;
//    if(timercount > TIMER_MAX_COUNT)
//    {
//      endlessBlink();
//    }
//    delay(10);
//  }
//  else
//  {
//    timercount = 0;
//  }
}

void toggleLights(int setting)
{

  switch(setting) {
    case 0:
      allOff();
      break;
    case 1:
      allBrightWhite();
      break;
    case 2:
      allHalfWhite();
      break;
    case 3:
      allBrightRed();
      break;
    case 4:
      fiveBlink();
      break;
//    case 5:
//      wristsBrightWhite();
//      break;
    default:
      allOff();  
  }

  for(int n = 0; n < NUMSTRIPS; n++)
  {
    strip[n].show();
  }
}

void endlessBlink()
{
  while(1)
  {
    allBrightRed();
    delay(1000);
    allOff();
    delay(1000);
  }
}

void allBrightWhite()
{
  for(int n = 0; n < NUMSTRIPS; n++)
  {
    strip[n].setBrightness(BRIGHTNESS);
    for(int p = 0; p < numPix[n]; p++)
    {
    strip[n].setPixelColor(p, strip[n].Color(255,255,255));
    }
  }
}

void allHalfWhite()
{
  for(int n = 0; n < NUMSTRIPS; n++)
  {
    strip[n].setBrightness(BRIGHTNESS/2);
    for(int p = 0; p < numPix[n]; p++)
    {
    strip[n].setPixelColor(p, strip[n].Color(255,255,255));
    }
  }
}

void allBrightRed()
{
  for(int n = 0; n < NUMSTRIPS; n++)
  {
    strip[n].setBrightness(BRIGHTNESS);
    for(int p = 0; p < numPix[n]; p++)
    {
    strip[n].setPixelColor(p, strip[n].Color(255,0,0));
    }
  }
}

void headBrightWhite()
{
  leftstrip.setBrightness(BRIGHTNESS);
  floraboard.setBrightness(BRIGHTNESS);
  
  for(int p = 0; p < 4; p++)
  {
    leftstrip.setPixelColor(p, leftstrip.Color(255,255,255));
  }
  floraboard.setPixelColor(1,floraboard.Color(255,255,255));
}

void wristsBrightWhite()
{
  leftstrip.setBrightness(BRIGHTNESS);
  floraboard.setBrightness(BRIGHTNESS);
  
  for(int p = 4; p < 12; p++)
  {
    leftstrip.setPixelColor(p, leftstrip.Color(255,255,255));
  }
  floraboard.setPixelColor(1,floraboard.Color(255,255,255));
}

void allOff()
{ 
  for(int n = 0; n < NUMSTRIPS; n++)
  {
    strip[n].setBrightness(BRIGHTNESS);
    for(int p = 0; p < numPix[n]; p++)
    {
    strip[n].setPixelColor(p, strip[n].Color(0,0,0));
    }
  }
}

void fiveBlink()
{ 
  for(int k = 0; k < 5; k++)
    {
    allBrightRed();
      for(int n = 0; n < NUMSTRIPS; n++)
  {
    strip[n].show();
  }
    delay(2000);
    allOff();
      for(int n = 0; n < NUMSTRIPS; n++)
  {
    strip[n].show();
  }
    delay(1000);
    }
}
