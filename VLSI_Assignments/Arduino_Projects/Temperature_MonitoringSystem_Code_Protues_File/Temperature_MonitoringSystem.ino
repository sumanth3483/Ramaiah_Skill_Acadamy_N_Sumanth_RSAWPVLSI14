

#define LM35_PIN A0         

float temperature;
const float threshold = 30.0; 

void setup() {
  Serial.begin(9600);
  
  
 

  pinMode(LM35_PIN, INPUT);
  pinMode(3, OUTPUT);
}

void loop() {
  
  int sensorValue = analogRead(LM35_PIN);
  float voltage = sensorValue * (5.0 / 1023.0);
  temperature = voltage * 100.0;  
  if (isnan(temperature)) {
    Serial.println("Error reading temperature!");
    digitalWrite (3, LOW);
  } else {
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");

    
    if (temperature > threshold) {
      Serial.println("Warning: Temperature exceeds threshold!");
      digitalWrite (3, HIGH);
    }
  }

  delay(1000);
}
