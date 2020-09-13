/***************************************************************************
* Example sketch for the INA226_WE library
*
* This sketch is based on the continuous mode example but uses the function setResistorRange to set a different resistor value. 
*  
* This setup uses two stromsensor6mm boards with a 5 mOhm shunt resistor each
* More information on this board can be found here: https://github.com/generationmake/stromsensor6mm
* 
***************************************************************************/
#include <Wire.h>
#include <INA226_WE.h>

INA226_WE ina226_1(0x40);
INA226_WE ina226_2(0x41);

void setup() {
  Serial.begin(9600);
  while(!Serial); // wait until serial comes up on Arduino Leonardo or MKR WiFi 1010
  Wire.begin();
  ina226_1.init();
  ina226_2.init();

  ina226_1.setResistorRange(0.005,10.0); // choose resistor 5 mOhm and gain range up to 10 A
  ina226_2.setResistorRange(0.005,4.0); // choose resistor 5 mOhm and gain range up to 4 A
    
  Serial.println("INA226 Current Sensor Example Sketch with two stromsensor6mm boards");
  
  ina226_1.waitUntilConversionCompleted(); //if you comment this line the first data might be zero
  ina226_2.waitUntilConversionCompleted(); //if you comment this line the first data might be zero
}

void loop() {
  float shuntVoltage_mV = 0.0;
  float loadVoltage_V = 0.0;
  float busVoltage_V = 0.0;
  float current_mA = 0.0;
  float power_mW = 0.0; 

  ina226_1.readAndClearFlags();
  shuntVoltage_mV = ina226_1.getShuntVoltage_mV();
  busVoltage_V = ina226_1.getBusVoltage_V();
  current_mA = ina226_1.getCurrent_mA();
  power_mW = ina226_1.getBusPower();
  loadVoltage_V  = busVoltage_V + (shuntVoltage_mV/1000);
  
  Serial.println("[1] INA226 on stromsensor6mm board 1");
  Serial.print("[1] Shunt Voltage [mV]: "); Serial.println(shuntVoltage_mV);
  Serial.print("[1] Bus Voltage [V]: "); Serial.println(busVoltage_V);
  Serial.print("[1] Load Voltage [V]: "); Serial.println(loadVoltage_V);
  Serial.print("[1] Current[mA]: "); Serial.println(current_mA);
  Serial.print("[1] Bus Power [mW]: "); Serial.println(power_mW);
  if(!ina226_1.overflow){
    Serial.println("[1] Values OK - no overflow");
  }
  else{
    Serial.println("[1] Overflow! Choose higher current range");
  }
  Serial.println();
  
  ina226_2.readAndClearFlags();
  shuntVoltage_mV = ina226_2.getShuntVoltage_mV();
  busVoltage_V = ina226_2.getBusVoltage_V();
  current_mA = ina226_2.getCurrent_mA();
  power_mW = ina226_2.getBusPower();
  loadVoltage_V  = busVoltage_V + (shuntVoltage_mV/1000);
  
  Serial.println("[2] INA226 on stromsensor6mm board 2");
  Serial.print("[2] Shunt Voltage [mV]: "); Serial.println(shuntVoltage_mV);
  Serial.print("[2] Bus Voltage [V]: "); Serial.println(busVoltage_V);
  Serial.print("[2] Load Voltage [V]: "); Serial.println(loadVoltage_V);
  Serial.print("[2] Current[mA]: "); Serial.println(current_mA);
  Serial.print("[2] Bus Power [mW]: "); Serial.println(power_mW);
  if(!ina226_2.overflow){
    Serial.println("[2] Values OK - no overflow");
  }
  else{
    Serial.println("[2] Overflow! Choose higher current range");
  }
  Serial.println();
  
  delay(3000);
}
