#include <Arduino.h>
#include <IRremote.h>
#include <string.h>

#define IR_LED 4
#define IR_DETECT 13

class IRTransciever
{
public:
  IRTransciever(int aTxPin, int aRxPin)
  {
    mIrSend.begin(aTxPin);
    mIrRec.begin(aRxPin);
  }

  // Kinda guessing at the emplementation of this function.
  // may need to play with how we do this.
  void send(uint16_t address, uint8_t data)
  {
    // Send address and data no repeats
    mIrSend.sendNEC(address, data, 0);
  }

  void handleRx()
  {
    if (mIrRec.decode())
    { // We have captured something.
      // The capture has stopped at this point.
      Serial.print("IR RX: Addr" + String(mIrRec.decodedIRData.address) + " Val:" + String(mIrRec.decodedIRData.command));
    }
  }

private:
  IRsend mIrSend;
  IRrecv mIrRec;
};

IRTransciever ir(IR_LED, IR_DETECT);

void setup()
{
  Serial.begin(9600);
}

uint16_t txAddr = 0;
uint16_t txVal = 0;
void loop()
{
  ir.handleRx();
  ir.send(txAddr, txVal);
  Serial.print("IR TX: Addr:" + String(txAddr) + "Val:" + String(txVal));
  txVal++;
}
