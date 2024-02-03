#include <Arduino.h>
#include "HID-Project.h"

#include "controller.cpp"


Controller* c = new Controller();

int reverserPin = A0;
int throttlePin = A1;
int dynamicBrakePin = A2;
int autoBrakePin = A3;
int independentBrakePin = A4;

int reverser = 0;
int throttle = 0;
int dynamicBrake = 0;
int autoBrake = 0;
int independentBrake = 0;

// Raildriver only sends 15 bytes, but there's a bug with one of the Arduino libraries where buffers under 64 bytes won't send. Sending 64 doesn't cause a problem.
uint8_t writeBuffer[64]; 
uint8_t rawhidData[255];


void setup()
{
    RawHID.begin(rawhidData, sizeof(rawhidData));
    Serial.begin(9600);
    
    for(int i = 0; i < sizeof(writeBuffer); i++)
    {
      writeBuffer[i] = 0;
    }

    writeBuffer[14] = 210;
}

void loop()
{
  reverser = analogRead(reverserPin);
  throttle = analogRead(throttlePin);
  dynamicBrake = analogRead(dynamicBrakePin);
  autoBrake = analogRead(autoBrakePin);
  independentBrake = analogRead(independentBrakePin);

  c->setReverser(reverser);
  c->setThrottle(throttle);
  c->setDynamicBrake(dynamicBrake);
  c->setAutoBrake(autoBrake);
  c->setIndependentBrake(independentBrake);

  Serial.print(",Throttle:");
  Serial.print(throttle);
  Serial.print(",DynamicBrake:");
  Serial.print(dynamicBrake);
  Serial.print(",ComputedThrottle:"); // mixed throttle/dynamic brake for Run8
  Serial.println(c->getThrottle());

  writeBuffer[0] = c->getReverser();
  writeBuffer[1] = c->getThrottle();
  writeBuffer[2] = c->getAutoBrake();
  writeBuffer[3] = c->getIndependentBrake();

  RawHID.write(writeBuffer, sizeof(writeBuffer));
  delay(50); // who knows how fast we can go?

}