#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include<SoftwareSerial.h>
SoftwareSerial espSerial(D1,D2);

#define FIREBASE_HOST "plantmonitoringsystem-da869-default-rtdb.firebaseio.com"      
#define FIREBASE_AUTH "qCo3Mqk4Ksz5JLzEyQaPkjJUBMYR2CUcs4rdLs6K"            


const char *ssid =  "Airtel-E5573-92C2";     // replace with your wifi ssid and wpa2 key
const char *pass =  "hd1997r8";

WiFiClient client;


String getValue(String data, char separator, int index)
   {
     int found = 0;
      int strIndex[] = {0, -1};
      int maxIndex = data.length()-1;
   
     for(int i=0; i<=maxIndex && found<=index; i++){
      if(data.charAt(i)==separator || i==maxIndex){
            found++;
            strIndex[0] = strIndex[1]+1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
      }
    
      return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
  }   
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
          WiFi.begin(ssid, pass); 
       while (WiFi.status() != WL_CONNECTED) 
          {
            delay(500);
            Serial.print(".");
          }
      Serial.println("");
      Serial.println("WiFi connected"); 




Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  
  espSerial.begin(9600); 
}

void loop() {
   //put your main code here, to run repeatedly:
    String msg=espSerial.readStringUntil('\n');

  
    String humidity = getValue(msg,' ',0);
    String TempC = getValue(msg,' ',1);
    String TempF = getValue(msg,' ',2);
    String HeatC = getValue(msg,' ',3);
    String HeatF = getValue(msg,' ',4);
    String Photodiode = getValue(msg,' ',5);
    String SoilM = getValue(msg,' ',6);

  if(humidity!="")
    Firebase.pushString("/SensorOutput/Humidity", humidity);            //setup path to send Humidity readings
     if(TempC!="")
    Firebase.pushString("/SensorOutput/TemperatureinC", TempC);         //setup path to send Temperature readings
//    Firebase.pushString("/SensorOutput/TemperatureinF", TempF);
 if(HeatC!="") 
    Firebase.pushString("/SensorOutput/HeatIndexinC", HeatC); 
//    Firebase.pushString("/SensorOutput/HeatIndexinF", HeatF); 
 if(Photodiode!="")
    Firebase.pushString("/SensorOutput/PhotodiodeOutput", Photodiode); 
     if(SoilM!="")
    Firebase.pushString("/SensorOutput/SoilMoistureOutput", SoilM); 
    if (Firebase.failed()) 
    {
 
      Serial.print("pushing /logs failed:");
      Serial.println(Firebase.error()); 
      return;
  }        

if ((humidity!="") && (TempC!="") && (HeatC!="") && (Photodiode!="") && (SoilM!=""))
{
//  Firebase.pushString("/SensorOutput", "");    
  Firebase.setString("/LiveOutput/LiveData", msg);
  Serial.print("Humidity: ");
  Serial.println(humidity);    
  Serial.print("Temperature in C: ");
  Serial.println(TempC);
  Serial.print("Heat Index in C: ");
  Serial.println(HeatC);
  Serial.print("Photo sensor Output in %: ");
  Serial.println(Photodiode);
  Serial.print("Soil Moisture Output in %: ");
  Serial.println(SoilM);
  Serial.print("\n");
  
}
  


//  // handle error
//  if (Firebase.failed()) {
//      Serial.print("setting /message failed:");
//      Serial.println(Firebase.error());  
//      return;
//  }
//  delay(100);
//
//  Serial.println(humidity);
//
//  String name = Firebase.pushString("logs", msg);
//  // handle error
//  if (Firebase.failed()) {
//      Serial.print("pushing /logs failed:");
//      Serial.println(Firebase.error());  
//      return;
//  }
//  Serial.print("pushed: /logs/");
//  Serial.println(name);
//  delay(1000);

}
