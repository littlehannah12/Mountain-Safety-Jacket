// toggle settings
#define BUTTON1 10 //for toggling settings
//#define THRESHOLD 10
int buttonread;
int last = HIGH;
int count = 0;

void setup() {
pinMode(BUTTON1, INPUT_PULLUP); //set toggle button sensor as input
Serial.begin(9600);
}

void loop() {

toggle();

}

void toggle()
{
  //soft button
  buttonread = digitalRead(BUTTON1);
  if(buttonread == last)
  {
    return;
  }
  else {
  Serial.println("toggle");
  Serial.println(count);
  count += 1;
  }
  delay(30);
  buttonread = last;
}

