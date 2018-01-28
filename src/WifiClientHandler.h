#ifndef _WIFI_CLIENT_HANDLER_H
#define _WIFI_CLIENT_HANDLER_H

class WifiClientHandler {
  private:
    WiFiClient* client;
    bool closeConnection = false;

  public:
    char linebuf[1024];
    int charcount = 0;
    int lineType = 0;

    HttpRequest request;
    HttpResponse response;

  public:
    WifiClientHandler();
  
    WifiClientHandler(const WiFiClient & wifiClient);

    WiFiClient* getClient();

    bool shouldConnectionClose();
};

#endif
