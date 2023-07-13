#include <Arduino.h>
#include <IRremote.h>
#include <string.h>

#define IR_LED 5
#define IR_DETECT 6
#define STATUS_LED 7

class IRTransciever
{
public:
  static IRTransciever* getInstance(){
    if(!mInstance){
      return new IRTransciever(IR_LED,IR_DETECT);
    }else {
      return mInstance;
    }
  }
  
  IRTransciever(int aTxPin, int aRxPin)
  {
    mIrSend.begin(aTxPin);
    mIrRec.begin(aRxPin);
    mIrRec.registerReceiveCompleteCallback(&IRTransciever::ReceiveCompleteCallbackHandler);
    mInstance = nullptr;
    mIRDataJustReceived = false;
  }

  // Kinda guessing at the emplementation of this function.
  // may need to play with how we do this.
  static void send(uint16_t address, uint16_t data)
  {
    // Send address and data no repeats
    auto sendData = address | (data << 16);
    mIrSend.sendNECMSB(sendData,32);
    //mIrSend.sendNEC(address, data, 0);
  }

  static void handleRx()
  {
    if (mIRDataJustReceived)
    { 
      mIrRec.printIRResultAsCVariables(&Serial);
      mIRDataJustReceived = false;
      mIrRec.resume();
    }
  }

  static void ReceiveCompleteCallbackHandler() {
    IrReceiver.decode(); // fill IrReceiver.decodedIRData

    if (IrReceiver.decodedIRData.command == 0x10) {
        // do something SHORT here
    } else if (IrReceiver.decodedIRData.command == 0x11) {
        // do something SHORT here too
    }

    mIRDataJustReceived = true;
}

private:
  static IRTransciever* mInstance;
  static IRsend mIrSend;
  static IRrecv mIrRec;
  static volatile bool mIRDataJustReceived;

};

void setup()
{
  Serial.begin(9600);
  pinMode(STATUS_LED, OUTPUT);
  digitalWrite(STATUS_LED, 0);
  IRTransciever::getInstance();
}

uint16_t txAddr = 0;
uint16_t txVal = 0;
void loop()
{
  IRTransciever::getInstance()->handleRx();
  //ir.send(txAddr, txVal);
  //Serial.print("IR TX: Addr:" + String(txAddr) + " Val:" + String(txVal) + "\r\n");
  //txVal++;
  //digitalWrite(STATUS_LED, !digitalRead(STATUS_LED));
}

