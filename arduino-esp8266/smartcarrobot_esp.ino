#include <AuthClient.h>
#include <MicroGear.h>
#include <MQTTClient.h>
#include <SHA1.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <EEPROM.h>
#include <MicroGear.h>

const char* ssid     = "<ssid>";
const char* password = "<password>";

#define APPID       "<APPID>"
#define GEARKEY     "<GEARKEY>"
#define GEARSECRET  "<GEARSECRET>"
#define SCOPE       ""

int ledD0 =  16;
int ledD1 =  5;

WiFiClient client;
AuthClient *authclient;


MicroGear microgear(client);

void onMsghandler(char *topic, uint8_t* msg, unsigned int msglen) {
  if(msg[0] == 'L'){
    Serial.println("L");
    digitalWrite(ledD1, HIGH);
    delay(100);
    digitalWrite(ledD1, LOW);
  }
  if(msg[0] == 'R'){
    Serial.println("R");
    digitalWrite(ledD1, HIGH);
    delay(100);
    digitalWrite(ledD1, LOW);
  }
  if(msg[0] == 'F'){
    Serial.println("F");
    digitalWrite(ledD1, HIGH);
    delay(100);
    digitalWrite(ledD1, LOW);
  }
  if(msg[0] == 'B'){
    Serial.println("B");
    digitalWrite(ledD1, HIGH);
    delay(100);
    digitalWrite(ledD1, LOW);
  }
}

void onConnected(char *attribute, uint8_t* msg, unsigned int msglen) {
    microgear.setName("robotcar");
}

void setup() {
    /* Event listener */
    microgear.on(MESSAGE,onMsghandler);
    microgear.on(CONNECTED,onConnected);
    Serial.begin(9600);
    
    pinMode(ledD0, OUTPUT);
    pinMode(ledD1, OUTPUT);
    
    if (WiFi.begin(ssid, password)) {

      while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        //Serial.print(".");
      }

      //uncomment the line below if you want to reset token -->
      //microgear.resetToken();
      microgear.init(GEARKEY,GEARSECRET,SCOPE);
      microgear.connect(APPID);
    }
}

int timer = 0;

void loop() {
  if (microgear.connected()) {
    microgear.loop();
    digitalWrite(ledD0, HIGH);
    if(timer==1500){
      //Serial.println("Publish...");
      microgear.chat("controller","O");
      timer=0;
    }else{
      delay(200);
      timer=timer+100;  
    }
  }else {
    digitalWrite(ledD0, LOW);
    microgear.connect(APPID);
    delay(3000);
  }
}
