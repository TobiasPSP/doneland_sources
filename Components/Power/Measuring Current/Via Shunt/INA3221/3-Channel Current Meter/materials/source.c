#include <Wire.h>
#include <INA3221.h>

INA3221 powerMonitor;

void setup() {
  Wire.begin(); // Start I2C bus
  Serial.begin(9600); // Start serial communication at 9600 baud

  powerMonitor.begin(); // Initialize INA3221
  powerMonitor.setShuntResistor(0, 0.1); // Set shunt resistor value for channel 1
  // Repeat for other channels as needed
}

void loop() {
  float shuntVoltage = powerMonitor.getShuntVoltage(0); // Read shunt voltage on channel 1
  float busVoltage = powerMonitor.getBusVoltage(0); // Read bus voltage on channel 1
  float current = powerMonitor.getCurrent(0); // Read current on channel 1

  // Output the measurements
  Serial.print("Shunt Voltage: "); Serial.print(shuntVoltage); Serial.println(" mV");
  Serial.print("Bus Voltage: "); Serial.print(busVoltage); Serial.println(" V");
  Serial.print("Current: "); Serial.print(current); Serial.println(" mA");

  delay(1000); // Wait for 1 second before next reading
}