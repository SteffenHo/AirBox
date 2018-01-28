#ifndef _CONFIGURATION_H
#define _CONFIGURATION_H

// general
#define __DEV__
#define BAUD_RATE 115200
#define SERVER_PORT 80

// Pinout
#define SD_PIN 22
#define SEND_PIN 27
#define RECEIVER_PIN 2

// Board
#define BOARD_ESP_8266 1
#define BOARD_ESP_32 2
#define BOARD BOARD_ESP_32

// server settings
#define MAX_CLIENTS 4

#define MAX_BODY_SIZE 2024

#define MAX_HEADER_ENTRIES 10
#define MAX_HEADER_KEY_LENGTH 64
#define MAX_HEADER_VALUE_LENGTH 512

// Response
#define RESPONSE_DEFAULT_STATUS_CODE 500
#define MAX_RESPONSE_BODY_SIZE 4096
#define CORS_ALLOWED_ORIGINS "*"
#define CORS_ALLOWED_METHODS "GET,POST,OPTIONS"
#define CORS_ALLOWED_HEADERS "Cache-Control"

// Routing
#define HTTP_ROUTER_MAX_ROUTES 10
#define HTTP_ROUTER_ROUTE_BUFFER 256

#define HTTP_ROUTE_MAX_PARTS 5
#define HTTP_ROUTE_MAX_PART_SIZE 65

// HTTP-methods
#define HTTP_METHOD_UNKNOWN 0
#define HTTP_METHOD_GET 1
#define HTTP_METHOD_POST 2
#define HTTP_METHOD_DELETE 3
#define HTTP_METHOD_PUT 4
#define HTTP_METHOD_PATCH 5
#define HTTP_METHOD_OPTIONS 6

// SD-card settings
#define SEPARATOR '|'
#define AVEM_STR_SIZE 300
#define ID_STR_SIZE 10
#define DB_FILE_NAME "/AVEM07.TXT"

// avem
#define AVEM_NAME_LENGTH 256
#define AVEM_SERIALIZE_BUFFER_SIZE 2048

//device
#define DEVICE_NAME_LENGTH 256
#define DEVICE_DB_FILE_NAME "/DEVICE.TXT"

#endif
