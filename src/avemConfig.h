#ifndef _AVEM_CONFIG_H
#define _AVEM_CONFIG_H
#include <ArduinoJson.h>

class AvemConfig {
public:
  unsigned long decimal;
  unsigned int bit_length;
  unsigned int pulse_length;
  unsigned int protocol;
  
public:
  AvemConfig(unsigned long p_decimal, unsigned int p_bit_length, unsigned int p_pulse_length, unsigned int p_protocol){
    decimal=p_decimal;
    bit_length=p_bit_length;
    pulse_length=p_pulse_length;
    protocol=p_protocol;
  }
  
  AvemConfig(){
    decimal=0;
    bit_length=0;
    pulse_length=0;
    protocol=0;
  }
  
  char* bin2tristate(const char* bin) const {
    static char returnValue[50];
    int pos = 0;
    int pos2 = 0;
    while (bin[pos]!='\0' && bin[pos+1]!='\0') {
      if (bin[pos]=='0' && bin[pos+1]=='0') {
        returnValue[pos2] = '0';
      } else if (bin[pos]=='1' && bin[pos+1]=='1') {
        returnValue[pos2] = '1';
      } else if (bin[pos]=='0' && bin[pos+1]=='1') {
        returnValue[pos2] = 'F';
      } else {
        return "not applicable";
      }
      pos = pos+2;
      pos2++;
    }
    returnValue[pos2] = '\0';
    return returnValue;
  }
  
  char* dec2binWzerofill(unsigned long Dec, unsigned int bitLength) const {
      static char bin[64]; 
      unsigned int i=0;
    
      while (Dec > 0) {
        bin[32+i++] = ((Dec & 1) > 0) ? '1' : '0';
        Dec = Dec >> 1;
      }
    
      for (unsigned int j = 0; j< bitLength; j++) {
        if (j >= bitLength - i) {
          bin[j] = bin[ 31 + i - (j - (bitLength - i)) ];
        } else {
          bin[j] = '0';
        }
      }
      bin[bitLength] = '\0';
      
      return bin;
    }
  
  void print() const{
#ifdef __DEV__
    if (decimal == 0) {
      Serial.print("Unknown encoding.");
      Serial.print(decimal);
      Serial.print( bit_length );
      Serial.print(pulse_length);
      Serial.println(protocol);
    } else {
      const char* b = dec2binWzerofill(decimal, bit_length);
      Serial.print(" \nDecimal: ");
      Serial.print(decimal);
      Serial.print(" (");
      Serial.print( bit_length );
      Serial.print("Bit) Binary: ");
      Serial.print( b );
      Serial.print(" \nTri-State: ");
      Serial.print( bin2tristate( b) );
      Serial.print(" \nPulseLength: ");
      Serial.print(pulse_length);
      Serial.print(" microseconds");
      Serial.print(" \nProtocol: ");
      Serial.println(protocol);
    }
#endif
  }
  
  JsonObject& toJson(JsonObject &root) const{
    JsonObject& config = root.createNestedObject("config");
    config["decimal"] = decimal;
    config["bitLength"] = bit_length;
    config["pulseLength"] = pulse_length;
    config["protocol"] = protocol;
    
    return root;
  }
  
  char* getTriState() const {
   const char* b = dec2binWzerofill(decimal, bit_length);
   return bin2tristate( b);
  }
};

#endif
