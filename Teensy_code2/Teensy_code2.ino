//Code by Ben Goldberg, Tim and Andrew Hollabaugh

#include Servo.h

#define READY 0
#define GETTING 1
#define DISPENSING 2
#define DONE 3
#define IRPIN 23
#define PHOTOPIN 22
#define BILLPIN 25
#define SERVOPIN 20

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
  
  servo.attach(servoPin); // attaches the servo on pin 20
  
  //Inputs
  pinMode(irPin, INPUT); // Infrared dollar sensor
  pinMode(photoPin, INPUT); // detector to verify bill is being accepted
  
//Outputs
  pinMode(billPin, OUTPUT); // Motor output
  pinMode(ledPin, OUTPUT);  // LED output
  
  digitalWrite(led, HIGH);
}
void loop(){
  int now = millis();
  sensorUpdate(now);
  motorUpdate(now);
  Serial.println(state);
  switch(state){
    case READY:
      if(irPin == 0){
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
    irState = digitalRead(irPin);
    photoState = digitalRead(photoPin);
    sensorMillis = cur_millis;
  }
}

void motorUpdate(unsigned long now){
  unsigned long cur_millis;
  static unsigned long motorMillis = 0UL;
  static unsigned long servoMillis = 0UL;
  
  if(now - motorMillis >= 10UL){
    analogWrite(billPin, billPower);
    servo.write(servoPos);
    motorMillis = now;
  }
}

void dispense(){
  for (servoPos = 5; servoPos < 85; servoPos++){}
  for (servoPos = 85; servoPos > 5; servoPos--){}
}
