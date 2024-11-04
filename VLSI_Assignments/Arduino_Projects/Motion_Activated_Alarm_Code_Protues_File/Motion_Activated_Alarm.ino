
int Status = 13;  // Status LED pin (optional, can be removed if not needed)
int buzzerPin = 9; // Buzzer pin
int sensor = 12;   // PIR motion sensor pin

void setup() {
  Serial.begin(9600);
  pinMode(sensor, INPUT);   // Declare PIR sensor as input
  pinMode(buzzerPin, OUTPUT); // Declare buzzer as output
  pinMode(Status, OUTPUT);  // Declare LED as output (optional)
}

void loop() {
  long state = digitalRead(sensor);
  
  Serial.println(state); // Print sensor state to Serial Monitor
  
  if (state == HIGH) {
    digitalWrite(buzzerPin, HIGH); // Sound the buzzer
    Serial.print("Motion detected at: ");
    Serial.print(millis() / 1000); // Log timestamp in seconds
    Serial.println(" seconds");
    delay(50); // Wait to avoid multiple triggers
  } else {
    digitalWrite(buzzerPin, LOW); // Turn off the buzzer
    Serial.println("Motion absent!");
    delay(100); // Delay for readability
  }
}
