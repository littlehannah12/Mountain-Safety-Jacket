/* Better Debouncer
 * 
 * This debouncing circuit is more rugged, and will work with tilt switches!
 *
 * http://www.ladyada.net/learn/sensor/tilt.html
 */
 
int inPin = 2;         // the number of the input pin
//int outPin = 13;       // the number of the output pin
 
//int LEDstate = HIGH;      // the current state of the output pin
int reading;           // the current reading from the input pin
int previous = LOW;    // the previous reading from the input pin
 
// the follow variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long time = 0;         // the last time the output pin was toggled
long debounce = 300;   // the debounce time, increase if the output flickers
 
void setup()
{
  pinMode(inPin, INPUT);
  Serial.begin(9600);
}
 
void loop()
{
  int switchstate;
 
  reading = digitalRead(inPin);
 
  // If the switch changed, due to bounce or pressing...
  if (reading != previous) {
    // reset the debouncing timer
    time = millis();
    Serial.println("press");
  } 
 
//  if ((millis() - time) > debounce) {
//     // whatever the switch is at, its been there for a long time
//     // so lets settle on it!
//     
//  }
 
  // Save the last reading so we keep a running tally
  previous = reading;
}

