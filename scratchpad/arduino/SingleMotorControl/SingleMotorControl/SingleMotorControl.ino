// Motors (M) //
#define M_max_speed 255
#define M_min_speed 0

// Motor 1 (M1) //
#define M1_EN 10  // M1 enable/PWM pin
#define M1_C1 8   // M1 control pin 1
#define M1_C2 9   // M1 control pin 2
int M1_speed = 0; // Initial speed


void setup()
{
  // initialize serial:
  Serial.begin(9600);
  
  // Initialize motor defaults
  motor_setup();
  
  Serial.println("Starting in 2 s...");
  delay(2000);
}

void loop()
{
  motor_on();
  Serial.print("SPEED_1 = ");
  Serial.println(M1_speed);
  
  digitalWrite(M1_C1, HIGH);
  digitalWrite(M1_C2, LOW);
  Serial.println("DIR 1");
  set_speed(255, 20);
  delay(1000);
  
  // Set speed to 200
  set_speed(200, 30);
  Serial.print("SPEED_2 = ");
  Serial.println(M1_speed);
  delay(2000);

  // Stop
  motor_stop();
  motor_off();
  delay(1000);
  motor_on();
  Serial.print("SPEED_3 = ");
  Serial.println(M1_speed);
  delay(1000);
  
  // Change direction
  digitalWrite(M1_C1, LOW);
  digitalWrite(M1_C2, HIGH);
  Serial.println("DIR 2");
  set_speed(160, 20);
  delay(1000);
  
  // Stop
  motor_off();
  Serial.print("SPEED_4 = ");
  Serial.println(M1_speed);
  delay(1000);
}


// ######################################################
// ######################################################

void motor_setup()
{
  // Initialize motor defaults
  pinMode(M1_EN, OUTPUT);
  pinMode(M1_C1, OUTPUT);
  pinMode(M1_C2, OUTPUT);
  analogWrite(M1_EN, 0);
}

void acc(int to_speed, int t)
{
  Serial.println("ACC");
  M1_speed = M1_speed + 1;
  for (M1_speed; M1_speed <= to_speed; M1_speed++)
  {
    Serial.print("SPEED_ACC = ");
    Serial.println(M1_speed);
    analogWrite(M1_EN, M1_speed);
    delay(t);
  }
  Serial.println("");
  M1_speed = M1_speed - 1;
}


void dcc(int to_speed, int t)
{
  Serial.println("DCC");
  M1_speed = M1_speed - 1;
  for (M1_speed; M1_speed >= to_speed; M1_speed--)
  {
    analogWrite(M1_EN, M1_speed);
    Serial.print("SPEED_DCC = ");
    Serial.println(M1_speed);
    delay(t);
  }
  Serial.println("");
  M1_speed = M1_speed + 1;
}


void set_speed(int s, int t)
{
  Serial.print("SETTING SPEED TO = ");
  Serial.println(s);
  if (s < M1_speed)
  {
    dcc(s, t);
  }
  else if (s > M1_speed)
  {
    acc(s, t);
  }
}


void motor_off()
{
  Serial.println("MOTOR OFF");
  digitalWrite(M1_EN, LOW);
}


void motor_on()
{
  Serial.println("MOTOR ON");
  digitalWrite(M1_EN, HIGH);
}


void motor_stop()
{
  Serial.println("MOTOR STOP");
  if (M1_speed > 0)
  {
    set_speed(0, 10);
  }
}

