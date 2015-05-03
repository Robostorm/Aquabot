#include <Servo.h>

#define ALILE 1
#define ELEV 0

#define LEFTMOTOR 5
#define RIGHTMOTOR 6

#define ALILEZERO 1500
#define ALILEMAX 1000
#define ALILEMIN 2000
#define ALILEDEAD 50

#define ELEVZERO 1500
#define ELEVMAX 1000
#define ELEVZMIN 2000
#define ELEVDEAD 100

int time = 0;
int printTime = 0;
int alie = 0;
int elev = 0;
int oldAlie = 0;
int oldElev = 0;
int leftMotor = 0;
int rightMotor = 0;

Servo leftServo;
Servo rightServo;
 
void setup() {
  leftServo.attach(LEFTMOTOR);
  rightServo.attach(RIGHTMOTOR);
  pinMode(ALILE, INPUT);
  pinMode(ELEV, INPUT);
  Serial.begin(9600);
  attachInterrupt(ALILE, alieRising, RISING);
  attachInterrupt(ELEV, elevRising, RISING);
  time = millis();
  printTime = time;
}
 
void loop() {
  time = millis();
  if (time - printTime >= 100) {
    Serial.print(alie);
    Serial.print(" : ");
    Serial.println(elev);
    printTime = time;
  }
  
  //motors
  if (alie < 1500 - ALILEDEAD || alie > 1500 + ALILEDEAD) {
    leftServo.write(map(alie, 1000, 2000, 0, 180));
  } else {
    leftServo.write(90);
  }
  if (elev < 1500 - ELEVDEAD || elev > 1500 + ELEVDEAD) {
    rightServo.write(map(elev, 1000, 2000, 0, 180));
  }  else {
    rightServo.write(90);
  }
}

void alieRising() {
  attachInterrupt(ALILE, alieFalling, FALLING);
  oldAlie = micros();
}
 
void alieFalling() {
  attachInterrupt(ALILE, alieRising, RISING);
  alie = micros() - oldAlie;
}

void elevRising() {
  attachInterrupt(ELEV, elevFalling, FALLING);
  oldElev = micros();
}
 
void elevFalling() {
  attachInterrupt(ELEV, elevRising, RISING);
  elev = micros() - oldElev;
}

