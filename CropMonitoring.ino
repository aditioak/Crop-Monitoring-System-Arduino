#include "DHT.h"
#define DHTPIN 2  
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);

//photodiode sensor
 int pd=3;   
 int senRead=A1;  
 
//Soil moisture sensor
#define sensorPower 7
#define sensorPin A0

  //  This function returns the analog soil moisture measurement
int readSensor() {
  digitalWrite(sensorPower, HIGH);  // Turn the sensor ON
  delay(10);              // Allow power to settle
  int val = analogRead(sensorPin);  // Read the analog value form sensor
  digitalWrite(sensorPower, LOW);   // Turn the sensor OFF
  return val;             // Return analog moisture value

}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
//  Serial.println(F("DHTxx test!"));
  dht.begin();

  pinMode(pd,OUTPUT);  
  digitalWrite(pd,HIGH);

  //soil moisture
   pinMode(sensorPower, OUTPUT);  
  // Initially keep the sensor OFF
  digitalWrite(sensorPower, LOW);

}

void loop() {
  // put your main code here, to run repeatedly:
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

//  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(" ");
//  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(" ");
//  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(" ");
//  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(" ");
//  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.print(" ");
//  Serial.println(F("°F"));


  //Photodiode
   float val=analogRead(senRead);  //variable to store values from the photodiode  
   val=(val/1023)*100;
//   float ValInV=val*(5.0/1023.0);
//  Serial.print("Photodiode value is: ");          // prints the values from the sensor in serial monitor  
 Serial.print(val); 
// Serial.println("V");    

  //SoilMoisture

    //get the reading from the function below and print it
//  Serial.print("Analog output of soil moisture sensor is: ");
Serial.print(" ");
  Serial.print((float(readSensor())/1023)*100);
  Serial.print("\n");
  delay(2000);
}
