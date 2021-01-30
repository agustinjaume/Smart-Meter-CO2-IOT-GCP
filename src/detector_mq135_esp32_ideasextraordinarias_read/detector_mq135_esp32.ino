#include "config/config_wifi.h"
#include <WiFi.h>
int Buzzer = 32;        // used for ESP32
int Gas_analog = 34;    // used for ESP32
int Gas_digital = 2;   // used for ESP32
#define MQ135_THRESHOLD_1 1000 // Fresh Air threshold
WiFiClient askClient;
void setup() {
Serial.begin(115200);
Serial.println("*****************************************************");
Serial.println("********** Program Start : ESP32 publishes MQ-135n data to AskSensors over MQTT");
Serial.print("********** connecting to WIFI : ");
Serial.println(ssid);
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
Serial.println("");
Serial.println("->WiFi connected");
Serial.println("->IP address: ");
Serial.println(WiFi.localIP());
}
void loop() {
int MQ135_data = analogRead(Gas_analog);
if(MQ135_data < MQ135_THRESHOLD_1){
Serial.print("Fresh Air: ");
} else {
Serial.print("Poor Air: ");
digitalWrite (Buzzer, HIGH) ; //send tone
delay(1000);
digitalWrite (Buzzer, LOW) ;  //no tone
}
Serial.print(MQ135_data); // analog data
Serial.println(" PPM"); // Unit = part per million

} //loop
