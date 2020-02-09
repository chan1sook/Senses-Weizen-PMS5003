#include <SoftwareSerial.h>
#include "PMS.h"
#include "Senses_wifi_esp32.h"

const char *ssid = "WIFI SSID";
const char *passw = "WIFI PASSWORD";
const char *userid = "SENSES USERID";
const char *key = "DEVICE KEY";

#define PM25_SLOT_DATA 1
#define SEND_DATA_DELAY 5000

SoftwareSerial pmsSerial(34, 26);
Senses_wifi_esp32 myiot;

String response;
float pm25data;

PMS pms(pmsSerial);
PMS::DATA pmsData;

void setup() {
  Serial.begin(9600);
  pmsSerial.begin(9600);

  response = myiot.connect(ssid, passw, userid, key);
  Serial.println(response);
}

void loop() {
  if(pms.read(pmsData))
  {
    pm25data = pmsData.PM_AE_UG_2_5;
    Serial.print("PM 2.5 (μg/m3): ");
    Serial.println(pm25data);

    response = myiot.send(PM25_SLOT_DATA, pm25data);
    Serial.println(response);

    Serial.println();
    delay(SEND_DATA_DELAY);
  }
}
