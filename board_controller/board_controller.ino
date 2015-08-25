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
  motor.attach(5, 1000, 2000);
  motor.writeMicroseconds(1000);
  delay(400);

}

long max_delay = 100000;
int speed = 0;
void loop() {

  boolean timeout = false;
  unsigned long started_waiting_at = micros(); // Set up a timeout period, get the current microseconds
  while ( ! radio.available() ) {
    if ((micros() - started_waiting_at) > max_delay ) { 
      timeout = true;
      Serial.println("Fuck");
      break; 
    } 
  }
  if (timeout) {
    speed = 92;
  } else {
    speed = 0;
    radio.read(&speed, sizeof(int));
  }
  Serial.println(speed);
  motor.write(speed);
}
