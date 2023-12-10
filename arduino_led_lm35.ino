#include <elapsedMillis.h>

const int tempSensorPin = A0; // Analog pin for LM35 temperature sensor
const int ledPin = 13;        // Digital pin for onboard LED

const int tempThreshold = 30;  // Temperature threshold in degrees Celsius
int blinkInterval = 500;       // Initial blink interval
const int blinkStep = 50;      // Step for adjusting blink interval

elapsedMillis blinkTimer;      // Timer for LED blinking

void setup() {
  pinMode(tempSensorPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int currentTemp = readTemperature();

  if (currentTemp < tempThreshold) {
    blinkLED(blinkInterval);
  } else {
    adjustBlinkInterval(currentTemp);
    blinkLED(blinkInterval);
  }
}

int readTemperature() {
  // Read analog value from LM35 temperature sensor
  int sensorValue = analogRead(tempSensorPin);

  // Convert analog value to temperature in degrees Celsius
  float temperature = (sensorValue * 0.48828125);

  return static_cast<int>(temperature);
}

void blinkLED(int interval) {
  if (blinkTimer >= interval) {
    digitalWrite(ledPin, !digitalRead(ledPin));  // Toggle LED state
    blinkTimer = 0;  // Reset timer
  }
}

void adjustBlinkInterval(int currentTemp) {
  if (currentTemp > tempThreshold && blinkInterval > blinkStep) {
    // Increase blink interval when temperature rises above the threshold
    blinkInterval -= blinkStep;
  } else if (currentTemp < tempThreshold && blinkInterval < 1000) {
    // Decrease blink interval when temperature falls below the threshold
    blinkInterval += blinkStep;
  }
}