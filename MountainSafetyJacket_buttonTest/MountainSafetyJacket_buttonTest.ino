/*
Adafruit Arduino - Lesson 3. RGB LED
*/

const int button = 2;
int buttonval;
int count = 0;

//uncomment this line if using a Common Anode LED
//#define COMMON_ANODE

void setup()
{
  Serial.begin(9600);
  pinMode(button, INPUT_PULLUP);  
}

void loop()
{
  buttonval = digitalRead(button);

  if(buttonval == LOW)
  {
    Serial.print("press   ");
    Serial.println(count);
    count += 1;
    delay(120);
  }
  
}

