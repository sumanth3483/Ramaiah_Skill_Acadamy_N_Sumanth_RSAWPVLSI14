#include "seven_segment.h"

// Ultrasonic sensor pins
const int trigPin = A0; // Trigger pin
const int echoPin = A1; // Echo pin
const int touchPin = A2; // Touch sensor pin

void setup() {
  // Initialize 7-segment display with pins (2-8 for segments, 0 for DP, 9-12 for digits)
  // sevenSegmentInit(2, 3, 4, 5, 6, 7, 8, 0, 9, 10, 11, 12);
  sevenSegmentInit(12, 11, 10, 9, 8, 7, 6, 0, 5, 4, 3, 2);

  // Set up ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Set up touch sensor pin
  pinMode(touchPin, INPUT);

  // Start serial communication for debugging
  Serial.begin(9600);
}

long getDistance() {
  // Trigger ultrasonic pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echo pulse and calculate distance
  long duration = pulseIn(echoPin, HIGH);
  long distance = duration * 0.034 / 2; // Convert to cm
  return distance;
}

void displayCount(int count) {
  int digits[4] = {0, 0, 0, 0};  // Array to store each digit

  // Separate the count into individual digits
  for (int i = 3; i >= 0; i--) {
    digits[i] = count % 10;
    count /= 10;
  }

  // Display each digit on the respective 7-segment display (D1 to D4)
  for (int segment = 1; segment <= 4; segment++) {
    selectSegment(segment);
    sevenSegmentDisplay(getDigit(digits[segment - 1]));
    // delay(); // Short delay for stable multiplexing
    delayMicroseconds(2);
  }
}

void loop() {
  int touchValue = analogRead(touchPin);

  // Debugging: Print touch value to the serial monitor
  Serial.print("Touch Value: ");
  Serial.println(touchValue);

  // Check if the touch sensor is activated
  if (touchValue > 160) { // Adjust threshold as needed
    long distance = getDistance(); // Get distance measurement
    displayCount(distance); // Display the measured distance
    Serial.print(distance);

    // Hold the value for 5 seconds
    delay(500); 

    // Clear the display after 5 seconds
    displayCount(0); // Optionally clear by displaying 0000
  }

  delay(100); // Short delay to avoid rapid polling of the touch sensor
}




