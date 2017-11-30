#ifndef _AVEM_H
#define _AVEM_H
#include "avemConfig.h"
#define JSON_ARRAY_SIZE 200

class Avem{
  private:
    int id;
    char name[20];
    AvemConfig config;
    int device_id;

  public:
    Avem(int p_id, const char* p_name,const AvemConfig &p_config, int p_device_id){
      id=p_id;
      device_id = p_device_id;
      int length = 0;
      const char* add = p_name;
      for(; add[length]; length++);
      
      //this->name = (char*)malloc((length+1)*sizeof(char));
      int i = 0;
      for(; i< length || i<19; i++){
        name[i] = p_name[i];
      }
      this->name[i++] = 0;
      config = p_config;
    }

   /*Avem(const Avem &av){
    Serial.println("Copy constructor allocating  Avem");
    id = av.id;
    device_id = av.device_id;
    int length = 0;
      char* add = av.name;
      for(; add[length]; length++);
      
      this->name = (char*)malloc((length+1)*sizeof(char));
      int i = 0;
      for(; i< length; i++){
        this->name[i] = av.name[i];
      }
      this->name[i++] = 0;
      config = av.config;
    
   }*/
    int getId() const {return id;}

    void print(){
      Serial.print("Id: ");
      Serial.print(id);
      Serial.print("\nName: ");
      Serial.print(this->name);
      Serial.print("\nConfig: ");
      this->config.print();
      Serial.print("\nDeviceId: ");
      Serial.print(device_id);
    }

    char* toJson() const{
      const size_t bufferSize = JSON_OBJECT_SIZE(8);
      DynamicJsonBuffer jsonBuffer(bufferSize);

      JsonObject& root = jsonBuffer.createObject();
      root["id"]= id;
      root["name"] = name;
      root["deviceId"] = device_id;
      JsonObject& t = config.toJson(root);
   
      char jsonChar[JSON_ARRAY_SIZE];
      t.printTo(jsonChar, sizeof(char)*JSON_ARRAY_SIZE);
    
      return jsonChar;
    }

};
#endif


