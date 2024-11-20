#include <LiquidCrystal_I2C.h>
#include <DHT.h>  // Including library for dht
#include <Wire.h>
#include <ESP8266WiFi.h>
String apiKey = "M3A28X4PHET5HCNS"; //  Enter your Write API key from ThingSpeak
const char *ssid =  "iPhone de Javier";     // replace with your wifi ssid and wpa2 key
const char *pass =  "12345678";
const char* server = "api.thingspeak.com";


LiquidCrystal_I2C lcd(0x27,16,4);
#define DHTPIN 2          //pin where the dht11 is connected
DHT dht(DHTPIN, DHT22);
WiFiClient client;


void setup() 
{
lcd.init();
lcd.backlight();

       Serial.begin(9600);
       delay(10);
       dht.begin();
 
       Serial.println("Connecting to ");
       Serial.println(ssid);
 
 
       WiFi.begin(ssid, pass);
 
      while (WiFi.status() != WL_CONNECTED) 
     {
            delay(500);
            Serial.print(".");
     }
      Serial.println("");
      Serial.println("WiFi connected");
pinMode(12,OUTPUT);
pinMode(13,OUTPUT);
pinMode(14,OUTPUT);
}


void loop() 
{

      float h = dht.readHumidity();
      float t = dht.readTemperature();
      
              if (isnan(h) || isnan(t)) 
                 {
                     Serial.println("Failed to read from DHT sensor!");
                      return;
                 }
 
                         if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
                      {  
                            
                             String postStr = apiKey;
                             postStr +="&field1=";
                             postStr += String(t);
                             postStr +="&field2=";
                             postStr += String(h);
                             postStr += "\r\n\r\n";
 
                             client.print("POST /update HTTP/1.1\n");
                             client.print("Host: api.thingspeak.com\n");
                             client.print("Connection: close\n");
                             client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
                             client.print("Content-Type: application/x-www-form-urlencoded\n");
                             client.print("Content-Length: ");
                             client.print(postStr.length());
                             client.print("\n\n");
                             client.print(postStr);
 
                             Serial.print("Temperature: ");
                             Serial.print(t);
                             Serial.print(" degrees Celcius, Humidity: ");
                             Serial.print(h);
                             Serial.println("%. Send to Thingspeak.");
                        }
          client.stop();
 
          Serial.println("Waiting...");
  
  // thingspeak needs minimum 15 sec delay between updates
delay(5000);

//LEDS 
//15% lower limit turn on yellow LED
if (t<30){
    digitalWrite (12,HIGH);
  }
else {
    digitalWrite (12,LOW);
  }
  //15% upper limit turn on red LED
if (t>40){ 
    digitalWrite (14,HIGH);
  }
else {
    digitalWrite (14,LOW);
  }
    //If not red nor yellow, turn on green LED
if (t<40 && t>30 ){
    digitalWrite (13,HIGH);
  }
else {
    digitalWrite (13,LOW);
  }


// Print Temperature and Humidity
lcd.setCursor(3,4);
lcd.print("MTY, N.L.");
lcd.setCursor(3,1);
lcd.print("Temp. y Humedad");
lcd.setCursor(3,2);
lcd.print(t);
lcd.setCursor(8,2);
lcd.print("C");
lcd.setCursor(3,3);
lcd.print(h);
lcd.setCursor(8,3);
lcd.print("\%");
\}
