#include <SSXdevice.h>

const char* ssid = "Czr Ap10";
const char* password = "aq1sw2de3";

SSXdevice(ssid, password);

void setup() {
  Serial.begin(115200);
  SSXdevice.setupWiFi();
}

void loop() {
    const char* hashCentral = "DSV";
    const char* equipamento = "280224";
    int codEvento = 1;
    double latitude = -22.5587487;
    double longitude = -42.5587487;
    int entradas = 1;
    int saidas = 0;
    TelemetriaData telemetria[] = {{17, 60}, {9, 30}, {15, 1500}};
    int idMotorista = 1212;

    if(SSXdevice.sendDeviceData(hashCentral, equipamento, codEvento, latitude, longitude, entradas, saidas, telemetria, 3, idMotorista)) {
        Serial.println("Dados enviados com sucesso!");
    } else {
        Serial.println("Falha ao enviar dados.");
    }
    delay(10000);
}
