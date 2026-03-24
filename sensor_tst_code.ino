#define VOLTAGE_SENSOR_PIN 34
#define CURRENT_SENSOR_PIN 35

void setup() {
  Serial.begin(115200);
  delay(2000);  // skip boot messages

  Serial.println("Sensor Test Started...");
}

void loop() {

  int rawVoltage = analogRead(VOLTAGE_SENSOR_PIN);
  int rawCurrent = analogRead(CURRENT_SENSOR_PIN);

  float voltagePin = (rawVoltage / 4095.0) * 3.3;
  float currentPin = (rawCurrent / 4095.0) * 3.3;

  Serial.print("Voltage Sensor -> Raw: ");
  Serial.print(rawVoltage);
  Serial.print(" | Pin Voltage: ");
  Serial.print(voltagePin, 3);
  Serial.print(" V   ||   ");

  Serial.print("Current Sensor -> Raw: ");
  Serial.print(rawCurrent);
  Serial.print(" | Pin Voltage: ");
  Serial.print(currentPin, 3);
  Serial.println(" V");

  delay(1000);
}