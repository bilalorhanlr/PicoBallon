#ifndef SETTINGS_H
#define SETTINGS_H

#include <PubSubClient.h>
#include <WiFi.h>
#include "esp_camera.h"
#include <String>
#include <base64.h>

// CAMERA SETTINGS //
#define PWDN_GPIO_NUM 32
#define RESET_GPIO_NUM -1
#define XCLK_GPIO_NUM 0
#define SIOD_GPIO_NUM 26
#define SIOC_GPIO_NUM 27
#define Y9_GPIO_NUM 35
#define Y8_GPIO_NUM 34
#define Y7_GPIO_NUM 39
#define Y6_GPIO_NUM 36
#define Y5_GPIO_NUM 21
#define Y4_GPIO_NUM 19
#define Y3_GPIO_NUM 18
#define Y2_GPIO_NUM 5
#define VSYNC_GPIO_NUM 25
#define HREF_GPIO_NUM 23
#define PCLK_GPIO_NUM 22

// WIFI SETTINGS //
const char ssid[] = "Bilo";
const char pass[] = "123456789";

// MQTT SETTINGS //
const int bufferSize = 23 * 1024;

String DEVICE_NAME = "123123";
String CONST_TOPIC = "qq1122/";
String CAMERA_TOPIC_get = CONST_TOPIC + DEVICE_NAME + String("/cam_get");
String CAMERA_TOPIC = CONST_TOPIC + DEVICE_NAME + String("/cam");
String SENSOR_TOPIC = CONST_TOPIC + DEVICE_NAME + String("/sensor");

String MQTT_SERVER = "test.mosquitto.org";

WiFiClient net;
PubSubClient client(net);



bool willtakepicture = false;
void initWiFi()
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, pass);
    Serial.print("Connecting to WiFi ..");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print('.');
        delay(1000);
    }
    Serial.println(WiFi.localIP());
}

void message_received(char *topic, byte *message, unsigned int length)
{
    Serial.print("Message arrived on topic: ");
    Serial.print(topic);
    Serial.print(". Message: ");
    String messageTemp;

    for (int i = 0; i < length; i++)
    {
        Serial.print((char)message[i]);
        messageTemp += (char)message[i];
    }
    Serial.println();
    if (strcmp(messageTemp.c_str(), "takepicture") == 0)
        willtakepicture = true;
}

void reconnect()
{
    // Loop until we're reconnected
    while (!client.connected())
    {
        Serial.print("Attempting MQTT connection...");
        // Attempt to connect
        if (client.connect(DEVICE_NAME.c_str()))
        {
            Serial.println("connected");
            // Subscribe
            client.subscribe(CAMERA_TOPIC_get.c_str());
            Serial.println("Subscribed to " + CAMERA_TOPIC_get);
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            // Wait 5 seconds before retrying
            delay(5000);
        }
    }
}

void cameraInit()
{
    camera_config_t config;
    config.ledc_channel = LEDC_CHANNEL_0;
    config.ledc_timer = LEDC_TIMER_0;
    config.pin_d0 = Y2_GPIO_NUM;
    config.pin_d1 = Y3_GPIO_NUM;
    config.pin_d2 = Y4_GPIO_NUM;
    config.pin_d3 = Y5_GPIO_NUM;
    config.pin_d4 = Y6_GPIO_NUM;
    config.pin_d5 = Y7_GPIO_NUM;
    config.pin_d6 = Y8_GPIO_NUM;
    config.pin_d7 = Y9_GPIO_NUM;
    config.pin_xclk = XCLK_GPIO_NUM;
    config.pin_pclk = PCLK_GPIO_NUM;
    config.pin_vsync = VSYNC_GPIO_NUM;
    config.pin_href = HREF_GPIO_NUM;
    config.pin_sscb_sda = SIOD_GPIO_NUM;
    config.pin_sscb_scl = SIOC_GPIO_NUM;
    config.pin_pwdn = PWDN_GPIO_NUM;
    config.pin_reset = RESET_GPIO_NUM;
    config.xclk_freq_hz = 20000000;
    config.pixel_format = PIXFORMAT_JPEG;
    config.frame_size = FRAMESIZE_VGA; // 640x480
    config.jpeg_quality = 10;
    config.fb_count = 2;

    // camera init
    esp_err_t err = esp_camera_init(&config);
    if (err != ESP_OK)
    {
        Serial.printf("Camera init failed with error 0x%x", err);
        ESP.restart();
        return;
    }
}

void takePhoto()
{
    camera_fb_t *fb = esp_camera_fb_get();
    if (fb != NULL && fb->format == PIXFORMAT_JPEG && fb->len < bufferSize)
    {
        String encoded = base64::encode(fb->buf, fb->len);
        Serial.print("Image Length: ");
        Serial.print(fb->len);
        Serial.print("\t Publish Image: ");
        bool result = client.publish(CAMERA_TOPIC.c_str(), encoded.c_str(), fb->len);
        Serial.println(result);
        if (!result)
            ESP.restart();
        willtakepicture = false;
    }
    esp_camera_fb_return(fb);
    delay(1);
}


#endif