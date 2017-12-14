#include <WiFi.h>
#include "esp_wifi.h"
#include "esp_wps.h"
#include "nvs_flash.h"
#include "esp_event_loop.h"

#define ESP_WPS_MODE WPS_TYPE_PBC
esp_wps_config_t config = WPS_CONFIG_INIT_DEFAULT(WPS_TYPE_PBC);

void wifi_helper_init() {
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK( ret );

    start_wps();
  
  WiFi.onEvent(WiFiEvent);
  /*WiFi.mode(WIFI_MODE_STA);

  Serial.println("Starting WPS");

  esp_wifi_wps_enable(&config);
  esp_wifi_wps_start(0);*/
}

void start_wps() {
  tcpip_adapter_init();
    esp_event_loop_init(event_handler, NULL);

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&cfg);

esp_wifi_set_auto_connect(true);

        Serial.println(WiFi.SSID());
        Serial.println(WiFi.psk());

WiFi.begin(WiFi.SSID().c_str(), WiFi.psk().c_str());
    
    esp_wifi_set_mode(WIFI_MODE_STA);
    esp_wifi_start();
    
    Serial.println("start wps...");
    
       
    esp_wifi_wps_enable(&config);
    esp_wifi_wps_start(0);
}

String wpspin2string(uint8_t a[]){
  char wps_pin[9];
  for(int i=0;i<8;i++){
    wps_pin[i] = a[i];
  }
  wps_pin[8] = '\0';
  return (String)wps_pin;
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
    
        WiFi.printDiag(Serial);
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
    case SYSTEM_EVENT_STA_WPS_ER_PIN:
    Serial.println("WPS_PIN = " + wpspin2string(info.sta_er_pin.pin_code));
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

static esp_err_t event_handler(void *ctx, system_event_t *event)
{
    switch(event->event_id) {
    case SYSTEM_EVENT_STA_START:
        Serial.println("SYSTEM_EVENT_STA_START");
        break;
    case SYSTEM_EVENT_STA_GOT_IP:
        Serial.println("SYSTEM_EVENT_STA_GOT_IP");
        Serial.print("got ip: ");
        Serial.println(ip4addr_ntoa(&event->event_info.got_ip.ip_info.ip));
        break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
        Serial.println("SYSTEM_EVENT_STA_DISCONNECTED");
        esp_wifi_connect();
        break;
    case SYSTEM_EVENT_STA_WPS_ER_SUCCESS:
  /*point: the function esp_wifi_wps_start() only get ssid & password
   * so call the function esp_wifi_connect() here
   * */
        Serial.println("SYSTEM_EVENT_STA_WPS_ER_SUCCESS");
        Serial.println(WiFi.SSID());
        Serial.println(WiFi.psk());
        esp_wifi_wps_disable();
        esp_wifi_connect();
  break;
    case SYSTEM_EVENT_STA_WPS_ER_FAILED:
      Serial.println("SYSTEM_EVENT_STA_WPS_ER_FAILED");
      esp_wifi_wps_disable();
      esp_wifi_wps_enable(&config);
      esp_wifi_wps_start(0);
  break;
    case SYSTEM_EVENT_STA_WPS_ER_TIMEOUT:
      Serial.println("SYSTEM_EVENT_STA_WPS_ER_TIMEOUT");
      esp_wifi_wps_disable();
      esp_wifi_wps_enable(&config);
      esp_wifi_wps_start(0);
  break;
    case SYSTEM_EVENT_STA_WPS_ER_PIN:
      Serial.println("SYSTEM_EVENT_STA_WPS_ER_PIN");
  /*show the PIN code here*/
      Serial.print("WPS_PIN");
      Serial.println(wpspin2string(event->event_info.sta_er_pin.pin_code));
  break;
    default:
        break;
    }
    return ESP_OK;
}

