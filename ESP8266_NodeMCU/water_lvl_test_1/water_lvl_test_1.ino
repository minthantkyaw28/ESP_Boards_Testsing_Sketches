const int sensorPin = A0;

void setup() {
   Serial.begin(115200);
 
}

void loop() {
 
  water_lvl_func();
  delay(1000); // Wait for 0.1 second before checking the sensor again

}


void water_lvl_func(){

  int sensorValue = analogRead(sensorPin); 
  Serial.print("Sensor value: ");

  if (sensorValue >= 600) { // Water high
    
    Serial.println("Sensor value is = "+String(sensorValue)+" It is high !!!"); 

  }else { // Water low
   
    Serial.println("Sensor value is = "+String(sensorValue)+" It is Low !!!"); 
  }

}
