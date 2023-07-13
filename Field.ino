#define DECODE_NEC // Includes Apple and Onkyo
#define DECODE_SAMSUNG

#include "IRTransciever.hpp"
#include <Arduino.h>
#include <string.h>

#define STATUS_LED 7

IRTransceiver *ir;

void setup() {
  Serial.begin(9600);
  pinMode(STATUS_LED, OUTPUT);
  digitalWrite(STATUS_LED, 0);

  ir = IRTransceiver::getInstance();
}

class IRChallenge {
public:
  IRChallenge(IRTransceiver *ir) {}

  void updateChallengeStatus();

private:
  enum class Challenge { SendData, PerformOperation };

  void sendOperationToRover();
};

void loop() {
  // Should not block will need to find a way to keep loop running.
  IRTransceiver::getInstance()->handleRx();

  // Serial.print("IR TX: Addr:" + String(txAddr) + " Val:" + String(txVal) +
  // "\r\n"); txVal++; digitalWrite(STATUS_LED, !digitalRead(STATUS_LED));
}
