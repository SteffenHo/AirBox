#include <ArduinoJson.h>

#include <WiFi.h>
#include "Configuration.h"
#include "HttpResponse.h"
#include "http_helper.h"
#include "HttpRouter.h"

#include "avem.h"
#include <RCSwitch.h>
#include "helper.h"
#include "SDCardHelper.h"
#define RECEIVER_PIN 2

RCSwitch receiver = RCSwitch();
bool receiverIsActive = false;
bool sendIsActive =  false;
bool isProcessingTask = false;
bool isSdInitialized = false;

 char* ssid     = "fh_ge_ahaus";
 char* password = "8468841547122342";

WiFiServer server(80);

char linebuf[1024];
int charcount = 0;
int line_type = 0;
HttpRequest request;
HttpResponse response;
HttpRouter router;

const int led1 =  16;      // the number of the LED pin
const int led2 =  17;      // the number of the LED pin

void setup()
{
  delay(100);
    Serial.begin(115200);
    delay(100);

    // We start by connecting to a WiFi network

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);
    
#if BOARD == BOARD_ESP_32
    tcpip_adapter_set_hostname(TCPIP_ADAPTER_IF_STA, "airbox");
    WiFi.setHostname("airbox");
#endif

    HttpRoute deviceConfigRoute;
    deviceConfigRoute.setRoute("/devices/configs");
    deviceConfigRoute.setMethod("GET");
    deviceConfigRoute.setCallback(get_configs);
    router.add(deviceConfigRoute);

    HttpRoute sendConfigRoute;
    sendConfigRoute.setRoute("/devices/configs/:id/send");
    sendConfigRoute.setMethod("POST");
    sendConfigRoute.setCallback(send_config);
    router.add(sendConfigRoute);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    receiver.enableReceive(RECEIVER_PIN);
    if(initSD()) {
      isSdInitialized = true;
      // ESP.restart();
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    
    server.begin();
    Serial.println("Web server started");
}

void get_configs(HttpRequest &request, HttpResponse &response) {
  StaticJsonBuffer<200> jsonBuffer;
  
  JsonObject& root = jsonBuffer.createObject();
  root["sensor"] = "gps";
  root["time"] = 1351824120;
  
  JsonArray& data = root.createNestedArray("data");
  data.add(48.756080);
  data.add(2.302038);
  
  root.printTo(response.body);

  response.statusCode = 200;
  response.end();
}

void send_config(HttpRequest &request, HttpResponse &response) {
  request.params.print();

  StaticJsonBuffer<200> jsonBuffer;
  
  JsonObject& root = jsonBuffer.createObject();
  root["sensor"] = "gps_var_moin";
  root["time"] = 1351824120;
  
  JsonArray& data = root.createNestedArray("data");
  data.add(48.756080);
  data.add(2.302038);
  
  root.printTo(response.body);

  response.statusCode = 200;
  response.end();
}

void loop()
{
  // listen for incoming clients
  http_helper_loop();

#ifdef __DEV__
  serialEvent();
#endif
  
  if (receiver.available()) {
    if(receiverIsActive && !isProcessingTask) {
      isProcessingTask = true;
      
      if(mainId > 0) {
        mainId++;
        
        Avem a(mainId, "test", 2,
          receiver.getReceivedValue(),
          receiver.getReceivedBitlength(),
          receiver.getReceivedDelay(),
          receiver.getReceivedProtocol()
        );
        
        createAvemString(a);
      } else {
#ifdef __DEV__
        Serial.println("error Id to small");
#endif
      }
     
      isProcessingTask = false;
    }
    receiver.resetAvailable();
  }
}

#ifdef __DEV__
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
    
    if(sendIsActive && !isProcessingTask) {
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
#endif
