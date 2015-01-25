#include <Servo.h>  // servo library

/* Simple sketch to demo the Bearduino
   Press button 1 to toggle eyes
   Press button 2 to toggle mouth
   Press both buttons to run demo
   
   Watch the demo at https://www.youtube.com/watch?v=n_XpuP_U368
*/
Servo teddy;  
const int eyeButtonPin = 3;
const int mouthButtonPin = 2;
const int servoPin = 9;
const int demoledPin = 13;

boolean teddyAwake;
boolean teddyShout;
boolean triggerDemo;

void setup()
{
  pinMode(eyeButtonPin, INPUT);
  pinMode(mouthButtonPin, INPUT);
  pinMode(demoledPin, OUTPUT);
  teddy.attach(servoPin);
  teddyAwake = false;
  teddyShout = false;
  triggerDemo = false;
}


void loop()
{
  // Bearduino
  // 180: Eyes and mouth closed
  // 179-91: Eyes opening, mouth closed
  // 90-1: Eyes fully open, mouth opening
  // 0: Eyes and mouth fully open

  int eyeButtonState, mouthButtonState;  // variables to hold the pushbutton states
  eyeButtonState = digitalRead(eyeButtonPin);
  mouthButtonState = digitalRead(mouthButtonPin);
  
  if ((eyeButtonState == LOW) && (mouthButtonState != LOW))
  {  
    // Just the eye button is pressed
    if (teddyAwake){
      teddyAwake = false;
      teddyShout = false;
    }else{
      teddyAwake = true;
      teddyShout = false;
    }
    delay(100);
  }
  else if ((eyeButtonState != LOW) && (mouthButtonState == LOW))
  {
    // Just the mouth button is pressed
    if (teddyShout){
      teddyAwake = true;
      teddyShout = false;
    }else{
      teddyAwake = true;
      teddyShout = true;
    }
    delay(100);
  }
  else if ((eyeButtonState == LOW) && (mouthButtonState == LOW))
  {
    // Both buttons are pressed
   triggerDemo = true;
   delay(100);
  }   
    
  
  if (triggerDemo){
    demoTeddy();
    triggerDemo = false;
  }else if (teddyShout){
    shockTeddy();
  }else if (teddyAwake){
    wakeTeddy();
  }else{
    restTeddy();
  }
  // make it easier to press both buttons
  delay(100);
}


void restTeddy(){
  // Set servo to 180
  teddy.write(180);
  teddyAwake = false;
  teddyShout = false;
}

void wakeTeddy(){
  // Set servo to 90
  teddy.write(90);
  teddyAwake = true;
  teddyShout = false;
}

void shockTeddy(){
  // Set servo to 180
  teddy.write(0);
  teddyAwake = true;
  teddyShout = true;
}

void demoTeddy(){

  // List the demo LED
  digitalWrite(demoledPin, HIGH);
  // Cycle through some states
  restTeddy();
  delay(500);
  // Blinks eyes
  for (int i = 0; i<5; i++)
  {
    restTeddy();
    delay(500);
    wakeTeddy();
    delay(500);
  }
  
  delay(100);
  
  // Yawn (Slow open, fast close)
  for(int position = 90; position >= 0; position--)
  {                                
    teddy.write(position); 
    delay(20); 
  }
  
  delay(2000);
  
  restTeddy();
  delay(2000);
  
  // Turn off the demo LED
  digitalWrite(demoledPin, LOW);
}

