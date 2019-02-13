#include <ESP8266WiFi.h>
#include <Wire.h>
#include <BH1750.h>
#include <DHT.h> 
#include <DallasTemperature.h>
#include <OneWire.h>

#define ONE_WIRE_BUS 12
#define DHTPIN  13                        // DHT11 data pin is connected to Arduino pin 8
#define DHTTYPE DHT11                    // DHT11 sensor is used

DHT dht(DHTPIN, DHTTYPE);
BH1750 lightMeter(0x23);
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensores(&oneWire);

//char temperature[] = "00 C";
//char humidity[]    = "00%";

float temperatura=0;
void setup(){

  Serial.begin(9600);
  dht.begin();                // Initialize the DHT library
  sensores.begin(); //Se inician los sensores
  // Initialize the I2C bus (BH1750 library doesn't do this automatically)
  Wire.begin();
  // begin returns a boolean that can be used to detect setup problems.
  if (lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE)) {
    Serial.println("BH1750 inicia");
  }
  else {
    Serial.println("Error iniciando BH1750");
  }
}

void loop() {

  // Read humidity
  float temp=dht.readTemperature();
  float hum=dht.readHumidity();
//  byte RH = dht.readHumidity();
//  //Read temperature in degree Celsius
//  byte Temp = dht.readTemperature();
//
//  temperature[0] = Temp / 10 + 48;
//  temperature[1] = Temp % 10 + 48;
//  humidity[0]    = RH / 10 + 48;
//  humidity[1]    = RH % 10 + 48;

  sensores.requestTemperatures(); //Prepara el sensor para la lectura
  temperatura= sensores.getTempCByIndex(0);
  
  float lux = lightMeter.readLightLevel();

  Serial.print("DS18B20: ");
  Serial.print(temperatura);
  Serial.println("");
  Serial.println("");
  Serial.print("DHT11: ");
  Serial.print("\t");
  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.print("\t");
  Serial.print("Humedad: ");
  Serial.print(hum);
  Serial.println("");
  Serial.println("");
  
  Serial.print("Luz (iluminancia): ");
  Serial.print(lux);
  Serial.println(" lx");
  Serial.println("");
  Serial.println("");
  delay(300);

}
