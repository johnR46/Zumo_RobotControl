#define BRAKE 0
#define CW    1
#define CCW   2
#define CS_THRESHOLD 15   // Definition of safety current (Check: "1.3 Monster Shield Example").

//MOTOR 1
#define MOTOR_A1_PIN 7
#define MOTOR_B1_PIN 8

//MOTOR 2
#define MOTOR_A2_PIN 4
#define MOTOR_B2_PIN 9

#define PWM_MOTOR_1 5
#define PWM_MOTOR_2 6

#define CURRENT_SEN_1 A2
#define CURRENT_SEN_2 A3

#define EN_PIN_1 A0
#define EN_PIN_2 A1

#define MOTOR_1 0
#define MOTOR_2 1

#define MAX  1920
#define MID  1495
#define MIN  1080

#define MAXCH1  1920
#define MIDCH1  1495
#define MINCH1  1080

#define MAXCH2  1920
#define MIDCH2  1495
#define MINCH2  1080

#define MAXCH3  1910
#define MINCH3  1080

#define MAXCH4  1910
#define MIDCH4  1490
#define MINCH4  1080

#define Error   100


#define ch1  22
#define ch2  23
#define ch3  24
#define ch4  25

int CH1 = 0;
int CH2 = 0;
int CH3 = 0;
int CH4 = 0;

short usSpeed = 150;  //default motor speed
unsigned short usMotor_Status = BRAKE;


void setup() {

  pinMode(MOTOR_A1_PIN, OUTPUT);
  pinMode(MOTOR_B1_PIN, OUTPUT);

  pinMode(MOTOR_A2_PIN, OUTPUT);
  pinMode(MOTOR_B2_PIN, OUTPUT);

  pinMode(PWM_MOTOR_1, OUTPUT);
  pinMode(PWM_MOTOR_2, OUTPUT);

  pinMode(CURRENT_SEN_1, OUTPUT);
  pinMode(CURRENT_SEN_2, OUTPUT);

  pinMode(EN_PIN_1, OUTPUT);
  pinMode(EN_PIN_2, OUTPUT);
  Serial.begin(9600);              // Initiates the serial to do the monitoring
  Serial.println("Begin motor control");

}




void loop() {

  CH1 =  pulseIn(ch1, HIGH);
  CH2 =  pulseIn(ch2, HIGH);
  CH3 =  pulseIn(ch3, HIGH);
  CH4 =  pulseIn(ch4, HIGH);
  int  val = map(CH3, MAXCH3, MINCH3, 0, 255);

  if ((CH2 <= MIDCH2 + Error ) && (CH2 >= MIDCH2 - Error) && (CH1 <= MIDCH1 + Error ) && (CH1 >= MIDCH1 - Error)  ) {
    motorGo(0, CW, 0);
    motorGo(1, CW, 0);
  }

  else if ((CH2 >= MIDCH2 + Error)) {
    //Serial.println("reward");
    motorGo(0, CW, val);
    motorGo(1, CW, val);

  }  else if ((CH2 <= MIDCH2 - Error)) {
    motorGo(0, CCW, val);
    motorGo(1, CCW, val);

  }
  else if ((CH1 >= MIDCH1 + Error)) {
    motorGo(0, CW, val);
    motorGo(1, CCW, val);


  }  else if ((CH1 <= MIDCH1 - Error)) {
    motorGo(0, CCW, val);
    motorGo(1, CW, val);

  }
}

void motorGo(uint8_t motor, uint8_t direct, uint8_t pwm)         //Function that controls the variables: motor(0 ou 1), direction (cw ou ccw) e pwm (entra 0 e 255);
{
  if (motor == MOTOR_1)
  {
    if (direct == CW)
    {
      digitalWrite(MOTOR_A1_PIN, LOW);
      digitalWrite(MOTOR_B1_PIN, HIGH);
    }
    else if (direct == CCW)
    {
      digitalWrite(MOTOR_A1_PIN, HIGH);
      digitalWrite(MOTOR_B1_PIN, LOW);
    }
    else
    {
      digitalWrite(MOTOR_A1_PIN, LOW);
      digitalWrite(MOTOR_B1_PIN, LOW);
    }

    analogWrite(PWM_MOTOR_1, pwm);
  }
  else if (motor == MOTOR_2)
  {
    if (direct == CW)
    {
      digitalWrite(MOTOR_A2_PIN, LOW);
      digitalWrite(MOTOR_B2_PIN, HIGH);
    }
    else if (direct == CCW)
    {
      digitalWrite(MOTOR_A2_PIN, HIGH);
      digitalWrite(MOTOR_B2_PIN, LOW);
    }
    else
    {
      digitalWrite(MOTOR_A2_PIN, LOW);
      digitalWrite(MOTOR_B2_PIN, LOW);
    }
    analogWrite(PWM_MOTOR_2, pwm);
  }
}

