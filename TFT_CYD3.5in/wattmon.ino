#include <TFT_eSPI.h>
#include <math.h>

TFT_eSPI tft = TFT_eSPI();

const int SHUNT_PIN = 35;    // ADC pin for shunt
const float SHUNT_RESISTANCE = 0.00075; // Shunt resistance in ohms
const float ADC_MAX_VOLTAGE = 3.3;     // Max voltage for ESP32 ADC
const int ADC_RESOLUTION = 4095;       // ESP32 ADC resolution

const float HARD_CODED_VOLTAGE = 12.0; // Hardcoded DC voltage
const float MAX_POWER = 1000.0;        // Maximum power for gauge scaling

float current = 0.0;
float power = 0.0;

void setup() {
  tft.begin();
  tft.setRotation(1); // Landscape mode
  tft.fillScreen(TFT_BLACK);

  // Load a smoother font (if supported)
  tft.setTextFont(2);  // Set a smoother, built-in font like FreeSerif12 or FreeMonoBold9
  tft.setTextColor(TFT_WHITE, TFT_BLACK); // White text on black background
  tft.setTextDatum(MC_DATUM); // Center alignment for text
}

void drawSmoothGauge(float value, float maxValue) {
  // Gauge parameters
  int centerX = 240; // Center of screen (x)
  int centerY = 160; // Center of screen (y)
  int radius = 140;  // Radius of the gauge (smaller for smoother)
  int thickness = 20; // Thickness of the gauge arc
  int startAngle = -180; // Start angle of arc
  int endAngle = 180;    // End angle of arc

  // Draw the background arc (gray with smoother color)
  for (int angle = startAngle; angle <= endAngle; angle++) {
    float xStart = centerX + (radius - thickness) * cos(radians(angle));
    float yStart = centerY + (radius - thickness) * sin(radians(angle));
    float xEnd = centerX + radius * cos(radians(angle));
    float yEnd = centerY + radius * sin(radians(angle));
    tft.drawLine(xStart, yStart, xEnd, yEnd, TFT_DARKGREY);
  }

  // Draw the value arc (gradient from green → yellow → red)
  float normalizedValue = constrain(value / maxValue, 0.0, 1.0);
  for (int angle = startAngle; angle <= startAngle + normalizedValue * (endAngle - startAngle); angle++) {
    uint16_t color;
    if (angle < startAngle + (endAngle - startAngle) * 0.5) {
      color = tft.color565(0, 255, 0); // Green
    } else if (angle < startAngle + (endAngle - startAngle) * 0.75) {
      color = tft.color565(255, 255, 0); // Yellow
    } else {
      color = tft.color565(255, 0, 0); // Red
    }

    float xStart = centerX + (radius - thickness) * cos(radians(angle));
    float yStart = centerY + (radius - thickness) * sin(radians(angle));
    float xEnd = centerX + radius * cos(radians(angle));
    float yEnd = centerY + radius * sin(radians(angle));
    tft.drawLine(xStart, yStart, xEnd, yEnd, color);
  }

  // Clear the center of the gauge
  tft.fillCircle(centerX, centerY, radius - thickness, TFT_BLACK);

  // Display the power value in the center with smoother font
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextDatum(MC_DATUM); // Center alignment

  // Adjust text size for better clarity
  if (value >= 1000.0) {
    tft.setTextSize(3);
    tft.drawString(String(value / 1000.0, 1) + " kW", centerX, centerY - 20); // Display in kW (1 decimal place)
    tft.setTextSize(2);
    tft.drawString("Kilowatt", centerX, centerY + 20); // Display "Kilowatt" text
  } else {
    tft.setTextSize(4); // Slightly larger font
    tft.drawString(String(value, 0) + " W", centerX, centerY - 20); // Display in W (rounded to 0 decimal)
    tft.setTextSize(2);
    tft.drawString("Watt", centerX, centerY + 20); // Display "Watt" text
  }
}

void loop() {
  // Read current from shunt
  int shuntRaw = analogRead(SHUNT_PIN);

  // Convert ADC reading to current
  float shuntVoltage = (shuntRaw / float(ADC_RESOLUTION)) * ADC_MAX_VOLTAGE; // Voltage across shunt
  current = shuntVoltage / SHUNT_RESISTANCE; // Calculate current

  // Calculate power
  power = HARD_CODED_VOLTAGE * current;

  // Draw the gauge
  drawSmoothGauge(power, MAX_POWER);

  delay(100); // Small delay for refresh
}
