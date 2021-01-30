#include "config/config_wifi.h"
#include <WiFi.h>  
#include <U8g2lib.h>
#include <Wire.h>
#include "esp32-mqtt.h"
#include "time.h"
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);


int Buzzer = 32;        // used for ESP32
int Gas_analog = 34;    // used for ESP32
char str[8];            // variable int to string
const char* connection ;
unsigned long lastMillis = 0;
#define MQ135_THRESHOLD_1 1000 // Fresh Air threshold
#define MQ135_MIN 300 // Fresh Air threshold
WiFiClient askClient;


const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 3600;
const char* ppm_time = "";
char resutltime[80];
char resutltimetimeHour[3];
char resutltimetimeWeekDay[10];

void setup() {
u8g2.begin(); //Init
Serial.begin(115200);
Serial.println("**********************************");
Serial.println("*****Program Start: ESP32 publishes MQ-135n ");
//initialise_wifi();
pinMode(LED_BUILTIN, OUTPUT);
setupCloudIoT();
//init and get the time
configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

}

void loop() {
  
Serial.println(WiFi.localIP());
delay(1000);
int MQ135_data = analogRead(Gas_analog); 
itoa( MQ135_data, str, 10 );

/* date */
struct tm timeinfo;
if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
} else {
    //strftime(resutltimetimeHour,3, "%H", &timeinfo);
    strftime(resutltime, 20,"%Y-%m-%d %H:%M:%S", &timeinfo);

}
/* date */


/* Status connection */
if(WiFi.status() != WL_CONNECTED){
connection = "Connect:Off-line";  
}else{
connection = "Connect:On-line";

}
/* Status connection */

/* Alarm */
if(MQ135_data < MQ135_THRESHOLD_1){
Serial.print("Fresh Air: ");
} else {
Serial.print("Poor Air: ");
digitalWrite (Buzzer, HIGH) ; //send tone
delay(2000);
digitalWrite (Buzzer, LOW) ;  //no tone
}
/* Alarm */

if(MQ135_data <= MQ135_MIN){
Serial.println(MQ135_data);              // analog data
Serial.println(" CO2 particles PPM");    // Unit = part per million
} else {
Serial.print(MQ135_data);                // analog data
Serial.println("CO2 particles PPM");     // Unit = part per million
}

/* send data to display */
u8g2.clearBuffer();                      // clear buffer
u8g2.setFont(u8g2_font_logisoso16_tr);   // fonts
u8g2.drawStr(1,15,"CO2 particles");      // write (X,Y)
u8g2.drawStr(20,33,str);                 // write (X,Y) 
u8g2.drawStr(65,33, "PPM" );             // write (X,Y) 
u8g2.drawStr(1,52,connection);           // write (X,Y) 
u8g2.sendBuffer();                       // send data to display
/* send data to display */

/* send data GCP */
mqtt->loop();
delay(10);                              // <- fixes some issues with WiFi stability
if (!mqttClient->connected()) {
    connect();
}
if (millis() - lastMillis > 10000) {
    lastMillis = millis();
    String payload =
    String("{\"fecha\":\"") + resutltime 
    + String("\",\"device_id\":\"") + device_id
    + String("\",\"name\":\"") + str + String("\"}");
    
    Serial.println(payload);
    publishTelemetry(payload); 
}
/* send data GCP */

} //loop
