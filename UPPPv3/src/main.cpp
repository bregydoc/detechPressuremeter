#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "ESP8266WebServer.h"
#include <FirebaseArduino.h>


#define FIREBASE_HOST "detech-1e226.firebaseio.com"
#define FIREBASE_AUTH "7TFuGs6pEOLkWe3DBSSUbIswuHaUBHVy5VpaVen1"
#define WIFI_SSID "MEDICAL"
#define WIFI_PASSWORD "10222375"


#define ledBusy  12
#define ledConn  13


bool statusLed = 0;
bool dbLed = 0;

void setup() {


    pinMode(ledBusy, OUTPUT);
    pinMode(ledConn, OUTPUT);

    Serial.begin(9600);

    digitalWrite(ledConn, 1);
    digitalWrite(ledBusy, statusLed);

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        statusLed = statusLed xor 1;
        digitalWrite(ledBusy, statusLed);
        delay(100);

    }

    digitalWrite(ledBusy, 1);

    Serial.println();
    Serial.print("connected: ");
    Serial.println(WiFi.localIP());

    digitalWrite(ledConn, 0);
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
    digitalWrite(ledConn, 1);

}

void loop() {
    float rawPressure = constrain(990-analogRead(0), 0, 990);
    //0.00263233
    float realPressure = (0.00273233*rawPressure + 0.08200484)*735.5591210146755;
    //Firebase.setFloat("currentPressureValue", realPressure);
    Serial.println(rawPressure);
    /*
    if (Firebase.failed()) {
            digitalWrite(ledConn, 0);
        //Serial.print("setting /number failed:");
        Serial.println(Firebase.error());
        return;
    }
    */
    dbLed = dbLed xor 1;
    digitalWrite(ledBusy, dbLed);
    delay(10);

}
