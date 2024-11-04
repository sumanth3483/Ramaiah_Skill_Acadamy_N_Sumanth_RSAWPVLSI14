#include "seven_segment.h"

// Ultrasonic sensor pins
const int trigPin = A0; // Trigger pin
const int echoPin = A1; // Echo pin
const int touchPin = A2; // Touch sensor pin

int counter = 0;                 // Counter to track the count value
const int distanceThreshold = 100; // Distance threshold in cm
const int touchThreshold = 160;    // Touch threshold for resetting

void setup() {
  // Initialize 7-segment display with pins (2-8 for segments, 0 for DP, 9-12 for digits)
  sevenSegmentInit(2, 3, 4, 5, 6, 7, 8, 0, 9, 10, 11, 12);
  // sevenSegmentInit(12, 11, 10, 9, 8, 7, 6, 0, 5, 4, 3, 2);

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
    
    // Ensure to display the correct digit
    sevenSegmentDisplay(getDigit(digits[segment - 1]));
    delay(15); // Short delay for stable multiplexing
  }
}

void loop() {
  // Get sensor readings
  long distance = getDistance();
  int touchValue = analogRead(touchPin);

  // Debugging: Print values to the serial monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm, Touch Value: ");
  Serial.println(touchValue);

  // Reset counter if touch value exceeds threshold
  if (touchValue > touchThreshold) {
    counter = 0; // Reset counter
  }
  // Start counting if distance is below threshold and touch is below threshold
  else if (distance < distanceThreshold && touchValue < touchThreshold) {
    counter++;
    if (counter > 9999) { // Ensure the counter doesn't exceed 999
      counter = 0; // Reset to zero if it exceeds
    }
    delay(1); // Delay to avoid rapid increment
  }

  // Display the counter value on the 4-digit 7-segment display
  displayCount(counter);
}
