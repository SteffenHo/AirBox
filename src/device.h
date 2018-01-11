#ifndef _DEVICE_H
#define _DEVICE_H

class Device {
  public:
    int id;
    char name[DEVICE_NAME_LENGTH];

    Device(int pId, const char* pName){
      id = pId;
      strcpy(name, pName);
    }
    int getId() const {return id;}
     void toJson(char* buffer, int pLength) const{
      StaticJsonBuffer<200> jsonBuffer;

      JsonObject& root = jsonBuffer.createObject();
      root["id"]= id;
      root["name"] = name;
      root.printTo(buffer, pLength);
    }
    void print(){
      Serial.print("id:");
      Serial.print(id);
      Serial.print("\nname:");
      Serial.print(name);
      Serial.print("\n");
    }

};

#endif

