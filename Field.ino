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
  void send(uint16_t address, uint16_t data)
  {
    uint32_t rawSenddata = 0;
    rawSenddata = address | (data << 16); // this is alittle out of my wheel house may have bitshifted wrong.
    mIrSend.sendNEC(rawSenddata, 32);
  }

  void handleRx()
  {
    decode_results results;
    if (mIrRec.decode(&results))
    { // We have captured something.
      // The capture has stopped at this point.
      uint16_t rxVal = results.value | 0xFF;
      uint16_t rxAddr = results.value | (0xFF << 16);
      Serial.print("IR RX: Addr" + String(rxAddr) + " Val:" + String(rxVal));
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

void loop()
{
  ir.handleRx();

  uint16_t txAddr = 0;
  uint16_t txVal = 0;
  ir.send(txAddr, txVal);
  Serial.print("IR TX: Addr:" + String(txAddr) + "Val:" + String(txVal));
  txVal++;
}
