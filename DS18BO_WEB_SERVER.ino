#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#define ESP32_BAUD 9600

#include <OneWire.h>
#include <DallasTemperature.h> 
#define ONE_WIRE_BUS 4         // Your ESP8266 pin (ESP8266 GPIO 2 = WeMos D1 Mini pin D4)
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
#define Wire 2

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "0_c6XxschV0ZfoF46U7HOSKK8xkzQK3t";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Malware repository";
char pass[] = "Yogesh@2002";

BlynkTimer timer;

float roomTemperature;            // Room temperature in F
long prevMillis = 0;
int interval = 1000;
char bpm;

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);

  sensors.begin();     
  // Starts the DS18B20 sensor(s)
  Wire.begin(); 
}

void loop()
{
  Blynk.run();
  timer.run();
  sensors.requestTemperatures(); 
  float temperatureC = sensors.getTempCByIndex(0);
  float temperatureF = sensors.getTempFByIndex(0);
  Serial.print(temperatureC);
  Serial.println("ºC");
  Serial.print(temperatureF);
  Serial.println("ºF");
  delay(100);
  Blynk.virtualWrite(1, temperatureC);
  
  Wire.requestFrom(0xA0 >> 1, 1);

  bpm = Wire.read(); // receive heart rate value (a byte)
  Serial.println(bpm, DEC); // print heart rate value

  Blynk.virtualWrite(0, bpm);
  
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
}
