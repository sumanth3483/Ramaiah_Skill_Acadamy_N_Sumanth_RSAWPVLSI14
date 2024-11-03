
#include "seven_segment.h"

// Ultrasonic sensor pins
const int trigPin = A0; // Trigger pin on A0
const int echoPin = A1; //

void setup() {
  // Initialize 7-segment display
  sevenSegmentInit(2, 3, 4, 5, 6, 7, 8, 0, 9, 10, 11, 12);

  // Set up ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // Get the distance from the ultrasonic sensor
  long duration, distance;
  
  // Trigger the ultrasonic pulse
  digitalWrite(trigPin, LOW);
  // delayMicroseconds(1);
  delay(1);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echo and calculate distance
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2; // Convert to cm

  // Limit the display to 4 digits
  int num = distance % 10000;

  // Display the distance on the 7-segment display
  int segment = 0;
  do {
    selectSegment(++segment);
    sevenSegmentDisplay(getDigit(num));
  } while ((num /= 10) != 0);
}
