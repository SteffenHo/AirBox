#ifndef _SD_CARD_HELPER_H
#define _SD_CARD_HELPER_H
#define SEPARATOR '|'
#define AVEM_STR_SIZE 300
#define ID_STR_SIZE 10
#define DB_FILE_NAME "AVEM30.TXT"

#include <SPI.h>
#include <SD.h>
#include <RCSwitch.h>

RCSwitch sender = RCSwitch();
//#include "helper.h"
File DB;
