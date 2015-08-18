#include <SPI.h>


#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>

RF24 radio(9, 10);
byte address[] = "cntrl1";
void setup() {
  Serial.begin(57600);
  printf_begin();
  radio.begin();
  radio.printDetails();
  radio.setPALevel(RF24_PA_HIGH);
  radio.openWritingPipe(address);
}

void loop() {
  int raw = analogRead(3) ;
  int speed = map(raw, 0, 1023, 0, 180);
  Serial.println(speed);
  if (!radio.write(&speed, sizeof(int))) {
    //   Serial.println("fail");
  }
  
}
