int sensor = 3; // sensor pin
int led = 9; // default led on arduino

void setup() {

pinMode(sensor,INPUT_PULLUP);

pinMode(led,OUTPUT);

Serial.begin(9600);

}

void loop() {

int voltage = digitalRead(sensor); // read sensor here

Serial.println (voltage); // print voltage to serial monitor on pc

delay (100);

if (voltage < 1) { // if spring contacts on shaking

digitalWrite (led, HIGH); // turn on led to show that vibration is sensed

delay (2000);

digitalWrite (led, LOW); // turn off led now

} // end if voltage

} // end loop
