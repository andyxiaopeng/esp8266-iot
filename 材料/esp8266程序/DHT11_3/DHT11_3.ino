#include "DHT.h"
#define DHTPIN 5
#define DHTTYPE DHT11

// Initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE, 15);

void setup() {

  // Start Serial  
  Serial.begin(115200); 
 
  // Init DHT 
  dht.begin();
}

void loop() {

  // Reading temperature and humidity
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // Display data
  Serial.print("Humidity: "); 
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: "); 
  Serial.print(t);
  Serial.println(" *C ");
  
   // Wait a few seconds between measurements.
  delay(2000);
}
