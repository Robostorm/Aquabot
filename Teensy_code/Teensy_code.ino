// First attempt at Arduino 2.0 software Rev 1
// by Derrick and Mike Rowe 04/26/2014 

//Pins taken 2,3,4,5,6,7,8,11,20

//Servo section
#include <Servo.h> 
Servo myservo;  	// create servo object to control a servo
int pos = 0;    	// variable to store the servo position

int led = 6;        //Teensy has LED on a different pin
int ir = 22;
int photo = 23;
int bill = 25;
int isBill = 0;


void setup() {
  myservo.attach(20);  // attaches the servo on pin 20 
 
  Serial.begin(9600);   // Begin Serial communication to display
  Serial.print("Place dollar bill into robot where indicated"); // Print LCD message

//Inputs
  pinMode(ir, INPUT); 	// Infrared dollar sensor
  pinMode(photo, INPUT); 	// detector to verify bill is being accepted

//Outputs
  pinMode(bill, OUTPUT);       	// LED output
  pinMode(led, OUTPUT);	// LED output
  
  digitalWrite(led, HIGH);
}
 
 
void loop() {
  if (digitalRead(ir) == HIGH) {
    analogWrite(bill, 255);
    delay(2000);
    if (digitalRead(photo) == HIGH) {
      while (photo == HIGH) { 
      }
      analogWrite(bill, 0);
      Serial.print("Thank You");
      isBill = 1;
    } else {
      analogWrite(bill, 0);
      Serial.print("No Bill Detected");
      isBill = 0;
    }
  }
  
/*
  for (pos = 5; pos < 85; pos++)  // goes from 5-85 degrees in steps of 1 degree
  {                                  
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(200);                       // waits 200ms for the servo to reach the position 
  } 
  for (pos = 85; pos > 5; pos--)     // goes from 85-5 degrees in steps of 1 degree
  {                                
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(200);                       // waits 200ms for the servo to reach the position 
  } 
  
*/
}









 
 

