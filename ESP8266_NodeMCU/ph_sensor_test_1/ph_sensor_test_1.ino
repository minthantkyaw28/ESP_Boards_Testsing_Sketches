
// Arduino pH meter code

// Import the necessary libraries
#include <Arduino.h>
#include <math.h>

// Define the calibration value
float calibration_value = 21.5;

// Define the buffer array
int buffer_arr[10];

// Define the average value
unsigned long int avgval;

// Define the pH value
float ph_act;

// Setup function
void setup() {
  // Initialize the serial port
  Serial.begin(115200);

  // Print a welcome message
  Serial.println("Arduino pH meter");
}

// Loop function
void loop() {
  // Read the analog input from A1
  for (int i = 0; i < 10; i++) {
    buffer_arr[i] = analogRead(A0);
    delay(30);
  }

  // Sort the readings
  for (int i = 0; i < 9; i++) {
    for (int j = i + 1; j < 10; j++) {
      if (buffer_arr[i] > buffer_arr[j]) {
        int temp = buffer_arr[i];
        buffer_arr[i] = buffer_arr[j];
        buffer_arr[j] = temp;
      }
    }
  }

  // Calculate the average reading
  avgval = 0;
  for (int i = 2; i < 8; i++) {
    avgval += buffer_arr[i];
  }

  // Calculate the pH value
  float volt = (float)avgval * 5.0 / 1023 / 6;
  ph_act = -5.70 * volt + calibration_value;

  // Print the pH value to the serial port
  Serial.print("pH Val: ");
  Serial.println(ph_act/3);

  // Delay for 1 second
  delay(1000);
}
