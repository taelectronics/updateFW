#include <Arduino.h>
#include <WiFiMulti.h>

#include "HttpsOTAUpdate.h"



#define WIFI_SSID "my wifi"
#define WIFI_PASSSWORD  "12345566778"

WiFiMulti wiFiMulti;

static const char *url = "https://github.com/taelectronics/updateFW/tree/main/BIN/fw.bin";  //state url of your firmware image

static const char *server_certificate = "-----BEGIN CERTIFICATE-----\n"
                                          "MIID9zCCAt+gAwIBAgIUTSm9YUDWx7aGVxhHov5xuVZ0pFEwDQYJKoZIhvcNAQEL\n"
                                          "BQAwgYoxCzAJBgNVBAYTAlZOMQswCQYDVQQIDAJUSDELMAkGA1UEBwwCVEgxCzAJ\n"
                                          "BgNVBAoMAlRIMQswCQYDVQQLDAJUSDEVMBMGA1UEAwwMKi5naXRodWIuY29tMTAw\n"
                                          "LgYJKoZIhvcNAQkBFiFlbGVjdHJvbmljcHJvZ3JhbW1pbmd0YUBnbWFpbC5jb20w\n"
                                          "HhcNMjQwNzA2MDgwNTIxWhcNMjcwNDI2MDgwNTIxWjCBijELMAkGA1UEBhMCVk4x\n"
                                          "CzAJBgNVBAgMAlRIMQswCQYDVQQHDAJUSDELMAkGA1UECgwCVEgxCzAJBgNVBAsM\n"
                                          "AlRIMRUwEwYDVQQDDAwqLmdpdGh1Yi5jb20xMDAuBgkqhkiG9w0BCQEWIWVsZWN0\n"
                                          "cm9uaWNwcm9ncmFtbWluZ3RhQGdtYWlsLmNvbTCCASIwDQYJKoZIhvcNAQEBBQAD\n"
                                          "ggEPADCCAQoCggEBAJy1YfXkca3fqp6X6FN0YE0Oi1DjlsxOkn3WJB63da1SIR9c\n"
                                          "RT6dl3AiDw7M2VLSP8HuC59utxifcJv1NGk9oLYgppY9eyr6dIfaT3mRMWsKOk+b\n"
                                          "7avDLvziSf/p5uJGKpGYGtwx4JDQynl5v/zY7PVRBITsyIOOfhLH1qwoczBn2RJi\n"
                                          "f0r3LLsF8RXSGa/GcIs4JyB1QgbfyTrUtKmoJDC9v3KeHoaQyG9doQmIZ7mKVwoC\n"
                                          "MoMY1avS/c2Y9WY56Gx2Xrfd7dPWgQD/kPpwG21Upo2rIAZ5DV/JJxfhciWSAqLp\n"
                                          "4OIaPf2cyZ3eyfykSqsUrjw+pw7JeZn/cUUp470CAwEAAaNTMFEwHQYDVR0OBBYE\n"
                                          "FPzi3l2fL26krz8xUYx1s8SK2SWKMB8GA1UdIwQYMBaAFPzi3l2fL26krz8xUYx1\n"
                                          "s8SK2SWKMA8GA1UdEwEB/wQFMAMBAf8wDQYJKoZIhvcNAQELBQADggEBADTAupN2\n"
                                          "Yw3mcGtxrApy/oK33k0W2qh/UInJ2gqo5F+m97ZTNEgYZzGBM2tEeMbtKJp/4WVS\n"
                                          "yWOldYt119/R92uUTt4gXj9M64dXCMN7TfD7dGWv+P3Zp58ziiixeQ2GbyDTeIak\n"
                                          "X0xPtXiI5xHGo8OJ7atHkGrAe7pKYRAUwm3V1ik/6bQs6mi6JUfHk+MfaHXw5b+T\n"
                                          "sW38WMHqRTrjUf+WP8rpD7Cerr2eS8wnhOc887S78m+pW7AgGdKsdSJgLLPWQ13/\n"
                                          "5qGpgUy2zch8Kd6elhA1NIv1SBrw2TU2Nh4K7r2oQrsSHD415fhpGEsRq9EkVBb8\n"
                                          "GAeXrSTbDOo2MMM=\n"
                                        "-----END CERTIFICATE-----\n";
static HttpsOTAStatus_t otastatus;
/*

void HttpEvent(HttpEvent_t *event) {
  switch (event->event_id) {
    case HTTP_EVENT_ERROR:        Serial.println("Http Event Error"); break;
    case HTTP_EVENT_ON_CONNECTED: Serial.println("Http Event On Connected"); break;
    case HTTP_EVENT_HEADER_SENT:  Serial.println("Http Event Header Sent"); break;
    case HTTP_EVENT_ON_HEADER:    Serial.printf("Http Event On Header, key=%s, value=%s\n", event->header_key, event->header_value); break;
    case HTTP_EVENT_ON_DATA:      break;
    case HTTP_EVENT_ON_FINISH:    Serial.println("Http Event On Finish"); break;
    case HTTP_EVENT_DISCONNECTED: Serial.println("Http Event Disconnected"); break;
    case HTTP_EVENT_REDIRECT:     Serial.println("Http Event Redirect"); break;
  }
} */


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

  otastatus = HttpsOTA.status();

  /* HttpsOTA.onHttpEvent(HttpEvent) ; */

  HttpsOTA.begin(url, server_certificate);

  otastatus = HttpsOTA.status();
  if (otastatus == HTTPS_OTA_SUCCESS) {
   /*  Serial.println("Firmware written successfully. To reboot device, call API ESP.restart() or PUSH restart button on device"); */
  } else if (otastatus == HTTPS_OTA_FAIL) {
    /* Serial.println("Firmware Upgrade Fail"); */
  }
  delay(1000);
}
