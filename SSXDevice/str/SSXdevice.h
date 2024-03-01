#ifndef SSXdevice_h
#define SSXdevice_h

#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

struct TelemetriaData {
  int id;
  int valor;
};

class SSXdevice {
  public:
    SSXdevice(const char* ssid, const char* password);
    void setupWiFi();
    bool sendJsonData(const String& jsonData);
    String getCurrentTime();
    bool sendDeviceData(const char* hashCentral, const char* equipamento, int codEvento, double latitude, double longitude, int entradas, int saidas, TelemetriaData telemetria[], int telemetriaCount, int idMotorista);

  private:
    const char* _ssid;
    const char* _password;
};

#endif
