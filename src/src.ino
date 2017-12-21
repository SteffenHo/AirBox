#include <ArduinoJson.h>

#include <WiFi.h>
#include "Configuration.h"
#include "HttpResponse.h"
#include "http_helper.h"
#include "HttpRouter.h"

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

    HttpRoute route;
    route.setRoute("/test me/hi/test");
    route.setMethod("GET");
    route.setCallback(process_hi);
    router.add(route);

    HttpRoute route3;
    route3.setRoute("/test me/hi/:test/Moin");
    route3.setMethod("GET");
    route3.setCallback(process_hi_var_2);
    router.add(route3);

    HttpRoute route2;
    route2.setRoute("/test me/hi/:test");
    route2.setMethod("POST");
    route2.setCallback(process_hi_var);
    router.add(route2);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    
    server.begin();
    Serial.println("Web server started");
}

void process_hi(HttpRequest &request, HttpResponse &response) {
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

void process_hi_var(HttpRequest &request, HttpResponse &response) {
  request.params.print();

  StaticJsonBuffer<200> jsonBuffer;
  
  JsonObject& root = jsonBuffer.createObject();
  root["sensor"] = "gps_var";
  root["time"] = 1351824120;
  
  JsonArray& data = root.createNestedArray("data");
  data.add(48.756080);
  data.add(2.302038);
  
  root.printTo(response.body);

  response.statusCode = 200;
  response.end();
}

void process_hi_var_2(HttpRequest &request, HttpResponse &response) {
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
  WiFiClient client = server.available();
  if (client) {
    memset(linebuf, 0, sizeof(linebuf));
    
    charcount = 0;
    response.clear();
    http_clear_request(request, line_type);
    
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        linebuf[charcount] = c;
        charcount++;

        int requestEnded = (line_type > 1 && (request.body.getCurrentIndex() + charcount) >= request.body.content_length);
        if(requestEnded) {
          request.bodyReady = true;
          request.ready = true;
        }

        if(c == '\n' || requestEnded) {
          parse_http_request(request, linebuf, line_type);

          if(request.ready) {
            process_request(request, response);
          }
         
          memset(linebuf, 0, sizeof(linebuf));
          charcount=0;
        }
      }

      if(response.isReady()) {
        response.send(client);
        break;
      }
    }
    // give the web browser time to receive the data
    delay(1);

    // close the connection:
    client.stop();
  }
}

void process_request(HttpRequest &request, HttpResponse &response) {
  if(!router.process(request, response)) {
    response.statusCode = 404;
    response.end();
  }

  if(request.ready) {
    Serial.println("---------- REQUEST ----------");
    
    Serial.print("Route: ");
    request.route.print();

    Serial.print("Method-Type: ");
    Serial.println((int) request.method);

    Serial.println("Headers:");
    request.header.print();

    Serial.println("Body:");
    if(request.bodyReady) {
      Serial.println(request.body.getRaw());
    } else {
      Serial.println("-- no body --");
    }
  }
}

