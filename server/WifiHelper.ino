#include <WiFi.h>
#include "esp_wps.h"

#define ESP_WPS_MODE WPS_TYPE_PBC
esp_wps_config_t config = WPS_CONFIG_INIT_DEFAULT(ESP_WPS_MODE);

void wifi_helper_init() {
  WiFi.onEvent(WiFiEvent);
  WiFi.mode(WIFI_MODE_STA);

  Serial.println("Starting WPS");

  esp_wifi_wps_enable(&config);
  esp_wifi_wps_start(0);
}

void WiFiEvent(WiFiEvent_t event, system_event_info_t info){
  switch(event){
    case SYSTEM_EVENT_STA_START:
    Serial.println("Station Mode Started");
    break;
    case SYSTEM_EVENT_STA_GOT_IP:
    Serial.println("Connected to :" + String(WiFi.SSID()));
    Serial.print("Got IP: ");
    Serial.println(WiFi.localIP());
    break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
    Serial.println("Disconnected from station, attempting reconnection");
    WiFi.reconnect();
    break;
    case SYSTEM_EVENT_STA_WPS_ER_SUCCESS:
    Serial.println("WPS Successfull, stopping WPS and connecting to: " + String(WiFi.SSID()));
    esp_wifi_wps_disable();
    delay(10);
    WiFi.begin();
    break;
    case SYSTEM_EVENT_STA_WPS_ER_FAILED:
    Serial.println("WPS Failed, retrying");
    esp_wifi_wps_disable();
    esp_wifi_wps_enable(&config);
    esp_wifi_wps_start(0);
    break;
    case SYSTEM_EVENT_STA_WPS_ER_TIMEOUT:
    Serial.println("WPS Timedout, retrying");
    esp_wifi_wps_disable();
    esp_wifi_wps_enable(&config);
    esp_wifi_wps_start(0);
    break;
    default:
    break;
  }
}

