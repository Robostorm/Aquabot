#define ALILE 1
#define ELEV 0

int time = 0;
int printTime = 0;
int alie = 0;
int elev = 0;
int oldAlie = 0;
int oldElev = 0;
 
void setup() {
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

