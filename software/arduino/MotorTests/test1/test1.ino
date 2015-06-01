volatile unsigned long count1 = 0L;
volatile unsigned long count2 = 0L;
int command;
int m_num;
int par;

// Motors (M) //
#define M_max_speed 255
#define M_min_speed 0

// Motor 1 (M1) //
#define M1_EN 10  // M1 enable/PWM pin
#define M1_C1 8   // M1 control pin 1
#define M1_C2 9   // M1 control pin 2
int M1_speed = 0; // Initial speed
int M1_dir = 0;      // 0 - forward; 1 - backward

// Motor 2 (M2) //
#define M2_EN 10  // M1 enable/PWM pin
#define M2_C1 8   // M1 control pin 1
#define M2_C2 9   // M1 control pin 2
int M2_speed = 0; // Initial speed
int M2_dir = 0;      // 0 - forward; 1 - backward


void setup() {
  motor_setup();
  attachInterrupt(0, countCallback1, FALLING);
  attachInterrupt(1, countCallback2, FALLING);
  Serial.begin(115200);
  Serial.setTimeout(2);  // fine tune it with o-scope!
  Serial.println("Setup done!");
  Serial.print("\n>> ");
}

void loop() {
  handleSerialCom();
  handle_motor();
}


///////////////////////////////////////
///////////////////////////////////////

void handleSerialCom()
{
  if (Serial.available() > 0)
  {
    command = Serial.parseInt();
    m_num = Serial.parseInt();
    par = Serial.parseInt();
    Serial.print(command);
    Serial.print(" ");
    Serial.print(m_num);
    Serial.print(" ");
    Serial.println(par);
    
    switch (command)
    {
      // Get counters
      case 1:
        Serial.print("Counter ");
        Serial.print(m_num);
        Serial.print(": ");
        Serial.println(get_counter(m_num));
        Serial.println("OK");
        break;
      // Reset counters
      case 2: 
        reset_counter(m_num);
        Serial.print("Counter ");
        Serial.print(m_num);
        Serial.println(" reset");
        Serial.println("OK");
        break;

      // Alive?
      case 5:
        Serial.println("ALIVE");
        Serial.println("OK");
        break;
      
      // Motor controls
      // Set speed
      case 6:
        set_speed(m_num, par);
        Serial.println("OK");
        break;
      // Set direction
      case 7:
        set_direction(m_num, par);
        Serial.println("OK");
        break;
      default:
        Serial.println("NOK");
    }
    Serial.print(">> ");
  }
}

///////////////////////////////////////////
//               COUNTERS                //
///////////////////////////////////////////

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

unsigned long get_counter(int side)
{
  if(side == 1)
  {
    return count1;
  }
  else if(side == 2)
  {
    return count2;
  }
}

void reset_counter(int side)
{
  if(side == 1)
  {
    count1 = 0L;
  }
  else if(side == 2)
  {
    count2 = 0L;
  }
}

///////////////////////////////////////////
//               MOTORS                  //
///////////////////////////////////////////

void motor_setup()
{
  // Initialize motor defaults
  pinMode(M1_EN, OUTPUT);
  pinMode(M1_C1, OUTPUT);
  pinMode(M1_C2, OUTPUT);
  analogWrite(M1_EN, 0);
}

void handle_motor()
{
  analogWrite(M1_EN, M1_speed);
  
  if(M1_dir == 1)
  {
    forward();
  }
  else if(M1_dir == 2)
  {
    backward();
  }
}

void set_speed(int side, int speed)
{
  if(side == 1)
  {
    M1_speed = speed;
  }
  else if(side == 0)
  {
    M2_speed = speed;
  }
}

void set_direction(int side, int direction)
{
  if(side == 1)
  {
    M1_dir = direction;
  }
  else if(side == 0)
  {
    M2_dir = direction;
  }
}

void forward()
{
  digitalWrite(M1_C1, HIGH);
  digitalWrite(M1_C2, LOW);
}

void backward()
{
  digitalWrite(M1_C1, LOW);
  digitalWrite(M1_C2, HIGH);
}
