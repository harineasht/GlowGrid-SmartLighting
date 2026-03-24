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

  Serial.println("\n--- UNIVERSAL E220 CONFIGURATOR ---\n");


  LoRaSerial.begin(9600, SERIAL_8N1, LORA_RX, LORA_TX);


  e220.begin();


  // Put in Config mode

  e220.setMode(MODE_3_PROGRAM); 

  delay(100);


  // Read current config

  ResponseStructContainer c = e220.getConfiguration();

  if (c.status.code != E220_SUCCESS) {

    Serial.print("Read error: ");

    Serial.println(c.status.getResponseDescription());

    return;

  }


  Configuration cfg = *(Configuration*) c.data;

  c.close();


  Serial.println("Old settings:");

  Serial.print("Address: "); Serial.print(cfg.ADDH, HEX); Serial.print(cfg.ADDL, HEX);

  Serial.print("\nChannel: "); Serial.println(cfg.CHAN);

  

  // ---- CHANGE ONLY WHAT IS SAFE AND UNIVERSAL ----

  cfg.ADDH = 0x00;  

  cfg.ADDL = 0x00;  

  cfg.CHAN = 17;      // 867 MHz


  // UART + Air rate (safe defaults)

  cfg.SPED.uartBaudRate = UART_BPS_9600;

  cfg.SPED.uartParity   = MODE_00_8N1;

  // cfg.SPED.airDataRate stays default (safe)


  // Save config

  ResponseStatus rs = e220.setConfiguration(cfg, WRITE_CFG_PWR_DWN_SAVE);


  Serial.print("Write status: ");

  Serial.println(rs.getResponseDescription());


  // Back to normal mode

  e220.setMode(MODE_0_NORMAL);


  Serial.println("\n✓ Configuration DONE!");

  Serial.println("✓ Channel set to 17  (867 MHz)");

  Serial.println("✓ Address set to 0x0000");

  Serial.println("Now move to transmitter/receiver sketch.\n");

}

void loop() {}



