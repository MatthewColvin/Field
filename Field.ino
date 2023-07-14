#define DECODE_NEC // Includes Apple and Onkyo
#define DECODE_SAMSUNG

#include "IRTransciever.hpp"
#include <Arduino.h>
#include <ArduinoSTL.h>
#include <string.h>

#define STATUS_LED 7

IRChallenge *challenge;
class IRChallenge {
public:
  IRChallenge(IRTransceiver *anIr) : mIr(anIr) {}

  // Call in loop() do not block!!
  void handle() { mIr->handleRx(); }

  // Call to reset Challenge
  void reset();

private:
  enum class Challenge { ReceiveData, PerformOperation };

  void sendOperationToRover();
  IRTransceiver *mIr = nullptr;
};

void setup() {
  Serial.begin(9600);
  pinMode(STATUS_LED, OUTPUT);
  digitalWrite(STATUS_LED, 0);
  challenge = new IRChallenge(IRTransceiver::getInstance());
}

void loop() {
  challenge->handle();
  // Should not block will need to find a way to keep loop running.
}
