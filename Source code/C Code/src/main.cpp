#include "settings.h"


void voltageCalculator()
{
    float voltage;
    voltage = (float)analogRead(Voltage_Calculator_Pin)/4096 * 5;
    if (voltage <= 4.75)
        Serial.println("%0");
    else if (voltage > 4.75 && voltage <= 4.80)
        Serial.println("%10");
    else if (voltage > 4.80 && voltage <= 4.85)
        Serial.println("%20");
    else if (voltage > 4.85 && voltage <= 4.90)
        Serial.println("%40");
    else if (voltage > 4.90 && voltage <= 4.95)
        Serial.println("%60");
    else if (voltage > 4.95 && voltage <= 4.99)
        Serial.println("%80");
    else if (voltage > 4.99)
        Serial.println("%100");
}

void setup()
{
    Serial.begin(115200);
    cameraInit();
    initWiFi();
    // initMQTT();
    client.setBufferSize(1024 * 30);
    client.setServer(MQTT_SERVER.c_str(), 1883);
    client.setCallback(message_received);
}


void loop()
{
    if (!client.connected())
    {
        Serial.println("if girdi");
        reconnect();
    }
    client.loop();

    if (willtakepicture)
        takePhoto();

    voltageCalculator();
}