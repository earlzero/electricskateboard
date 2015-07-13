#include <Servo.h>

#include <SPI.h>

#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>

byte address[] = "cntrl1";

RF24 radio(9, 10);
Servo motor; 


void setup() {
  Serial.begin(57600);
  printf_begin();
  radio.begin();
  radio.printDetails();
  radio.setPALevel(RF24_PA_LOW);
  radio.openReadingPipe(1, address);
  radio.startListening();
  motor.attach(6);
  motor.writeMicroseconds(1000);
}

void loop() {

  boolean timeout = false;
  unsigned long started_waiting_at = micros(); // Set up a timeout period, get the current microseconds
  while ( ! radio.available() ) { // While nothing is received
    if (micros() - started_waiting_at > 50000 ) { // If waited longer than 200ms, indicate timeout and exit while loop
      timeout = true;
      break;
    }
  }
  if (timeout) {
       motor.write(92);
  } else {
    int value = 0;
    radio.read(&value, sizeof(int));
    Serial.println(value);
    motor.write(value);
  }
}
