#pragma once
#include <IRremote.h>

#define IR_LED 5
#define IR_DETECT 6

class IRTransceiver {
public:
  static IRTransceiver *getInstance() {
    if (!mInstance) {
      mInstance = new IRTransceiver(IR_LED, IR_DETECT);
    }
    return mInstance;
  }

  IRTransceiver(int aTxPin, int aRxPin) {
    mIrSend.begin(aTxPin);
    mIrRec.begin(aRxPin);
    mIrRec.registerReceiveCompleteCallback(
        &IRTransceiver::ReceiveCompleteCallbackHandler);

    Serial.print(F("Ready to receive IR signals of protocols: "));
    printActiveIRProtocols(&Serial);

    Serial.print("\n on Pin:");
    Serial.print(aRxPin);
    Serial.print("\n");
  }

  // Kinda guessing at the emplementation of this function.
  // may need to play with how we do this.
  static void send(uint16_t address, uint16_t data) {
    // Send address and data no repeats
    auto sendData = address | (data << 16);
    mIrSend.sendNECMSB(sendData, 32);
    // mIrSend.sendNEC(address, data, 0);
  }

  static void handleRx() {
    if (mIRDataJustReceived) {
      Serial.print("GOT data");
      mIrRec.printIRResultShort(&Serial);
      mIrRec.printIRSendUsage(&Serial);
      mIRDataJustReceived = false;
    }
  }

  static void ReceiveCompleteCallbackHandler() {
    mIrRec.decode(); // fill IrReceiver.decodedIRData

    if (mIrRec.decodedIRData.command == 0x10) {
      // do something SHORT here
    } else if (mIrRec.decodedIRData.command == 0x11) {
      // do something SHORT here too
    }

    mIRDataJustReceived = true;
    mIrRec.resume();
  }

private:
  static IRTransceiver *mInstance;
  static IRsend mIrSend;
  static IRrecv mIrRec;
  static volatile bool mIRDataJustReceived;
};

IRTransceiver *IRTransceiver::mInstance = nullptr;
IRsend IRTransceiver::mIrSend;
IRrecv IRTransceiver::mIrRec;
volatile bool IRTransceiver::mIRDataJustReceived = false;