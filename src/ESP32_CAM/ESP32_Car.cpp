#include "esp_camera.h"
#include <WiFi.h>

//
// ATENȚIE!!! Asigurați-vă că ați selectat fie modulul ESP32 Wrover,
//            fie altă placă care are PSRAM activat
//
// Adafruit ESP32 Feather

// Selectați modelul camerei
#define CAMERA_MODEL_AI_THINKER

const char *ssid = "DIGI-L9TK";		    // Introduceți numele SSID al rețelei WiFi
const char *password = "a9yKtM9zjE";	// Introduceți parola rețelei WiFi

#if defined(CAMERA_MODEL_WROVER_KIT)
#define PWDN_GPIO_NUM -1
#define RESET_GPIO_NUM -1
#define XCLK_GPIO_NUM 21
#define SIOD_GPIO_NUM 26
#define SIOC_GPIO_NUM 27

#define Y9_GPIO_NUM 35
#define Y8_GPIO_NUM 34
#define Y7_GPIO_NUM 39
#define Y6_GPIO_NUM 36
#define Y5_GPIO_NUM 19
#define Y4_GPIO_NUM 18
#define Y3_GPIO_NUM 5
#define Y2_GPIO_NUM 4
#define VSYNC_GPIO_NUM 25
#define HREF_GPIO_NUM 23
#define PCLK_GPIO_NUM 22

#elif defined(CAMERA_MODEL_AI_THINKER)
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

#else
#error "Modelul camerei nu este selectat"
#endif

// Configurare GPIO
extern int gpLed = 4; // Lumina
extern String WiFiAddr = "";

void startCameraServer();

void setup()
{  
	Serial.begin(115200);
	Serial.setDebugOutput(true);
	Serial.println();

	pinMode(gpLed, OUTPUT); // Lumina
	digitalWrite(gpLed, LOW);

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
	// Inițializare cu specificații ridicate pentru a aloca buffer-e mai mari
	if (psramFound())
	{
		config.frame_size = FRAMESIZE_HD;/*	FRAMESIZE_96X96,    // 96x96
												FRAMESIZE_QQVGA,    // 160x120
												FRAMESIZE_QCIF,     // 176x144
												FRAMESIZE_HQVGA,    // 240x176
												FRAMESIZE_240X240,  // 240x240
												FRAMESIZE_QVGA,     // 320x240
												FRAMESIZE_CIF,      // 400x296
												FRAMESIZE_HVGA,     // 480x320
												FRAMESIZE_VGA,      // 640x480
												FRAMESIZE_SVGA,     // 800x600
												FRAMESIZE_XGA,      // 1024x768
												FRAMESIZE_HD,       // 1280x720
												FRAMESIZE_SXGA,     // 1280x1024
												FRAMESIZE_UXGA,     // 1600x1200*/
		config.jpeg_quality = 10;		/*Poate fi orice între 0 și 63. Cu cât numărul este mai mic, cu atât calitatea este mai mare*/
		config.fb_count = 2;
		Serial.println("FRAMESIZE_HD");
	}
	else
	{
		config.frame_size = FRAMESIZE_CIF;
		config.jpeg_quality = 12;
		config.fb_count = 1;
		Serial.println("FRAMESIZE_QVGA");
	}

	// Inițializare cameră
	esp_err_t err = esp_camera_init(&config);
	if (err != ESP_OK)
	{
		Serial.printf("Inițializarea camerei a eșuat cu eroarea 0x%x", err);
		return;
	}

	// Reducerea dimensiunii frame-ului pentru o rată inițială mai mare
	sensor_t *s = esp_camera_sensor_get();
	s->set_framesize(s, FRAMESIZE_CIF);

	WiFi.begin(ssid, password);

	while (WiFi.status() != WL_CONNECTED)
	{
		delay(500);
		Serial.print(".");
	}
	Serial.println("");
	Serial.println("WiFi conectat");

	startCameraServer();

	Serial.print("Cameră pregătită! Utilizați 'http://");
	Serial.print(WiFi.localIP());
	WiFiAddr = WiFi.localIP().toString();
	Serial.println("' pentru conectare");
}

void loop()
{

	// puneți codul principal aici, pentru a rula în mod repetat:
}
