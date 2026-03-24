#include <LoRa_E220.h>

#define LORA_RX 16

#define LORA_TX 17

#define PIN_M0 25

#define PIN_M1 26

#define PIN_AUX 27


HardwareSerial LoRaSerial(2);

LoRa_E220 e220(&LoRaSerial, PIN_M0, PIN_M1, PIN_AUX);


void setup() {

  Serial.begin(9600);

  delay(500);


  Serial.println("\n--- LoRa RECEIVER ---");


  LoRaSerial.begin(9600, SERIAL_8N1, LORA_RX, LORA_TX);

  e220.begin();

  e220.setMode(MODE_0_NORMAL);


  Serial.println("Receiver ready. Waiting for messages...");

}


void loop() {

  if (e220.available() > 0) {

    ResponseContainer rc = e220.receiveMessage();

    if (rc.status.code == E220_SUCCESS) {

      Serial.print("Received: ");

      Serial.println(rc.data);

    } else {

      Serial.print("Receive error: ");

      Serial.println(rc.status.getResponseDescription());

    }

  }

}