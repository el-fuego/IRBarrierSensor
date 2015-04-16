
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

IRBarrierSensor::IRBarrierSensor(int _sensorPin, float _barrierLimitDeviation, int _calibrationInterval) : sensorPin(_sensorPin), barrierLimitDeviation(_barrierLimitDeviation), calibrationInterval(_calibrationInterval) {
  calibrate();
}

void IRBarrierSensor::calibrate () {
  assideCalibration();
  defaultValue = analogRead(sensorPin);
  
  Serial.println("Sensor was calibrated");
}

bool IRBarrierSensor::hasBarrier () {
  float sensorValue = analogRead(sensorPin);
  float deviation = 1 - sensorValue/defaultValue;
  bool hasBarrier = deviation > barrierLimitDeviation;
  
  Serial.print("val: "); Serial.print(sensorValue);
  Serial.print(" ; def: "); Serial.print(defaultValue);
  Serial.print(" ; deviation: "); Serial.println(deviation);
  
  if(isNeedCalibration(hasBarrier)) {
    calibrate();
  }
  
  return hasBarrier;
}
