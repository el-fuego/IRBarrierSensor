#include <IRBarrierSensor.h>

// setup pin
int barrierSensorPin = A3;

void setup() {
  // declare the LED pin as an OUTPUT:
  pinMode(LED_BUILTIN, OUTPUT);
}

IRBarrierSensor barrierSensor(barrierSensorPin);

void loop() {
  // turn ON builtin LED if barrier is detected
  digitalWrite(LED_BUILTIN, barrierSensor.hasBarrier() ? HIGH : LOW);
  
  delay(100);
}
