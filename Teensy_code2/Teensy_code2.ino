// Initial code by Derrick and Mike Rowe 04/26/2014
//Code by Ben Goldberg, Tim and Andrew Hollabaugh

//Pins taken 2,3,4,5,6,7,8,11,20

//Servo section
#include <Servo.h>

#define WAITING 0; //Waiting for bill
#define GETTING_BILL 1; //Brining bill in
#define DISPENSING_BOTTLE 2; //Dispensing Bottle
#define DONE 3; //Any finishing code

Servo myservo; // create servo object to control a servo
int pos = 0; // variable to store the servo position

int led = 6; //Teensy has LED on a different pin
int ir = 23;
int photo = 22;
int bill = 25;
int isBill = 0;
int state = 1;


void setup() {
  myservo.attach(20); // attaches the servo on pin 20
  
  Serial.begin(9600); // Begin Serial communication to display
  Serial.println("Place dollar bill into robot where indicated"); // Print LCD message
  
//Inputs
  pinMode(ir, INPUT); // Infrared dollar sensor
  pinMode(photo, INPUT); // detector to verify bill is being accepted
  
//Outputs
  pinMode(bill, OUTPUT); // Motor output
  pinMode(led, OUTPUT);  // LED output
  
  digitalWrite(led, HIGH);
}
 
 
void loop()
{
  TimerUpdate();
}

void TimerUpdate(){
  unsigned long cur_millis;
  static unsigned long BillMillis = 0UL;
  static unsigned long ServoMillis = 0UL;
  
  cur_millis = millis();
  if(cur_millis - BillMillis >= 10UL){
    BillUpdate();
    BillMillis = cur_millis;
  }
  if(cur_millis - ServoMillis >= 10UL){
    ServoUpdate();
    ServoMillis = cur_millis;
  }
}

void BillUpdate(){
  if (digitalRead(ir) == LOW) {
    analogWrite(bill, 255);
    delay(2000);
    if (digitalRead(photo) == HIGH) {
      while (photo == HIGH) {
    }
    analogWrite(bill, 0);
    Serial.println("Thank You");
    isBill = 1;
  } else {
    analogWrite(bill, 0);
    Serial.println("No Bill Detected");
    isBill = 0;
  }
}
 
/*
for (pos = 5; pos < 85; pos++){ // goes from 5-85 degrees in steps of 1 degree
  myservo.write(pos); // tell servo to go to position in variable 'pos'
  delay(200); // waits 200ms for the servo to reach the position
}
for (pos = 85; pos > 5; pos--){ // goes from 85-5 degrees in steps of 1 degree
  myservo.write(pos); // tell servo to go to position in variable 'pos'
  delay(200); // waits 200ms for the servo to reach the position
}
*/
}
