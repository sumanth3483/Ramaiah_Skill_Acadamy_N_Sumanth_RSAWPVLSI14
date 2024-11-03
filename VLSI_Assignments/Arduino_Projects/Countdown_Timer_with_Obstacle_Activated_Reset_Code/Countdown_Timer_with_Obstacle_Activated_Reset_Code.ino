

//  //perfectly WORKING 4.	Countdown Timer with Obstacle-Activated Reset:
//  //Use the touch sensor to start a countdown on the 7-segment display. 
//  //If the ultrasonic sensor detects an obstacle (within a specified range) during the countdown, reset the timer.
//  // Display "E" on the display if the countdown completes without interruption.


#define TRIG_PIN A0    // Define TRIG pin as A0
#define ECHO_PIN A1    // Define ECHO pin as A1
#define TOUCH_PIN A2   // Define TOUCH pin as A2

const int segmentPins[7] = {2, 3, 4, 5, 6, 7, 8};  // Pins connected to a, b, c, d, e, f, g
const int digitPins[4] = {9, 10, 11, 12};           // Pins for D1, D2, D3, D4

// Digit patterns for numbers 0-9 (common cathode)
const byte digits[10] = {
  0b00111111, // 0
  0b00000110, // 1
  0b01011011, // 2
  0b01001111, // 3
  0b01100110, // 4
  0b01101101, // 5
  0b01111101, // 6
  0b00000111, // 7
  0b01111111, // 8
  0b01101111  // 9
};

// Digit pattern for letter 'E'
const byte letterE = 0b01111001; // Segments a, f, g, e, d

// Function to clear all digits
void clearDisplay() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(digitPins[i], HIGH);
  }
}

// Function to display a digit at a specified position
void displayDigit(int digit, int position) {
  for (int i = 0; i < 7; i++) {
    digitalWrite(segmentPins[i], (digits[digit] >> i) & 0x01);
  }
  digitalWrite(digitPins[position], LOW);
  delay(1);  // Small delay to stabilize display
  digitalWrite(digitPins[position], HIGH);
}

// Function to display the letter 'E' on a specified position
void displayLetterE(int position) {
  for (int i = 0; i < 7; i++) {
    digitalWrite(segmentPins[i], (letterE >> i) & 0x01);
  }
  digitalWrite(digitPins[position], LOW);
  delay(1);  // Short delay to stabilize display
  digitalWrite(digitPins[position], HIGH);
}

void setup() {
  for (int i = 0; i < 7; i++) {
    pinMode(segmentPins[i], OUTPUT);
  }
  for (int i = 0; i < 4; i++) {
    pinMode(digitPins[i], OUTPUT);
    digitalWrite(digitPins[i], HIGH);  // Turn off all digits initially
  }

  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(TOUCH_PIN, INPUT);
}

void loop() {
  // Read ultrasonic distance
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  long duration = pulseIn(ECHO_PIN, HIGH);
  float distance = duration * 0.034 / 2; // Speed of sound is ~0.034 cm/µs

  // Read touch sensor value
  int touchValue = analogRead(TOUCH_PIN);

  // Display distance and touch sensor value in Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm\tTouch Sensor Value: ");
  Serial.println(touchValue);

  // Conditions to control the countdown
  static int count = 100;

  if (touchValue < 160) {
    // Stop the counter if touch value is less than 160
    return;
  }

  if (distance < 150) {
    // Reset the counter if ultrasonic distance is less than 150
    count = 100;
    return;
  }

  // Decrement counter from 100 to 0 on 7-segment display
  if (count >= 0) {
    int hundreds = (count / 100) % 10;
    int tens = (count / 10) % 10;
    int units = count % 10;

    // Display the count on 4-digit 7-segment display
    for (int i = 0; i < 50; i++) {
      clearDisplay();
      if (hundreds > 0) {
        displayDigit(hundreds, 0);
      }
      displayDigit(tens, 1);
      displayDigit(units, 2);
    }

    // If count reaches 0, display 'E' on D4
    if (count == 0) {
      for (int i = 0; i < 50; i++) {
        clearDisplay();
        displayLetterE(3); // Display 'E' on D4
        delay(10000);
      }
    }

    count--; // Decrement count
  }
}
