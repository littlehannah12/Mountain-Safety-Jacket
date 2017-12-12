//Hannah Rudin 11.28.2017
//Making Studio Final Project: Mountain Safety Jacket draft1

//PURPOSE: allow wearer to adjust through several light settings using single analog soft-button.
// Use tilt switch to read user's motion: if wearer is motionless for more than 10s,
// lights will begin blinking endlessly until circuit is reset. (This timer will last longer on the actual
// product, but is short for demo purposes.)

#include <Adafruit_NeoPixel.h>

//Output Pins
#define PIXEL_PIN_L 6 //left arm
#define PIXEL_PIN_R 1 //right arm
#define PIXEL_PIN_H 9 //head
#define BOARD_PIXEL 8 //floraboard neopixel

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

//// timer 10s (~1000 counts of 10ms)
//#define TIMER_MAX_COUNT 1000
//int timercount = 0;

//tilt switch
#define SENSOR1 12 //for sensing movement (tilt switch)
 
int LEDstate = HIGH;      // the current state of the output pin
int reading;           // the current reading from the input pin
int previous = LOW;    // the previous reading from the input pin
 
// the follow variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long time = 0;         // the last time the output pin was toggled
long timer_max = 100000;   // the debounce time, increase if the output flickers

// toggle settings
#define BUTTON1 10 //for toggling settings
//#define THRESHOLD 10
int buttonread;
int debouncecount = 0;
int setting = 0;

//initialize integers
//int buttonSample = 0;
//int vibeRead = 0;

void setup() 
{
  Serial.begin(9600);
  pinMode(SENSOR1, INPUT); //set tilt switch sensor as input
  pinMode(BUTTON1, INPUT); //set toggle button sensor as input
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
  //soft button
  buttonread = digitalRead(BUTTON1);
  if(debouncecount == 0 && buttonread == HIGH)
  {
    setting += 1;
    toggleLights(setting);
  }
  debouncecount += 1;
  if(debouncecount > 10)
  {
    debouncecount = 0;
  }

if(setting > 3)
{
  setting = 0;
}
  
  //movement sensor
  int switchstate;
  reading = digitalRead(SENSOR1);
  // If the switch changed, due to bounce or pressing...
  if (reading != previous) {
    // reset the debouncing timer
    time = millis();
  } 
 
  if ((millis() - time) > timer_max) {
     // whatever the switch is at, its been there for a long time
     endlessBlink(setting);
}
last = current;
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
      exitBlink();
      break;
//    case 5:
//      wristsBrightWhite();
//      break;
    default:
      allOff();  
  }
showStrips();
}

void endlessBlink()
{
  while(1)
  {
    allBrightRed();
    showStrips();
    delay(1000);
    allOff();
    showStrips();
    delay(500);
  }
}

void exitBlink(int setting)
{
  int current = setting;
  while(current == setting)
  {
    allBrightRed();
    showStrips();
    delay(1000);
    allOff();
    showStrips();
    delay(500);
    int button = digitalRead(BUTTON1);
    if(button == HIGH)
    {
      current += 1;
    }
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

void showStrips()
{
  for(int n = 0; n < NUMSTRIPS; n++)
  {
    strip[n].show();
  }
}
