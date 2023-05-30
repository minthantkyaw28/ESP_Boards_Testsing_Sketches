    /*
  modified on Sep 28, 2020
  Modified by MohammedDamirchi from Arduino Examples
  Home
*/


// the setup routine runs once when you press reset:
// void setup() {
//   // initialize serial communication at 9600 bits per second:
//   Serial.begin(9600);
// }

// // the loop routine runs over and over again forever:
// void loop() {
//   // read the input on analog pin 0:
//   int sensorValue = analogRead(A0);
//   // print out the value you read:
//   Serial.println(sensorValue);
//   delay(800);
//   }

const int sensorPin = A0;  // Analog pin connected to the turbidity sensor

// Calibration data points (customize based on your own calibration data)
const int numDataPoints = 5;
const int sensorReadings[numDataPoints] = {0, 256, 512, 768, 1023};
const float ntuValues[numDataPoints] = {0.0, 10.0, 50.0, 100.0, 200.0};

void setup() {
  Serial.begin(9600);  // Initialize serial communication
}

void loop() {
  // Read the analog value from the turbidity sensor
  int sensorValue = analogRead(sensorPin);
  
  // Convert the sensor reading to NTU
  float ntu = convertToNTU(sensorValue);
  
  // Print the turbidity value in NTU
  Serial.println("Turbidity (NTU): "+String(ntu));
  //Serial.println(ntu);
  
  delay(1000);  // Wait for 1 second before taking the next reading
}

// Function to convert sensor reading to NTU using linear interpolation
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
