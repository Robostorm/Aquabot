int led = 6;        //Teensy has LED on a different pin
int ir = 22;
int photo = 23;
int bill = 25;
int photoval = 0;
int irval = 0;

void setup() {
   Serial.begin(9600);   // Begin Serial communication to display
  Serial.print("Place dollar bill into robot where indicated"); // Print LCD message

//Inputs
  pinMode(ir, INPUT); 	// Infrared dollar sensor
  pinMode(photo, INPUT); 	// detector to verify bill is being accepted

//Outputs
  pinMode(bill, OUTPUT);       	// LED output
  pinMode(led, OUTPUT);	// LED output
  
  digitalWrite(led, HIGH);
  analogWrite(bill, 255);
}

void loop() {
  if (digitalRead(ir) == 0) {
    Serial.println("IR 0");
  }
  
  if (digitalRead(ir) == 1) {
    Serial.println("IR 1");
  }
  
  if (digitalRead(photo) == 0) {
    Serial.println("Photo 0");
  }
  
  if (digitalRead(photo) == 1) {
    Serial.println("Photo 1");
  }
}
