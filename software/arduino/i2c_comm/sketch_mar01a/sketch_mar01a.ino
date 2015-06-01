#include <Wire.h>

#define LED_PIN 13
#define LED_1 12
#define LED_2 11

int x;

void setup() {
  Wire.begin(4);                // Start I2C Bus as a Slave (Device Number 9)
  Wire.onReceive(receiveEvent); // register event
  
  pinMode(LED_PIN, OUTPUT);
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  
  digitalWrite(LED_PIN, LOW);
  digitalWrite(LED_1, LOW);
  digitalWrite(LED_2, LOW);
  Serial.begin(115200);
  
  x = 0;
}

void loop() {
  // Serial.println(x);
  // delay(100);
}

void receiveEvent(int howMany) {
  // x = Wire.read();    // receive byte as an integer
  Serial.println(Wire.read());
}

