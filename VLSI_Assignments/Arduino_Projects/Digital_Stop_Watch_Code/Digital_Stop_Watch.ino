#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

const int startStopButton = 8;
const int resetButton = 9;

unsigned long startTime = 0;
double elapsedTime = 0;
bool timing = false;
bool lastStartStopState = HIGH;

void setup() {
    lcd.begin(16, 2);
    lcd.clear();
    lcd.print("Press Start");

    pinMode(startStopButton, INPUT_PULLUP);
    pinMode(resetButton, INPUT_PULLUP);

    Serial.begin(9600);
}

void loop() {
    bool startStopState = digitalRead(startStopButton);

    if (startStopState == LOW && lastStartStopState == HIGH) {
        delay(50);
        if (!timing) {
            startTime = millis();
            timing = true;
            lcd.clear();
            lcd.print("Timing...");
        } else {
            timing = false;
        }
    }
    lastStartStopState = startStopState;

    if (digitalRead(resetButton) == LOW && !timing) {
        elapsedTime = 0;
        lcd.clear();
        lcd.print("Press Start");
        delay(500);
    }

    if (timing) {
        unsigned long currentTime = millis();
        elapsedTime = (currentTime - startTime) / 1000.0;

        lcd.setCursor(0, 1);
        lcd.print("Time: ");
        lcd.print(elapsedTime);
        lcd.print(" sec   ");
    } else if (elapsedTime > 0) {
        lcd.setCursor(0, 1);
        lcd.print("Final: ");
        lcd.print(elapsedTime);
        lcd.print(" sec   ");
    }
}


// #include <LiquidCrystal.h>

// // Initialize LCD with RS, E, D4, D5, D6, D7 pin connections
// LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

// void setup() {
//     // Set up the LCD's number of columns and rows
//     lcd.begin(16, 2);
    
//     // Display "Hello, World!" on the LCD
//     lcd.print("Hello, World!");
// }

// void loop() {
//     // Nothing needed here for static display
// }



