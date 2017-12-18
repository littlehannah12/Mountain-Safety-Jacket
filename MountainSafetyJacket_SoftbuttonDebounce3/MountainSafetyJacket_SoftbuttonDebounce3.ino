/* Better Debouncer
 * 
 * This debouncing circuit is more rugged, and will work with tilt switches!
 *
 * http://www.ladyada.net/learn/sensor/tilt.html
 */

#include <Bounce2.h>
 
int inPin = 10;         // the number of the input pin
Bounce button = Bounce();
int buttonval;
int setting = 0;
 
void setup()
{
  pinMode(inPin, INPUT_PULLUP);
  button.attach(inPin);
  button.interval(150);
  Serial.begin(9600);
}
 
void loop()
{
 button.update();
 buttonval = button.read();
 if(buttonval == LOW)
 {
  setting += 1;
  Serial.println(setting);
 }
}

