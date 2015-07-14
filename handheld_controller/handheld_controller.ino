#include <SPI.h>

#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>

byte address[] = "cntrl1";
//long address = 0xaabbccddeel;
RF24 radio(9, 10);

int inPin = 7;
int prev_value = 0;
boolean cruise_control = false;
int cruise_speed = 0;
int prev_speed = 0;
void setup() {
  pinMode(inPin, INPUT);
  digitalWrite(inPin, HIGH);
  Serial.begin(57600);
  printf_begin();
  radio.begin();
  radio.printDetails();
  radio.setPALevel(RF24_PA_HIGH);
  radio.openWritingPipe(address);
  radio.startListening();
}

void loop() {
  radio.stopListening();
  int data = analogRead(3);
  delay(50);
  int button_value = digitalRead(inPin);
  int speed = (int)(data * 180.0 / 1023);
  if(!button_value) {
    cruise_speed = max(cruise_speed, speed);
  } else if(prev_speed != speed) {
    cruise_speed = 0;
  }
  prev_speed = speed;
  speed = max(cruise_speed, speed);
  Serial.println(speed);  
  if (!radio.write(&speed, sizeof(int))) {
    //   Serial.println("fail");
  }
  radio.startListening();
}

