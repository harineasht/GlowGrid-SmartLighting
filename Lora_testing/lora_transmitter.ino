// Code for Transmitter using ESP 32 and pushbutton
#include <LoRa_E220.h>

#define LORA_RX 16
#define LORA_TX 17
#define PIN_M0 25
#define PIN_M1 26
#define PIN_AUX 27

#define BUTTON_PIN 4   // Push button pin

HardwareSerial LoRaSerial(2);
LoRa_E220 e220(&LoRaSerial, PIN_M0, PIN_M1, PIN_AUX);

bool lastButtonState = HIGH;

void setup() {
  Serial.begin(115200);
  delay(500);

  pinMode(BUTTON_PIN, INPUT_PULLUP);  // ✅ Internal pull-up enabled

  Serial.println("\n--- LoRa TRANSMITTER (BUTTON) ---");

  LoRaSerial.begin(9600, SERIAL_8N1, LORA_RX, LORA_TX);
  e220.begin();

  e220.setMode(MODE_0_NORMAL);

  Serial.println("Press button to send signal...");
}

void loop() {

  bool currentState = digitalRead(BUTTON_PIN);

  // Detect button press (HIGH → LOW transition)
  if (lastButtonState == HIGH && currentState == LOW) {

    String msg = "BUTTON_PRESSED";

    ResponseStatus rs = e220.sendMessage(msg);

    Serial.print("Sent: ");
    Serial.print(msg);
    Serial.print(" | Status: ");
    Serial.println(rs.getResponseDescription());
  }

  lastButtonState = currentState;

  delay(50);  // small debounce
}