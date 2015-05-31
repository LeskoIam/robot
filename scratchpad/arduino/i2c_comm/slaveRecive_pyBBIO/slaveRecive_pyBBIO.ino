// Wire Slave Receiver
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Receives data as an I2C/TWI slave device
// Refer to the "Wire Master Writer" example for use with this

// Created 29 March 2006

// This example code is in the public domain.

#include <Wire.h>

int ans = 0;  // This in an answer int

void setup()
{
  Wire.begin(8);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent); // register event
  Wire.onRequest(requestEvent); // register event
  Serial.begin(115200);         // start serial for output
}

void loop()
{
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany)
{
  Serial.println("receiveEvent");
  Serial.print("howMany: ");
  Serial.println(howMany);
  
  Serial.print("+|");
  for (int i=0; i<howMany; i++)
  {
    if (Wire.available())
    {
      int c = Wire.read();
      Serial.print(c);
      Serial.print(", ");
      // If 22 is last integer recevied set ans to 1
      if (c == 22) ans = 1;
      else ans = 255;
    }
  }
  Serial.print("|+");
  Serial.println("");
}

void requestEvent()
{
  Serial.println("requestEvent");
  Wire.write(ans);
}
