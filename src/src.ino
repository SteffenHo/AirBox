#include <ArduinoJson.h>

#include <WiFi.h>
#include "Configuration.h"
#include "HttpResponse.h"
#include "http_helper.h"
#include "HttpRouter.h"

#include "avem.h"
#include "device.h"
#include <RCSwitch.h>
#include "helper.h"
#include "SDCardHelper.h"

RCSwitch receiver = RCSwitch();
bool receiverIsActive = false;
bool sendIsActive =  false;
bool isProcessingTask = false;
bool isSdInitialized = false;

char* ssid     = "fh_ge_ahaus";
char* password = "8468841547122342";

WiFiServer server(SERVER_PORT);

char linebuf[1024];
int charcount = 0;
int line_type = 0;
HttpRequest request;
HttpResponse response;
HttpRouter router;

void setup()
{
  delay(100);
    Serial.begin(BAUD_RATE);
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
    HttpRoute optionsHandlerRoute;
    optionsHandlerRoute.setRoute("/");
    optionsHandlerRoute.setMethod("OPTIONS");
    optionsHandlerRoute.setCallback(handle_options_request);
    router.add(optionsHandlerRoute);

    HttpRoute sendConfigRoute;
    sendConfigRoute.setRoute("/devices/configs/:id/send");
    sendConfigRoute.setMethod("POST");
    sendConfigRoute.setCallback(send_config);
    router.add(sendConfigRoute);

    HttpRoute deviceConfigIdRoute;
    deviceConfigIdRoute.setRoute("/devices/configs/:id");
    deviceConfigIdRoute.setMethod("GET");
    deviceConfigIdRoute.setCallback(get_configs_id);
    router.add(deviceConfigIdRoute);

    HttpRoute deviceConfigRoute;
    deviceConfigRoute.setRoute("/devices/configs");
    deviceConfigRoute.setMethod("GET");
    deviceConfigRoute.setCallback(get_configs);
    router.add(deviceConfigRoute);

    HttpRoute saveConfigRoute;
    saveConfigRoute.setRoute("/devices/configs");
    saveConfigRoute.setMethod("POST");
    saveConfigRoute.setCallback(save_config);
    router.add(saveConfigRoute);

    HttpRoute mainBundleRoute;
    mainBundleRoute.setRoute("/main/bundle");
    mainBundleRoute.setMethod("GET");
    mainBundleRoute.setCallback(get_main_bundle);
    router.add(mainBundleRoute);

    HttpRoute saveDevicesRoute;
    saveDevicesRoute.setRoute("/devices");
    saveDevicesRoute.setMethod("POST");
    saveDevicesRoute.setCallback(save_devices);
    router.add(saveDevicesRoute);

    HttpRoute devicesRoute;
    devicesRoute.setRoute("/devices");
    devicesRoute.setMethod("GET");
    devicesRoute.setCallback(get_devices);
    router.add(devicesRoute);

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

void get_main_bundle(HttpRequest &request, HttpResponse &response) {
  char text[4096] = "Test";
  strcpy(response.body, text);
  response.statusCode = 200;
    response.end();
}

void handle_options_request(HttpRequest &request, HttpResponse &response) {
  response.statusCode = 200;
  response.end();
}

void get_configs(HttpRequest &request, HttpResponse &response) {
  if(!isSdInitialized) {
    response.statusCode = 503;
    response.end();
    return;
  }
  
  if(!readFileToString(response.body, DB_FILE_NAME )) {
    response.body[0] = 0;
    response.statusCode = 500;
    response.end();
    return;
  }

  response.statusCode = 200;
  response.end();
}

void get_configs_id(HttpRequest &request, HttpResponse &response) {
  
  int id = atoi(request.params.get(0));
  if(id <= 0) {
    response.statusCode = 400;
    response.end();
    
    return;
  }
  
  Avem av = readFile(id);
  if(av.isEmpty()) {
    response.statusCode = 404;
    response.end();
    
    return;
  }
  
  av.toJson(response.body, MAX_BODY_SIZE);
  response.statusCode = 200;
  response.end();
}

void save_config(HttpRequest &request, HttpResponse &response) {
  receiverIsActive = true;
  sendIsActive = false;
  
  response.statusCode = 200;
}

void send_config(HttpRequest &request, HttpResponse &response) {
  receiverIsActive = false;
  sendIsActive = true;

  int id = atoi(request.params.get(0));
  if(id <= 0) {
    response.statusCode = 400;
    response.end();
    
    return;
  }
  
  Avem av = readFile(id);
  if(av.isEmpty()) {
    response.statusCode = 404;
    response.end();
    
    return;
  }

  sendAvem(av);

  receiverIsActive = false;
  sendIsActive = false;
  

  response.statusCode = 200;
  response.end();
}


void save_devices(HttpRequest &request, HttpResponse &response) {
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& requestBody = jsonBuffer.parseObject(request.body.getRaw(), MAX_BODY_SIZE);
  mainDeviceId++;
  Device d( mainDeviceId, requestBody["name"]);
  createDeviceString(d);
  response.statusCode = 200;
  response.end();
}

void get_devices(HttpRequest &request, HttpResponse &response) {
  if(!isSdInitialized) {
    response.statusCode = 503;
    response.end();
    return;
  }
  
  if(!readFileToString(response.body, DEVICE_DB_FILE_NAME )) {
    response.body[0] = 0;
    response.statusCode = 500;
    response.end();
    return;
  }

  response.statusCode = 200;
  response.end();
}

void client_loop(HttpRequest &request, HttpResponse &response) {
#ifdef __DEV__
  serialEvent();
#endif
  
  if (receiver.available()) {
    if(receiverIsActive && !isProcessingTask) {
      isProcessingTask = true;
      
      if(mainId > 0) {
        mainId++;
        
        StaticJsonBuffer<200> jsonBuffer;
        JsonObject& requestBody = jsonBuffer.parseObject(request.body.getRaw(), MAX_BODY_SIZE);
        
        Avem a(mainId,
          requestBody["name"],
          requestBody["deviceId"],
          receiver.getReceivedValue(),
          receiver.getReceivedBitlength(),
          receiver.getReceivedDelay(),
          receiver.getReceivedProtocol()
        );
        
        createAvemString(a);
        
        response.end();
      } else {
#ifdef __DEV__
        Serial.println("error Id to small");
#endif
      }
     
      isProcessingTask = false;
      receiverIsActive = false;
    }
    receiver.resetAvailable();
  }
}

void loop()
{
  // listen for incoming clients
  http_helper_loop(request, response, client_loop);
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
        //isProcessingTask = readFile(2); //an
      }
      else if(ch == 98)//b 
      { 
       //isProcessingTask = readFile(3); //aus
      }
      isProcessingTask = false;
    }
  }
}
#endif
