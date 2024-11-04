//  // 8.  People Counter with Direction Detection:
//  // Place an IR sensor on either side of a doorway to count the number of people entering and exiting.
//  // Display the count on a 7-segment display. 
//  // Use the ultrasonic sensor to confirm direction by measuring the time an object passes between the two IR sensors




// IR Sensor Pins
#define ir_s1 A0 // IR Sensor 1 (entry sensor) 
#define ir_s2 A1 // IR Sensor 2 (exit sensor) 

// Ultrasonic Sensor Pins
#define triggerPin A2  // Trigger pin
#define echoPin A3     // Echo pin






// 7-Segment Display Pins
const int segmentPins[7] = {2, 3, 4, 5, 6, 7, 8};  // Pins connected to a, b, c, d, e, f, g
const int digitPins[4] = {9, 10, 11, 12};          // Pins for D1, D2, D3, D4

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

int person = 0; // Initialize person counter
int flag1 = 0, flag2 = 0; // Flags for IR sensor states

// Function to clear all digits
void clearDisplay() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(digitPins[i], HIGH);
  }
}

// Function to display a digit at a specified position
void displayDigit(int digit, int position) {
  // Set segment pins
  for (int i = 0; i < 7; i++) {
    digitalWrite(segmentPins[i], (digits[digit] >> i) & 0x01);
  }
  // Activate the selected digit position
  digitalWrite(digitPins[position], LOW);
  delay(1);  // Small delay to stabilize display
  digitalWrite(digitPins[position], HIGH);
}

void setup() {
  Serial.begin(9600);

  // Initialize IR sensor pins
  pinMode(ir_s1, INPUT);
  pinMode(ir_s2, INPUT);

  // Initialize 7-segment display pins
  for (int i = 0; i < 7; i++) {
    pinMode(segmentPins[i], OUTPUT);
  }
  for (int i = 0; i < 4; i++) {
    pinMode(digitPins[i], OUTPUT);
    digitalWrite(digitPins[i], HIGH);  // Turn off all digits
  }

  // Initialize ultrasonic sensor pins
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // Trigger the ultrasonic sensor
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  // Measure the time duration of the pulse
  long duration = pulseIn(echoPin, HIGH);

  // Convert the duration to distance in centimeters
  long distance = duration * 0.034 / 2;

  // Check if the distance is less than 200 cm
  if (distance < 200) {
    int sensor1 = digitalRead(ir_s1); // Read IR Sensor 1
    int sensor2 = digitalRead(ir_s2); // Read IR Sensor 2

    // Detect entry
    if (sensor1 == LOW && flag1 == 0) { // Person detected at entry sensor
      flag1 = 1;
      if (flag2 == 0) {
        person += 1;
        Serial.print("Entry detected. Person count: ");
        Serial.println(person);
      }
    }

    // Detect exit
    if (sensor2 == LOW && flag2 == 0) { // Person detected at exit sensor
      flag2 = 1;
      if (flag1 == 0 && person > 0) {
        person -= 1;
        Serial.print("Exit detected. Person count: ");
        Serial.println(person);
      }
    }

    // Reset flags after person has moved past both sensors
    if (sensor1 == HIGH && sensor2 == HIGH && flag1 == 1 && flag2 == 1) {
      flag1 = 0;
      flag2 = 0;
    }

    // Extract digits for display
    int hundreds = (person / 100) % 10;
    int tens = (person / 10) % 10;
    int units = person % 10;

    // Display the count on the 4-digit 7-segment display
    for (int i = 0; i < 50; i++) {  // Refresh display quickly to show all digits
      clearDisplay();
      if (hundreds > 0) {  // Display hundreds place only if non-zero
        displayDigit(hundreds, 0);
      }
      displayDigit(tens, 1);
      displayDigit(units, 2);
    }
  } else {
    // If distance is greater than 200 cm, skip counting
    Serial.println("Ultrasonic distance is greater than 200 cm. Skipping count update.");
  }

  delay(100); // Small delay to prevent bouncing
}
