/*
  LinkIt Smart 7688 Duo Example - LinkIt One board to IBM Bluemix Connection quick start
- continuously obtains values from the Virtuabotix DHT11 temperature/humidity sensor
- formats the results as a JSON string for the IBM IOT example
- connects to an MQTT server (either local or at the IBM IOT Cloud)
- and publishes the JSON String to the topic named quickstart:MY_MAC_ADDRESS
*/



#include <SPI.h>
#include <YunClient.h>

// You can get the Pubsub client from https://github.com/knolleary/pubsubclient
#include <PubSubClient.h>
#include <Wire.h>


// This sketch uses DHT library from github : https://github.com/RobTillaart/Arduino/tree/master/libraries/DHTlib
// You can download DHT library from the above link and add the library to Arduino IDE.

#include <dht.h>


// Edit the PIN number if you have connected the sensor to PIN other than 4.
#define DHT22_PIN 4


char macstr[] = "123456789abcdef";  // Enter the device mac address here


char servername[] = "quickstart.messaging.internetofthings.ibmcloud.com";
String clientName = String("d:quickstart:arduino:") + macstr; 
String topicName = String("iot-2/evt/status/fmt/json");

float tempC = 0.0;
float humidity = 0.0;

dht DHT;
YunClient wifiClient;
PubSubClient client(servername, 1883, 0, wifiClient);


void setup()
{

   // Start the Yun Bridge
   Bridge.begin();
    
   Serial.begin(9600);

}

void loop()
{
 
  char clientStr[34];
  clientName.toCharArray(clientStr,34);
  char topicStr[26];
  topicName.toCharArray(topicStr,26);
  

  // Read the Temperature and humuditiy data from the DHT sensor
  getData();
  
  if (!client.connected()) {
    Serial.print("Trying to connect to: ");
    Serial.println(clientStr);
   
    Serial.println("Connecting to server "); 
    while (! client.connect(clientStr))
    {
      Serial.println("Re-Connecting to SERVER");
      delay(3000);
    }
   Serial.println("Connected to server");
    
  }
  
  if (client.connected() ) {
    
    Serial.println("Connected to server : Building jason");
    
    String json = buildJson();
    char jsonStr[200];
    json.toCharArray(jsonStr,200);
    Serial.println("Connected to server : publishing");
    boolean pubresult = client.publish(topicStr,jsonStr);
    Serial.print("attempt to send ");
    Serial.println(jsonStr);
    Serial.print("to ");
    Serial.println(topicStr);
    if (pubresult)
     Serial.println("successfully sent");
    else
      Serial.println("unsuccessfully sent");
  }
  else  Serial.println("not Yet connected");
  
  delay(5000);
}

String buildJson() {
  String data = "{";
  data+="\n";
  data+= "\"d\": {";
  data+="\n";
  data+="\"Device\": \"LinkIt Smart 7688 Duo DHT\",";
  data+="\n";
  data+="\"temperature (C)\": ";
  data+=(int)tempC;
  data+= ",";
  data+="\n";
  data+="\"humidity\": ";
  data+=(int)humidity;
  data+="\n";
  data+="}";
  data+="\n";
  data+="}";
  return data;
}

void getData() {

   int chk = DHT.read22(DHT22_PIN);
   if(chk == DHTLIB_OK)
    {
        Serial.println("------------------------------");

        tempC = DHT.temperature; 
        humidity = DHT.humidity;
      
        
        Serial.print("temperature = ");
        Serial.println(tempC);
        Serial.print("humidity = ");
        Serial.println(humidity);
    }
    else
    {
         Serial.print("Sensor Error: Temperature Read FAILED !!");
         // Setting the temperature and humidity values to ZERO. !!
         tempC = 0.0; 
         humidity = 0.0;
    }
    
}
