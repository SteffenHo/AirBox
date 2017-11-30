
#include "avem.h"
#include <RCSwitch.h>
#include "helper.h"

RCSwitch receiver = RCSwitch();

void setup() {
  // put your setup code here, to run once:

 Serial.begin(9600);
 receiver.enableReceive(D4);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if (receiver.available()) {
    
    //output(mySwitch.getReceivedValue(), mySwitch.getReceivedBitlength(), mySwitch.getReceivedDelay(), mySwitch.getReceivedRawdata(),mySwitch.getReceivedProtocol());
    AvemConfig av(receiver.getReceivedValue(), receiver.getReceivedBitlength(), receiver.getReceivedDelay(),receiver.getReceivedProtocol());
    Avem a(2, "test", av, 2);
    createAvemString(a);
    receiver.resetAvailable();
  }
}
