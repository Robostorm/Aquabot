#include <Servo.h>

#define READY 0
#define GETTING 1
#define DISPENSING 2
#define DONE 3
#define IRPIN 23
#define PHOTOPIN 22
#define BILLPIN 25
#define SERVOPIN 20
#define LEDPIN 6

Servo servo; // create servo object to control a servo

int ledState = 0;
int irState = 0;
int photoState = 0;

int billPower = 0;
int servoPos = 90;

int state = 1;

void setup(){
  Serial.begin(9600); // Begin Serial communication to display
  Serial.println("Running Setup"); // Print LCD message
  
  servo.attach(SERVOPIN); // attaches the servo on pin 20
  
  //Inputs
  pinMode(IRPIN, INPUT); // Infrared dollar sensor
  pinMode(PHOTOPIN, INPUT); // detector to verify bill is being accepted
  
//Outputs
  pinMode(BILLPIN, OUTPUT); // Motor output
  pinMode(LEDPIN, OUTPUT);  // LED output
}
void loop(){
  int now = millis();
  sensorUpdate(now);
  motorUpdate(now);
  ledUpdate(now);
  Serial.println(state);
  switch(state){
    case READY:
      if(IRPIN == 0){
        state = GETTING;
      }
      return;
    case GETTING:
      billPower = 255;
      if(PHOTOPIN == HIGH) {
        state = DISPENSING;
      }
      return;
    case DISPENSING:
      if(PHOTOPIN == HIGH){
        return;
      }
      billPower = 0;
      dispense();
      state = DONE;
      return;
    case DONE:
      Serial.println("Thank you and have a nice day.");
      state = READY;
    return;
  }
}

void sensorUpdate(unsigned long now){
  static unsigned long sensorMillis = 0UL;
  
  if(now - sensorMillis >= 10UL){
    irState = digitalRead(IRPIN);
    photoState = digitalRead(PHOTOPIN);
    sensorMillis = now;
  }
}

void motorUpdate(unsigned long now){
  static unsigned long motorMillis = 0UL;
  
  if(now - motorMillis >= 10UL){
    analogWrite(BILLPIN, billPower);
    servo.write(servoPos);
    motorMillis = now;
  }
}

void ledUpdate(unsigned long now){
  static unsigned long ledMillis = 0UL;
  
  if(now - ledMillis >= 1000UL){
    if(ledState == HIGH){
      ledState = LOW;
    }else if(ledState == LOW) {
      ledState = HIGH;
    }
    digitalWrite(LEDPIN, ledState);
    ledMillis = now;
  }
}

void dispense(){
  for (servoPos = 5; servoPos < 85; servoPos++){}
  for (servoPos = 85; servoPos > 5; servoPos--){}
}
