#include <Arduino.h>
#include <WiFiMulti.h>

#include "HttpsOTAUpdate.h"

#define WIFI_SSID "my wifi"
#define WIFI_PASSSWORD  "12345566778"

WiFiMulti wiFiMulti;

/* put function declarations here: */
void WiFi_Init();

void Update_FW();

void setup() {
  Serial.begin(9600);
  (void) WiFi_Init();
  /**/

  (void) Update_FW();
}

void loop() {
  /* put your main code here, to run repeatedly: */
}


void WiFi_Init()
{
  wiFiMulti.addAP(WIFI_SSID, WIFI_PASSSWORD);

  while(wiFiMulti.run() != WL_CONNECTED)
  {
    delay(100);
  }

}


void Update_FW()
{
  String url = "http://otadrive.com/deviceapi/update?";
    url += "k=" + key;
    url += "&v=" + version;
    url += "&s=" + getChipId(); // định danh thiết bị trên Cloud

    WiFiClient client;
    httpUpdate.update(client, url, version);
}
