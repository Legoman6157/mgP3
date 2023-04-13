#include <IRremote.h>
#include <Servo.h>

IRsend  sender1,
        sender2;

IRrecv  receiver;

Servo flag1,
      flag2;

void setup() {
  Serial.begin(9600);
  sender1.begin(5);
  sender1.enableIROut(38);
  sender2.begin(3);
  sender2.enableIROut(38);

  receiver.begin(6);
  receiver.enableIRIn();

  flag1.attach(2);
  flag2.attach(4);

  flag1.write(0);
  flag2.write(0);

  pinMode(12, INPUT);
}

int b;

long decodedData;

bool flag1_down = true,
      flag2_down = true;

bool button_pressed;

void loop() {
  button_pressed = digitalRead(12) == HIGH;
  sender1.sendDenon(0x800000FF, 32);
  sender2.sendDenon(0x400000FF, 32);

  if (receiver.decode()) {
    decodedData = receiver.decodedIRData.decodedRawData;
    if ((decodedData == 0xFF000001) && (button_pressed) && (flag1_down)) {
      Serial.println("Sender 1");
      flag1.write(90);
      flag1_down = false;
    }
    else if ((decodedData == 0xFF000002) && (button_pressed) && (flag2_down)) {
      Serial.println("Sender 2");
      flag2.write(90);
      flag2_down = false;
    }
    receiver.resume();
  }
}