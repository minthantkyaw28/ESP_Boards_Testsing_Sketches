#include <Arduino.h>
// #include <WiFi.h>
#include <ESP8266WiFi.h>
#include <Firebase_ESP_Client.h>

//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

// Insert your network credentials
#define WIFI_SSID "GUSTO_209"
#define WIFI_PASSWORD "Gusto@123"

//Insert your network credentials
// #define WIFI_SSID "GUSTO WiFi"
// #define WIFI_PASSWORD "Gusto@123"



// Insert Firebase project API Key
#define API_KEY "AIzaSyAxHmTsjdZ-KCwiBOhzqPY2esib-s84FRA"

// Insert RTDB URLefine the RTDB URL */
#define DATABASE_URL "https://testingesp8266-e9ed1-default-rtdb.asia-southeast1.firebasedatabase.app/" 

//Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
int count = 0;
bool signupOK = false;


const int sensorPin = A0;  // Analog pin connected to the turbidity sensor


// Calibration data points (customize based on your own calibration data)
const int numDataPoints = 5;
const int sensorReadings[numDataPoints] = {0, 256, 512, 768, 1023};
const float ntuValues[numDataPoints] = {0.0, 10.0, 50.0, 100.0, 200.0};
String turbidityStatus = "";

void setup(){
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")){
    Serial.println("ok");
    signupOK = true;
  }
  else{
    // Serial.print("%s\n", config.signer.signupError.message.c_str());
  }

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
  
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop(){
  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 500 || sendDataPrevMillis == 0)){
    sendDataPrevMillis = millis();




  int turbidityValue = analogRead(sensorPin);
  float ntu = convertToNTU(turbidityValue);
  //float ntu = turbidityValue * (1.0 / 1023.0);

  if(ntu>=170){
    turbidityStatus="Clean Water";
    Serial.println("Turbidity (NTU): "+String(ntu)+" "+turbidityStatus);
  }else{
    turbidityStatus="Polluted Water";
    Serial.println("Turbidity (NTU): "+String(ntu)+" "+turbidityStatus);
  }
  
  //Serial.println("Turbidity Value : "+String(turbidityValue));
  //delay(1000);  // Wait for 1 second before taking 

    // // Write an Int number on the database path test/int
    // if (Firebase.RTDB.setInt(&fbdo, "test/int", count)){
    //   Serial.println("PASSED");
    //   Serial.println("PATH: " + fbdo.dataPath());
    //   Serial.println("TYPE: " + fbdo.dataType());
    // }
    // else {
    //   Serial.println("FAILED");
    //   Serial.println("REASON: " + fbdo.errorReason());
    // }
    // count++;
    
    // Write an Float data on the database path sensor_readings/turbidity_level
    if (Firebase.RTDB.setString(&fbdo, "sensor_readings/turbidity_level",turbidityStatus)){
      //Serial.println("PASSED");
      //Serial.println("PATH: " + fbdo.dataPath());
      //Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }


     // Write an Float data on the database path sensor_readings/turbidity_level
    if (Firebase.RTDB.setFloat(&fbdo, "sensor_readings/ntu_level", ntu)){
      //Serial.println("PASSED");
     //Serial.println("PATH: " + fbdo.dataPath());
      //Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
    
  }
}


float convertToNTU(int sensorReading) {
  if (sensorReading <= sensorReadings[0])
    return ntuValues[0];
  else if (sensorReading >= sensorReadings[numDataPoints - 1])
    return ntuValues[numDataPoints - 1];
  
  // Perform linear interpolation
  for (int i = 0; i < numDataPoints - 1; i++) {
    if (sensorReading >= sensorReadings[i] && sensorReading <= sensorReadings[i + 1]) {
      float slope = (ntuValues[i + 1] - ntuValues[i]) / (sensorReadings[i + 1] - sensorReadings[i]);
      float ntu = ntuValues[i] + slope * (sensorReading - sensorReadings[i]);
      
      return ntu;
    }
  }
  
  return 0.0;  // Default value if interpolation fails
}