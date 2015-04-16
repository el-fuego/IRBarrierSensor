
#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include "IRBarrierSensor.h"

void IRBarrierSensor::assideCalibration () {
  lastCalibrationTime = millis();
}
bool IRBarrierSensor::isNeedCalibration (bool hasBarrier) {
  if (calibrationInterval == 0) {
    return false;
  }
  if (hasBarrier) {
    assideCalibration();
    return false;
  }
  return lastCalibrationTime < millis() - calibrationInterval;
}

IRBarrierSensor::IRBarrierSensor(int _sensorPin, float _sensivityLimit, int _calibrationInterval) : sensorPin(_sensorPin), sensivityLimit(_sensivityLimit), calibrationInterval(_calibrationInterval) {
  calibrate();
}

void IRBarrierSensor::calibrate () {
  assideCalibration();
  defaultValue = analogRead(sensorPin);
  
  Serial.println("Sensor was calibrated");
}

bool IRBarrierSensor::getRaw () {
  float sensorValue = analogRead(sensorPin);
  float deviation = 1 - sensorValue/defaultValue;
  bool hasBarrier = deviation > sensivityLimit;
  
  if(isNeedCalibration(hasBarrier)) {
    calibrate();
  }
  
  return deviation;
}

bool IRBarrierSensor::hasBarrier () {
  float deviation = getRaw();
  
  return deviation > sensivityLimit;
}
