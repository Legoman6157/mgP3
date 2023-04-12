#include <IRremote.hpp>

int RECV_PIN = 2;
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.begin(RECV_PIN, ENABLE_LED_FEEDBACK); // Start the receiver
}

void loop()
{
  if (irrecv.decode())
    {
      irrecv.printIRResultShort(&Serial);
      Serial.println(irrecv.decodedIRData.decodedRawData);
      Serial.println(irrecv.decodedIRData.decodedRawData, HEX);
      irrecv.resume(); // Receive the next value
    }
}