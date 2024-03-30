/*
  this example was slightly adaped from the many examples published here: https://wolles-elektronikkiste.de/ina226
*/

#include <Arduino.h>
#include <Wire.h>
#include <INA226_WE.h>       
#define I2C_ADDRESS 0x40    // I2C address, can be adjusted via solder bridges on breakout board

INA226_WE ina226 = INA226_WE(I2C_ADDRESS);

void setup() {
  // adjust the baud rate to match your setting in platform.ini or your IDE:
  Serial.begin(115200);
  Wire.begin();
  ina226.init();

  /* by default, a R100 shunt resistor is expected
     for breakout boards with R010, uncomment line below:
  */
  //ina226.setResistorRange(0.01, 8.0);
  
  /* fine-tune current measurements by adding a correction factor
     Calculate factor as follows:
     factor = real current / INA226 measured current
  */
  //ina226.setCorrectionFactor(0.8877);
  
  /* how many samples should be combined and averaged?
  Reporting back individual measurements (default) is *not* recommended as
  values may vary due to noise and other factors.
  The higher the sample rate the more resilient are measurements but the less responsive are the results
  
  Possible values:
  AVERAGE_1            1 (default)
  AVERAGE_4            4
  AVERAGE_16          16
  AVERAGE_64          64
  AVERAGE_128        128
  AVERAGE_256        256
  AVERAGE_512        512
  AVERAGE_1024      1024
  */
  ina226.setAverage(AVERAGE_128); // use at least a few samples to average in order to cut out noise and erratic values

  /* Set conversion time in microseconds
     Required time to read a value:
     Samples to be averaged x conversion time x 2
     
     * Mode *         * conversion time *
     CONV_TIME_140          140 µs
     CONV_TIME_204          204 µs
     CONV_TIME_332          332 µs
     CONV_TIME_588          588 µs
     CONV_TIME_1100         1.1 ms (default)
     CONV_TIME_2116       2.116 ms
     CONV_TIME_4156       4.156 ms
     CONV_TIME_8244       8.244 ms  
  */
  ina226.setConversionTime(CONV_TIME_8244); // if measurement is not time critical, choose a high value
  
  /* Available measurement modes:
  POWER_DOWN - INA226 switched off
  TRIGGERED  - measurement on demand
  CONTINUOUS  - continuous measurements (default)
  */
  //ina226.setMeasureMode(TRIGGERED); // uncomment if you want to manually trigger single measurements
  
  Serial.println("Test starts.");
  
  // read one set of data
  ina226.waitUntilConversionCompleted(); 
}

void loop() {
  float shuntVoltage_mV = 0.0;
  float loadVoltage_V = 0.0;
  float busVoltage_V = 0.0;
  float current_mA = 0.0;
  float power_mW = 0.0; 

  ina226.readAndClearFlags();
  shuntVoltage_mV = ina226.getShuntVoltage_mV();
  busVoltage_V = ina226.getBusVoltage_V();
  current_mA = ina226.getCurrent_mA();
  power_mW = ina226.getBusPower();
  loadVoltage_V  = busVoltage_V + (shuntVoltage_mV/1000);
  
  Serial.print("Shunt Voltage [mV]: "); Serial.println(shuntVoltage_mV);
  Serial.print("Bus Voltage [V]: "); Serial.println(busVoltage_V);
  Serial.print("Load Voltage [V]: "); Serial.println(loadVoltage_V);
  Serial.print("Current[mA]: "); Serial.println(current_mA);
  Serial.print("Bus Power [mW]: "); Serial.println(power_mW);
  if(ina226.overflow) {
    Serial.println("Overflow! Choose higher current range");
  }
  else {
    Serial.println("Values OK - no overflow");
  }
  Serial.println();
  
   //print results every 2 seconds:
  delay(2000);
}