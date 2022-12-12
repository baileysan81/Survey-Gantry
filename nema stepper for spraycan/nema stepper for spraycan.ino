#include <Stepper.h>
#define STEPS 200
Stepper Stepper(STEPS, 2, 3);
#define motorInterfaceType 1


void setup() {
  
  Serial.begin(9600);
  // pinMode(SW, INPUT);
  // pinMode(MS1, OUTPUT);
  // pinMode(MS2, OUTPUT);
}

void loop() {
  Stepper.setSpeed(500);
  Serial.print("hmmm");
  Stepper.step(50);
  Serial.print(" not yet...");
  delay(20);
  Serial.println(" done waiting");
  Stepper.step(-25);
}