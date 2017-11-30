
#include "avem.h"
#include <RCSwitch.h>
#include "helper.h"
#include "SDCardHelper.h"

RCSwitch receiver = RCSwitch();
//RCSwitch sender = RCSwitch();
bool receiverIsActive = false;
bool sendIsActive =  false;
bool isProcessingTask = false;
void setup() {
  // put your setup code here, to run once:

 Serial.begin(9600);
 delay(20);
 receiver.enableReceive(D4);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  initSD();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println("z");
  serialEvent();
  
  
  if (receiver.available()) {
    if(receiverIsActive && !isProcessingTask){
      isProcessingTask = true;
      //output(mySwitch.getReceivedValue(), mySwitch.getReceivedBitlength(), mySwitch.getReceivedDelay(), mySwitch.getReceivedRawdata(),mySwitch.getReceivedProtocol());
      if(mainId >0){
        mainId++;
        AvemConfig av(receiver.getReceivedValue(), receiver.getReceivedBitlength(), receiver.getReceivedDelay(),receiver.getReceivedProtocol());
        Avem a(mainId, "test", av, 2);
         createAvemString(a);
      }
      else{
        Serial.println("error Id to small");
      }
     
      isProcessingTask = false;
    }
    receiver.resetAvailable();
  }
}
