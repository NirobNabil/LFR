

motor::motor(char motorSIDE)
{
  
  side = motorSIDE;
  if (motorSIDE == 'R')
  {
    PWM = motorRPWM;
    FORWARD = motorRForward;
    BACKWARD = motorRBackward;
    PWM = motorRPWM;
  }
  else if (motorSIDE == 'L')
  {
    FORWARD = motorLForward;
    BACKWARD = motorLBackward;
    PWM = motorLPWM;
  }
}

void motor::run(signed int SPEED)
{
  if( side == 'L' ) SPEED = map(SPEED, 0, 255, 0, 255-59);      // adjusting for motor speed variation at same pwm
  
  lastSPEED = SPEED;
  if (SPEED >= 0)
  {
    digitalWrite(FORWARD, HIGH);
    digitalWrite(BACKWARD, LOW);
    analogWrite(PWM, map(SPEED, 0, 255, speedValLow, speedValHigh));
//    print(side, SPEED, map(SPEED, 0, 255, 0, 100));
  }
  else if (SPEED < 0)
  {
    digitalWrite(FORWARD, LOW);
    digitalWrite(BACKWARD, HIGH);
    analogWrite(PWM, map(SPEED, 0, -255, speedValLow, speedValHigh));
//    print(side, SPEED, map(SPEED, 0, -255, 0, 100));
  }

  if( side == 'L' ) {
    lcd.setCursor(0,1); 
  }else lcd.setCursor(4, 1);
  lcd.print(SPEED);
  
}

// a backup of the last SPEED is saved everytime the run is called and it will not
// change after the bot goes to white because when the bot is in white there will be
// no calls to run function.
// reverseRun lets the bot go to where it came from
void motor::reverseRun()
{
  Serial.print("REVERSE");
  Serial.print("\t");

  if (lastSPEED >= 0)
  {
    digitalWrite(FORWARD, LOW);
    digitalWrite(BACKWARD, HIGH);
    analogWrite(PWM, map(lastSPEED, 0, 255, 40, 100));
//    print(side, lastSPEED, map(lastSPEED, 0, 255, 40, 100));
  }
  else if (lastSPEED < 0)
  {
    digitalWrite(FORWARD, HIGH);
    digitalWrite(BACKWARD, LOW);
    analogWrite(PWM, map(lastSPEED, 0, -255, 40, 70));
//    print(side, lastSPEED, map(lastSPEED, 0, -255, 40, 150));
  }
}

void motor::brake()
{
  digitalWrite(FORWARD, 1);
  digitalWrite(BACKWARD, 1);
  analogWrite(PWM, 0);
}
