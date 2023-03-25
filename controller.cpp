#include <Arduino.h>


class Controller {

private:

  const int dynamicMin = 0; // full dynamics
  const int dynamicMax = 127; // minimum dynamics

  const int throttleMin = 128; // n0
  const int throttleMax = 255; // n8

  int reverser; 
  int throttleDynamicBrake; 
  int autoBrake;
  int independentBrake;

  bool dynamicBrakeRangeActive() {
    return (throttleDynamicBrake < dynamicMax && throttleDynamicBrake > dynamicMin);
  }

  bool throttleRangeActive() {
    return (throttleDynamicBrake > throttleMin);
  }        

public:
  void setReverser(int value) {
    reverser = map(value, 0, 1024, 0, 255);
  };

  // value = 0 is idle, value = 255 is n8
  bool setThrottle(int value){
    if(!dynamicBrakeRangeActive()) {
      throttleDynamicBrake = map(value, 0, 1024, this->throttleMin, this->throttleMax);
      return true;
    } 

    return false;
  };

  // value = 0 is set-up, value = 255 is b8
  bool setDynamicBrake(int value){
    if(!throttleRangeActive()) {
      throttleDynamicBrake = map(value, 0, 1024, this->dynamicMax, this->dynamicMin);
      return true;
    } 

    return false;
  };

  void setAutoBrake(int value){
    autoBrake = map(value, 0, 1024, 0, 255);
  };

  void setIndependentBrake(int value){
    independentBrake = map(value, 0, 1024, 0, 255);
  };

  int getReverser() {
    return reverser;
  }

  int getThrottle() {
    return throttleDynamicBrake; 
  }

  int getAutoBrake() {
    return autoBrake;
  }

  int getIndependentBrake() {
    return independentBrake;
  }
};