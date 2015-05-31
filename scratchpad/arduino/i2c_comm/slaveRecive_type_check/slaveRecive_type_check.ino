// Wire Slave Receiver
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Receives data as an I2C/TWI slave device
// Refer to the "Wire Master Writer" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>

void setup()
{
  Wire.begin(8);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(115200);         // start serial for output
}

void loop()
{
  delay(100);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany)
{
  Serial.print("howMany: ");
  Serial.println(howMany);
  int type = Wire.read();  // WA, but it woorks, should be 0
  if (type != 0)
  {
    Serial.println("WA is not 0! type[0] != 0");
  }

  Serial.print("+|");
  while(1 < Wire.available()) // loop through all but the last (last = 9)
  {
    char c = Wire.read();  // receive byte as a character
    Serial.print(c);       // print the character
  }
  Serial.print("|+");
 int x = Wire.read();     // receive byte as an integer
 // Serial.println(x);    // print the integer
 Serial.println("");
}
