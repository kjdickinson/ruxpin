#include <Servo.h>  // servo library

// Simple sketch to demo the Bearduino
// Allow the user to control eyes and mouth and run a demo

Servo teddy;  
const int sleepLedPin = 12;
const int eyesLedPin = 11;
const int mouthLedPin = 10;

const int servoPin = 9;


void setup()
{
  pinMode(sleepLedPin, OUTPUT);
  pinMode(eyesLedPin, OUTPUT);
  pinMode(mouthLedPin, OUTPUT);
  
  teddy.attach(servoPin);
}

void loop(){
  
  // Blink all the leds
  // On
  for (int i = 0; i < 5; i += 1){
    setAllLED(HIGH);
    delay(500);
    // Off
    setAllLED(LOW);
    delay(500);
  }
  
  // All closed for 5 seconds
  digitalWrite(sleepLedPin, HIGH);
  teddy.write(180);
  delay(5000);
  digitalWrite(sleepLedPin, LOW);
  // Eyes open for 5 seconds
  digitalWrite(eyesLedPin, HIGH);
  teddy.write(90);
  delay(5000);
  digitalWrite(eyesLedPin, LOW);
  // Mouth open for 5 seconds
  digitalWrite(mouthLedPin, HIGH);
  teddy.write(0);
  delay(5000);
  digitalWrite(mouthLedPin, LOW);
  
}
  
  
void setAllLED(int state)
{
  digitalWrite(sleepLedPin, state);
  digitalWrite(eyesLedPin, state);
  digitalWrite(mouthLedPin, state);
}
