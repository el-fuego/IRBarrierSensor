
#ifndef IRBarrierSensor_h
#define IRBarrierSensor_h

#if (ARDUINO >= 100)
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

// With LED always turned on
class IRBarrierSensor {
  private:
    unsigned long lastCalibrationTime = 0;
    float defaultValue;
    int sensorPin;
    
    void assideCalibration ();
    bool isNeedCalibration (bool hasBarrier);
  
  public:
    int calibrationInterval;
    float barrierLimitDeviation;
    
    IRBarrierSensor(int _sensorPin, float _barrierLimitDeviation = 0.15, int _calibrationInterval = 500);

    void calibrate ();

    bool hasBarrier ();
};

#endif
