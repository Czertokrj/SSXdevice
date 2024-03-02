#include <SSXdevice.h>

const char* ssid = "SUA-REDE";
const char* password = "SENHA-DA-SUA-REDE";

SSXdevice myDevice(ssid, password);

void setup() {
  Serial.begin(115200);
  myDevice.setupWiFi();
}

void loop() {
    const char* hashCentral = "DSV";     // hashcode da sua empresa;
    const char* equipamento = "280224"; // crie um código único para seu dispositivo;
    int codEvento = 1; // vide lista de eventos
    double latitude = -22.5587487;
    double longitude = -42.5587487;
    int entradas = 1;   // decimal que representa a máscara em binário. ex. 000001;
    int saidas = 0; // decimal que representa a máscara em binário. ex. 000001;
    TelemetriaData telemetria[] = {{17, 60}, {9, 30}, {15, 1500}}; // vide lista de telemetrias;
    int idMotorista = 1212;

    if(myDevice.sendDeviceData(hashCentral, equipamento, codEvento, latitude, longitude, entradas, saidas, telemetria, 3, idMotorista)) {
        Serial.println("Dados enviados com sucesso!");
    } else {
        Serial.println("Falha ao enviar dados.");
    }
    delay(10000);
}
