#ifndef _AVEM_H
#define _AVEM_H

#include "avemConfig.h"

class Avem{
  public:
    AvemConfig config;
  private:
    int id;
    char name[AVEM_NAME_LENGTH];
    int device_id;

  public:
    Avem(int p_id, const char* p_name, int p_device_id){
      id=p_id;
      device_id = p_device_id;
      int length = strlen(p_name);
      
      int i = 0;
      for(; i< length || i<19; i++){
        name[i] = p_name[i];
      }
      this->name[i++] = 0;
    }
  
    Avem(int p_id, const char* p_name, const AvemConfig &p_config, int p_device_id) : Avem(p_id, p_name, p_device_id) {
      config = p_config;
    }
    
    Avem(int p_id, const char* p_name,int p_device_id, unsigned long p_decimal, unsigned int p_bit_length, unsigned int p_pulse_length, unsigned int p_protocol)
    : Avem(p_id, p_name, p_device_id) {
      config = AvemConfig(p_decimal, p_bit_length, p_pulse_length, p_protocol);
    }
    
    int getId() const {return id;}
    int getProtocol() const { return config.protocol;};
    int getPulseLength() const { return config.pulse_length;};
    char* getTriState() const { return config.getTriState();};

    void print() const{
#ifdef __DEV__
      Serial.print("Id: ");
      Serial.print(id);
      Serial.print("\nName: ");
      Serial.print(this->name);
      Serial.print("\nConfig: ");
      this->config.print();
      Serial.print("\nDeviceId: ");
      Serial.print(device_id);
#endif
    }

    void toJson(char* buffer, int pLength) const{
      StaticJsonBuffer<200> jsonBuffer;

      JsonObject& root = jsonBuffer.createObject();
      root["id"]= id;
      root["name"] = name;
      root["deviceId"] = device_id;
      JsonObject& t = config.toJson(root);
      
      int length = t.printTo(buffer, pLength);
    }

};

#endif
