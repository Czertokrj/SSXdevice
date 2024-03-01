#include "SSXdevice.h"

SSXdevice::SSXdevice(const char* ssid, const char* password) {
  _ssid = ssid;
  _password = password;
}

void SSXdevice::setupWiFi() {
  WiFi.begin(_ssid, _password);
  Serial.print("Conectando ao WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Conectado ao WiFi");
}

bool SSXdevice::sendJsonData(const String& jsonData) {
  if(WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin("http://device.systemsatx.com.br/v1/GenericPosition/Set");
    http.addHeader("Content-Type", "application/json");
    int httpCode = http.POST(jsonData);
    if (httpCode > 0) {
      String payload = http.getString();
      Serial.println(httpCode);
      Serial.println(payload);
      http.end();
      return true;
    } else {
      Serial.println("Erro na requisição HTTP");
      http.end();
      return false;
    }
  } else {
    Serial.println("Desconectado do WiFi");
    return false;
  }
}

String SSXdevice::getCurrentTime() {
  configTime(0, 0, "pool.ntp.org", "time.nist.gov");
  time_t now = time(nullptr);
  while (now < 57600) {
    delay(500);
    Serial.print(".");
    now = time(nullptr);
  }
  return String(now);
}

bool SSXdevice::sendDeviceData(const char* hashCentral, const char* equipamento, int codEvento, double latitude, double longitude, int entradas, int saidas, TelemetriaData telemetria[], int telemetriaCount, int idMotorista) {
  StaticJsonDocument<1024> doc;
  JsonArray data = doc.to<JsonArray>();

  JsonObject data_0 = data.createNestedObject();
  data_0["hashCentral"] = hashCentral;
  data_0["equipamento"] = equipamento;
  data_0["idComunicacao"] = nullptr;
  data_0["dataEvento"] = getCurrentTime();
  data_0["codEvento"] = codEvento;
  data_0["latitude"] = latitude;
  data_0["longitude"] = longitude;
  data_0["entradas"] = entradas;
  data_0["saidas"] = saidas;

  JsonArray telemetriaNum = data_0.createNestedArray("telemetriaNum");
  for (int i = 0; i < telemetriaCount; i++) {
    JsonObject telemetriaObj = telemetriaNum.createNestedObject();
    telemetriaObj["id"] = telemetria[i].id;
    telemetriaObj["valor"] = telemetria[i].valor;
  }

  data_0["idMotorista"] = idMotorista;

  String jsonData;
  serializeJson(doc, jsonData);

  return sendJsonData(jsonData);
}
