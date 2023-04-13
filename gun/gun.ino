#include "ICM_20948.h"
#include "Servo.h"
#include <math.h>
#include <IRremote.hpp>

ICM_20948_I2C myICM;

Servo myServos[3];

int servo_pins[3] = {2, 4, 7};
int initial_angles[3] = {90,90,90};

IRrecv receiver;

void setup() {
  Wire.begin();
  Wire.setClock(400000);

  Serial.begin(9600);

  for (int i = 0; i < 3; ++i) {
    myServos[i].attach(servo_pins[i]);
    myServos[i].write(initial_angles[i]);
  }

  bool initialized = false;
  while (!initialized) {

    myICM.begin(Wire, 0x69);

    if (myICM.status == ICM_20948_Stat_Ok)
      initialized = true;
    else
      delay(100);
  }

  receiver.begin(11, ENABLE_LED_FEEDBACK);
  receiver.enableIRIn();
}

int boundary_angles[3] = {10,10,10};
int angle_deltas[3] = {3,3,3};

int angles[3] = {90,90,90};

float values[3];

void loop() {

  if (receiver.decode()) {
    receiver.printIRResultShort(&Serial);
  }

  // put your main code here, to run repeatedly:
  if (myICM.dataReady()) {
    myICM.getAGMT();

    values[0] = myICM.gyrX();
    values[1] = -myICM.gyrY();
    values[2] = myICM.gyrZ();

    for (int i = 0; i < 3; ++i)
      if (values[i] > boundary_angles[i]) {
        if (angles[i] != 180) {
          angles[i] += angle_deltas[i];
          if (angles[i] > 180)
            angles[i] = 180;
          myServos[i].write(angles[i]);
          delay(7);
        }
      } else if (values[i] < -boundary_angles[i]) {
        if (angles[i] != 0) {
          angles[i] -= angle_deltas[i];
          if (angles[i] < 0)
            angles[i] = 0;
          myServos[i].write(angles[i]);
          delay(7);
        }
      }

    delay(30);
  }
}
