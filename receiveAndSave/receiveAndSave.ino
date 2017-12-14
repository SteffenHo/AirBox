
#include "avem.h"
#include <RCSwitch.h>
#include "helper.h"
#include "SDCardHelper.h"
#define RECEIVER_PIN 2

RCSwitch receiver = RCSwitch();
//RCSwitch sender = RCSwitch();
bool receiverIsActive = false;
bool sendIsActive =  false;
bool isProcessingTask = false;
void setup() {
  // put your setup code here, to run once:
 delay(100);
 Serial.begin(115200);
 delay(100);
 receiver.enableReceive(RECEIVER_PIN);
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
        //AvemConfig av(receiver.getReceivedValue(), receiver.getReceivedBitlength(), receiver.getReceivedDelay(),receiver.getReceivedProtocol());
        Avem a(mainId, "test",  2, receiver.getReceivedValue(), receiver.getReceivedBitlength(), receiver.getReceivedDelay(),receiver.getReceivedProtocol());
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

void serialEvent() {
  if(Serial.available()) {
    char ch = Serial.read();
    Serial.println(ch);
    if(!isProcessingTask){
      if(ch == 115) //s
      {
        receiverIsActive = true;
        sendIsActive = false;
      }
      else if(ch == 116) //t
      {
        receiverIsActive = false;
      }
      else if(ch == 109) //m
      {
        sendIsActive = true;
        receiverIsActive = false;
      }
      else if(ch == 111) // o
      {
        sendIsActive = false;
      }
     
    }
    
    if(sendIsActive && !isProcessingTask){
      isProcessingTask = true;
      if(ch == 97) //a
      { 
        isProcessingTask = !readFile(2); //an
      }
      else if(ch == 98)//b 
      { 
       isProcessingTask = !readFile(3); //aus
      }
      isProcessingTask = false;
    }
      
  }
}


