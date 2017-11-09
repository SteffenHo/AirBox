

#include "avem.h"
#include <RCSwitch.h>
#include "eepromHelper.h"



//var
bool receiver_is_active = false;
RCSwitch receiver = RCSwitch();
int addr = 10;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  receiver.enableReceive(0);
  //readAvem();
}

void loop() {
  // put your main code here, to run repeatedly:
  if(receiver_is_active){
    if (receiver.available()) {
      //output(receiver.getReceivedValue(), receiver.getReceivedBitlength(), receiver.getReceivedDelay(), receiver.getReceivedRawdata(),receiver.getReceivedProtocol());
      AvemConfig av(receiver.getReceivedValue(), receiver.getReceivedBitlength(), receiver.getReceivedDelay(),receiver.getReceivedProtocol());
      Avem a(1, "test", av, 2);
      a.print();
      String str = a.toJson();
      Serial.print(str);
      EEPROM_writeAnything(addr,str);
      
      receiver.resetAvailable();
      receiver_is_active = 0;
    }
  }
}

void saveAvem(Avem avem){
  addr += EEPROM_writeAnything(addr, avem);
  if (addr == EEPROM.length()) {
    Serial.print("EEPROM ERROR");
    addr = 0;
  }

}

void readAvem(){
  String str;
  EEPROM_readAnything(0, str);
  Serial.print("\n");
  Serial.print(str);
}

void serialEvent() {
  char ch = Serial.read();
  if(ch==97){
    
    readAvem();
  }
  if (ch == 101) {
    if(receiver_is_active){
      //activate only once
      Serial.print("Receiver is already activated");
    }
    else{
    receiver_is_active = true;
      if (receiver.available()) {
        receiver.resetAvailable();
      }
    }
  }
  else{
    receiver_is_active = false;
  }
}

