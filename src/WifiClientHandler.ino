#include "WifiClientHandler.h"

WifiClientHandler::WifiClientHandler() {
  this->client = NULL;
}

WifiClientHandler::WifiClientHandler(const WiFiClient & wifiClient) {
  this->client = new WiFiClient(wifiClient);
}

WiFiClient* WifiClientHandler::getClient() {
  return this->client;
}

bool WifiClientHandler::shouldConnectionClose() {
  return this->closeConnection;
}

