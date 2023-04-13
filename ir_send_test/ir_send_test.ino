#include <IRLibAll.h>

IRsend mySender;

void setup() {
  Serial.begin(9600);
  mySender.
}

/* Instructions on how to set data that you want to send
 *    when using IRLibAll IRsend.send() with IRrecv from
 *    IRremote.hpp:
 * Example data: 0xDEADBEEF
 * -First, you need to reverse the order of the hex digits
 *  So, 0xDEADBEEF -> 0xFEEBDAED
 * -Then, for each of the digits, you reverse their bits.
 *  So, 0xFEEBDAED -> 0xF77DB57B
 * Now when you send 0xF77DB57B, the receiver will read
 *    0xDEADBEEF.
*/

void loop() {
  if (Serial.read() != -1) {
    //send a code every time a character is received from the serial port
    //Sony DVD power A8BCA
    mySender.send(NEC, 0xF77DB57B, 32);
    Serial.println("Sent message");
    delay(40);
  }
}