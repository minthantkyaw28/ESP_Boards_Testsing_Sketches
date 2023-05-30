const int relay = 12; //relay signal pin / D6

const int sensorPin = A0; //analog signal pin / A0 for water level sensor 

int counter_water_level=0;

void setup() {

  Serial.begin(115200);
  pinMode(relay, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
 

  while(counter_water_level==0){
    water_lvl_func();
  }

  delay(1000);

}

void run_motor_func(int motorRunTime){
  // Normally Open configuration, send LOW signal to let current flow
  // (if you're usong Normally Closed configuration send HIGH signal)
  digitalWrite(relay, LOW);
  //Serial.println("Current Flowing");
  delay(motorRunTime); 
  
  // Normally Open configuration, send HIGH signal stop current flow
  // (if you're usong Normally Closed configuration send LOW signal)
  digitalWrite(relay, HIGH);
  //Serial.println("Current not Flowing");

  counter_water_level+=1;
}


void water_lvl_func(){

  int sensorValue = analogRead(sensorPin); 
  Serial.print("Sensor value: ");

  if (sensorValue >= 600) { // Water high
    
    run_motor_func(2000);
    Serial.println("Sensor value is = "+String(sensorValue)+" It is high !!!"); 

  }else { // Water low
    digitalWrite(relay, HIGH);
    Serial.println("Sensor value is = "+String(sensorValue)+" It is Low !!!"); 
  }

}
