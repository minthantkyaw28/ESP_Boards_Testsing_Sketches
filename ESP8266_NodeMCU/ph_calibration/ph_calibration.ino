// // Define the pin for pH sensor
// const int pHSensorPin = A0;

// void setup() {
//   // Initialize the serial communication
//   Serial.begin(9600);
// }

// void loop() {
//   // Read the pH value from the sensor
//   int pHValue = analogRead(pHSensorPin);

//   // Convert the analog value to pH
//   float voltage = pHValue * 5.0 / 1024.0;
//   float pH = -5.7 * voltage + 21.34;

//   // Print the pH value to the serial monitor
//   Serial.print("pH: ");
//   Serial.println(pH);

//   delay(1000);  // Wait for 1 second
// }
#include <Arduino.h>

int sensor_Reading_Value; 
float Voltage;
 
void setup() 
{ 
  Serial.begin(9600);
 // pinMode(pH_Value, INPUT); 
} 
 
void loop() 
{ 
  sensor_Reading_Value = analogRead(A0); 
  //Serial.println(sensor_Reading_Value); 
  

  Voltage = sensor_Reading_Value * (5.0 / 1023.0); 
   Voltage= Voltage-0.15;
   Serial.println("PH Level : "+String(Voltage*2.8)); 
  delay(500); 
}




// #define SensorPin A0          // the pH meter Analog output is connected with the Arduino’s Analog
// unsigned long int avgValue;  //Store the average value of the sensor feedback
// float b;
// int buf[10],temp;
 
// void setup()
// {
//   pinMode(13,OUTPUT);  
//   Serial.begin(9600);  
//   Serial.println("Ready");    //Test the serial monitor
// }
// void loop()
// {
//   for(int i=0;i<10;i++)       //Get 10 sample value from the sensor for smooth the value
//   { 
//     buf[i]=analogRead(SensorPin);
//     delay(10);
//   }
//   for(int i=0;i<9;i++)        //sort the analog from small to large
//   {
//     for(int j=i+1;j<10;j++)
//     {
//       if(buf[i]>buf[j])
//       {
//         temp=buf[i];
//         buf[i]=buf[j];
//         buf[j]=temp;
//       }
//     }
//   }
//   avgValue=0;
//   for(int i=2;i<8;i++)                      //take the average value of 6 center sample
//     avgValue+=buf[i];
    
//   float phValue=(float)avgValue*5.0/1024/6; //convert the analog into millivolt
//   phValue=3.5*phValue;                      //convert the millivolt into pH value
//   Serial.print("    pH:");  
//   Serial.print(phValue,2);
//   Serial.println(" ");
//   digitalWrite(13, HIGH);       
//   delay(800);
//   digitalWrite(13, LOW); 
 
// }



// float calibration = 0.00; //change this value to calibrate
// const int analogInPin = A0; 
// int sensorValue = 0; 
// unsigned long int avgValue; 
// float b;
// int buf[10],temp;
// void setup() {
// Serial.begin(9600);
// }
// void loop() {
// for(int i=0;i<10;i++) 
// { 
// buf[i]=analogRead(analogInPin);
// delay(30);
// }
// for(int i=0;i<9;i++)
// {
// for(int j=i+1;j<10;j++)
// {
// if(buf[i]>buf[j])
// {
// temp=buf[i];
// buf[i]=buf[j];
// buf[j]=temp;
// }
// }
// }
// avgValue=0;
// for(int i=2;i<8;i++)
// avgValue+=buf[i];
// float pHVol=(float)avgValue*5.0/1024/6;
// float phValue = -5.70 * pHVol + calibration;
// Serial.print("sensor = ");
// Serial.println(phValue);
// delay(500);
// }


// // pH Sensor Pin
// const int pHpin = A0;

// // Variables
// float pHValue = 0.0;

// // Calibration Constants (Adjust according to your sensor)
// float pHCalibration = 7;

// void setup() {
//   // Start Serial Monitor
//   Serial.begin(9600);
// }

// void loop() {
//   // Read pH Sensor
//   int pHSensorValue = analogRead(pHpin);
//   pHValue = convertToPH(pHSensorValue);

//   // Print pH Value
//   Serial.print("pH: ");
//   Serial.println(pHValue);

//   delay(1000); // Delay between readings
// }

// // Convert pH Sensor Reading to pH Level
// float convertToPH(int sensorValue) {
//   // Convert the sensor reading to pH value
//   float pH = sensorValue * pHCalibration;
//   return pH;
// }
