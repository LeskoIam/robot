// Wire Slave Receiver
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Receives data as an I2C/TWI slave device
// Refer to the "Wire Master Writer" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>

int answer = -1;

void setup()
{
  Wire.begin(8);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent); // register event
  Wire.onRequest(requestEvent); // register event
  Serial.begin(115200);         // start serial for output 
}

void loop()
{
  // delay(100);
  if (answer >= 0)
  {
    Wire.write(answer);
    Serial.println("Sending answer");
    answer = -1;
  }
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany)
{
  Serial.print("howMany: ");
  Serial.println(howMany);
  
  Serial.print("+|");
  for (int i=0; i<howMany; i++)
  {
    if (Wire.available())
    {
      char c = Wire.read();
      if (i != 0)
      {
        Serial.print(c);
        answer = 1;
      }
      else
      {
        Serial.print("?");
        answer = 0;
      }
    }
  }
  Serial.print("|+");
  Serial.println("");
}

void requestEvent()
{
  Wire.write("a");
  Serial.println("requestEvent");
}
