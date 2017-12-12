#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

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


// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code


  leftstrip.begin();
  leftstrip.show(); // Initialize all pixels to 'off'
  rightstrip.begin();
  rightstrip.show();
  headstrip.begin();
  headstrip.show();
  floraboard.begin();
  floraboard.show();
}

void loop() {
  // Some example procedures showing how to display to the pixels:
  colorWipe(leftstrip,leftstrip.Color(255, 0, 0), 50); // Red
  colorWipe(rightstrip,rightstrip.Color(255, 0, 0), 50); // Red
  colorWipe(headstrip,headstrip.Color(255, 0, 0), 50); // Red
  colorWipe(floraboard,floraboard.Color(255, 0, 0), 50); // Red
//  colorWipe(strip.Color(0, 255, 0), 50); // Green
//  colorWipe(strip.Color(0, 0, 255), 50); // Blue
//colorWipe(strip.Color(0, 0, 0, 255), 50); // White RGBW
  // Send a theater pixel chase in...
  theaterChase(leftstrip,leftstrip.Color(127, 127, 127), 50); // White
  theaterChase(rightstrip,rightstrip.Color(127, 127, 127), 50); // White
  theaterChase(headstrip,headstrip.Color(255, 255, 255), 50); // White
  theaterChase(floraboard,floraboard.Color(127, 127, 127), 50); // White
  theaterChase(leftstrip,leftstrip.Color(127, 0, 0), 50); // Red
  theaterChase(rightstrip,rightstrip.Color(127, 0, 0), 50); // Red
  theaterChase(headstrip,headstrip.Color(255, 0, 0), 50); // Red
  theaterChase(floraboard,floraboard.Color(127, 0, 0), 50); // Red
  theaterChase(leftstrip,leftstrip.Color(0, 127, 0), 50); // Red
  theaterChase(rightstrip,rightstrip.Color(0, 127, 0), 50); // Red
  theaterChase(headstrip,headstrip.Color(0, 255, 0), 50); // Red
  theaterChase(floraboard,floraboard.Color(0, 127, 0), 50); // Red

//  rainbow(20);
//  rainbowCycle(20);
//  theaterChaseRainbow(50);
}

// Fill the dots one after the other with a color
void colorWipe(Adafruit_NeoPixel strip, uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(Adafruit_NeoPixel strip, uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//// Input a value 0 to 255 to get a color value.
//// The colours are a transition r - g - b - back to r.
//uint32_t Wheel(Adafruit_NeoPixel strip, byte WheelPos) {
//  WheelPos = 255 - WheelPos;
//  if(WheelPos < 85) {
//    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
//  }
//  if(WheelPos < 170) {
//    WheelPos -= 85;
//    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
//  }
//  WheelPos -= 170;
//  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
//}
