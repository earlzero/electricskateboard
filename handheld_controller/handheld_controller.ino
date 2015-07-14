#include <SPI.h>

#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>

byte address[] = "cntrl1";
//long address = 0xaabbccddeel;
RF24 radio(9, 10);

void setup() {
  Serial.begin(57600);
  printf_begin();
  radio.begin();
  radio.printDetails();
  radio.setPALevel(RF24_PA_LOW);
  radio.openWritingPipe(address);
  radio.startListening();
}

void loop() {
  radio.stopListening();
  int data = analogRead(3);
  boolean timeout = false;
  delay(50);
  int value = (int)(data * 180.0 / 1023);
  if (!radio.write(&value, sizeof(int))) {
    //   Serial.println("fail");
  }
  radio.startListening();
}

