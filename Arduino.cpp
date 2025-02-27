#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Pin Definitions
#define LDR_PIN A0          // Pin for LDR (analog pin)
#define BUZZER_PIN 9        // Pin for Buzzer
#define SAFE_LIMIT_LOW 200  // Minimum safe light intensity
#define SAFE_LIMIT_HIGH 800 // Maximum safe light intensity

// LCD Setup
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // Initialize LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("LDR Monitoring");
  delay(2000);
  lcd.clear();

  // Initialize pins
  pinMode(LDR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  // Start serial communication
  Serial.begin(9600);
  Serial.println("Arduino LDR & Buzzer Project");
}

void loop() {
  // Read LDR value
  int ldrValue = analogRead(LDR_PIN);
  Serial.print("LDR Value: ");
  Serial.println(ldrValue);

  // Check for circuit disconnection
  if (ldrValue == 0) { // A value of 0 typically indicates disconnection
    handleConnectionFault();
    return; // Skip the rest of the loop until circuit is reconnected
  }

  // Display LDR value on LCD
  lcd.setCursor(0, 0);
  lcd.print("LDR Value: ");
  lcd.print(ldrValue);
  lcd.print("    "); // Clear extra characters

  // Check for light intensity conditions
  if (ldrValue < SAFE_LIMIT_LOW) {
    // If light intensity is below the minimum safe limit
    lcd.setCursor(0, 1);
    lcd.print("High Intensity! ");
    soundBuzzerForCondition();
  } else if (ldrValue > SAFE_LIMIT_HIGH) {
    // If light intensity exceeds the maximum safe limit
    lcd.setCursor(0, 1);
    lcd.print("Low Intensity!");
    soundBuzzerForCondition();
  } else {
    // Normal operation
    lcd.setCursor(0, 1);
    lcd.print("Intensity Normal");
    digitalWrite(BUZZER_PIN, LOW); // Turn off the buzzer
  }

  delay(500); // Delay for stability
}

// Function to handle connection fault
void handleConnectionFault() {
  Serial.println("Circuit Disconnected! Triggering Alarm...");
  lcd.clear();

  while (true) {
    int ldrValue = analogRead(LDR_PIN); // Continuously check LDR value
    if (ldrValue > 0) {
      // Circuit reconnected
      lcd.clear();
      Serial.println("Circuit Reconnected.");
      break;
    }

    // Display blinking "Circuit Disconnected!!" message
    lcd.setCursor(0, 0);
    lcd.print("Circuit");
    lcd.setCursor(0, 1);
    lcd.print("Disconnected!!");
    digitalWrite(BUZZER_PIN, HIGH);
    delay(500);

    lcd.clear();
    digitalWrite(BUZZER_PIN, LOW);
    delay(500);
  }
}

// Function to make the buzzer beep for abnormal conditions
void soundBuzzerForCondition() {
  digitalWrite(BUZZER_PIN, HIGH); // Turn on the buzzer
  delay(200);                     // Beep duration
  digitalWrite(BUZZER_PIN, LOW);  // Turn off the buzzer
  delay(200);                     // Pause before next check
}
