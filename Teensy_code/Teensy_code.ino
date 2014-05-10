// First attempt at Arduino 2.0 software Rev 1
// by Derrick and Mike Rowe 04/26/2014 

//Pins taken 2,3,4,5,6,7,8,11,20

//Servo section
#include <Servo.h> 
Servo myservo;  	// create servo object to control a servo  
int pos = 0;    	// variable to store the servo position

//Display section
#include <DogLcd.h>	// include the library code
/* We assume the following pins are connected:
 * LCD SI pin to digital pin 2
 * LCD CLK pin to digital pin 3
 * LCD RS pin to digital pin 4
 * LCD CSB pin to digital pin 5
 * LCD RESET pin is not used
 * LCD Backlight pin is not used
DogLcd lcd(2, 3, 4, 5);   // initialize the library with the numbers of the interface pins

  int ledPin = 11;  //Teensy has LED on a different pin


void setup() 
{
  myservo.attach(20);  // attaches the servo on pin 20 
 
  lcd.begin(DOG_LCD_M162);   // set up the LCD type and the contrast setting for the display
  lcd.print("Place dollar bill into robot where indicated"); // Print LCD message

//Inputs
  pinMode(PIN_7, INFRARED SENSOR); 	// Infrared dollar sensor
  pinMode(PIN_8, MONEY BILL SENSOR); 	// detector to verify bill is being accepted

//Outputs
  pinMode(PIN_6, OUTPUT);       	// LED output
  pinmode(ledPin, OUTPUT)		// LED output
}
 
 
void loop() 
{
  for(pos = 5; pos < 85; pos += 1)  // goes from 5-85 degrees in steps of 1 degree
  {                                  
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(200);                       // waits 200ms for the servo to reach the position 
  } 
  for(pos = 85; pos>=5; pos-=1)     // goes from 85-5 degrees in steps of 1 degree
  {                                
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(200);                       // waits 200ms for the servo to reach the position 
  } 

    
// NOT SURE IF ANY OF THIS WILL BE NEEDED ……………………………..

  if (digitalRead(PIN_D7)) {
    // D7 pin is high due to pullup resistor
    digitalWrite(PIN_D6, LOW);   // LED on
    delay(400);                  // Slow blink
    digitalWrite(PIN_D6, HIGH);  // LED off
    delay(400);
  } else {
    // D7 pin is low due to pushbutton pressed
    digitalWrite(PIN_D6, LOW);   // LED on
    delay(80);                   // Fast blink
    digitalWrite(PIN_D6, HIGH);  // LED off
    delay(80);
  }
}






 
 

