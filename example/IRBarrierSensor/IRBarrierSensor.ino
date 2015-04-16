#include <IRBarrierSensor.h>

// setup pin
const int barrierSensorPin = A3;

void setup() {
  // declare the LED pin as an OUTPUT:
  pinMode(LED_BUILTIN, OUTPUT);

  // setup serial output
  Serial.begin(9600);
}

IRBarrierSensor barrierSensor(barrierSensorPin);

void loop() {
  // turn ON builtin LED if barrier is detected
  digitalWrite(LED_BUILTIN, barrierSensor.hasBarrier() ? HIGH : LOW);
  
  // print current deviation
  Serial.println(barrierSensor.getRaw());
  
  delay(100);
}
