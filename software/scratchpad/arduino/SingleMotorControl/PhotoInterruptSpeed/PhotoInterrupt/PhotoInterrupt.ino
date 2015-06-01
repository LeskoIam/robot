volatile unsigned long count1 = 0L;
volatile unsigned long count2 = 0L;
int data_in;

void setup()
{
  attachInterrupt(0, countCallback1, FALLING);
  attachInterrupt(1, countCallback2, FALLING);
  Serial.begin(115200);
  Serial.setTimeout(5);
  Serial.println("Setup done!");
  Serial.print("\n>> ");
}

void loop()
{
  handleSerialCom();
}

void handleSerialCom()
{
  if (Serial.available() > 0)
  {
    data_in = Serial.parseInt();
    Serial.println(data_in);
    switch (data_in)
    {
      case 1: // Get counter 1
        Serial.println(count1);
        Serial.println("OK");
        break;
      case 2: // Get counter 2
        Serial.println(count2);
        Serial.println("OK");
        break;
      case 8: // Reset counter 1
        count1 = 0L;
        Serial.println("counter 1 reset");
        Serial.println("OK");
        break;
      case 9: // Reset counter 2
        count2 = 0L;
        Serial.println("counter 2 reset");
        Serial.println("OK");
        break;
      default:
        Serial.println("NOK");
    }
    Serial.print(">> ");
  }
}

void countCallback1()
{
  // Serial.println("Interrupt detected! I am the interrrupter!");
  count1++ ;
}

void countCallback2()
{
  // Serial.println("Interrupt detected! I am the interrrupter!");
  count2++ ;
}

