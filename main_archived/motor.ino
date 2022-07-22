const int motorLForward = 8;
const int motorLBackward = 9;
const int motorLPWM = 10;

const int motorRForward = 2;
const int motorRBackward = 3;
const int motorRPWM = 4;



class motor{
  public:
  int FORWARD,BACKWARD, PWM, lastSPEED;
  char side;

  motor(char motorSIDE){
    if(motorSIDE == 'R'){
      side = motorSIDE;
      PWM = pwm;
      FORWARD = motorRForward;
      BACKWARD = motorRBackward;
      PWM = motorRPWM; 
    }else if(motorSIDE == 'L'){
      side = motorSIDE;
      FORWARD = motorLForward;
      BACKWARD = motorLBackward;
      PWM = motorLPWM;
    }
  }

  void run(signed int SPEED){
    lastSPEED = SPEED;
    if(SPEED>0){
      digitalWrite(FORWARD, HIGH);
      digitalWrite(BACKWARD, LOW);
      analogWrite(PWM, map(SPEED, 0, 255, speedValLow, speedValHigh));
      print(side, SPEED, map(SPEED, 0, 255, 0, 100));
    }else if(SPEED<0){
      digitalWrite(FORWARD, LOW);
      digitalWrite(BACKWARD, HIGH);
      analogWrite(PWM, map(SPEED, 0, -255, speedValLow, speedValHigh));
      print(side, SPEED, map(SPEED, 0, -255, 0, 100));
    }else if(SPEED == 0){
      Serial.print("\t");
      analogWrite(PWM, map(SPEED, 0, -255, speedValLow, speedValHigh));
      print(side, SPEED, map(SPEED, 0, -255, 0, 100));
    }
  }

  //a backup of the last SPEED is saved everytime the run is called and it will not 
  //change after the bot goes to white because when the bot is in white there will be
  //no calls to run function.
  //reverseRun lets the bot go to where it came from
  void reverseRun(){
    Serial.print("REVERSE");
    Serial.print("\t");

    if(lastSPEED>0){
      digitalWrite(FORWARD, LOW);
      digitalWrite(BACKWARD, HIGH);
      analogWrite(PWM, map(lastSPEED, 0, 255, 40, 100));
      print(side, SPEED, map(lastSPEED, 0, 255, 40, 100));

    }else if(lastSPEED<0){
      digitalWrite(FORWARD, HIGH);
      digitalWrite(BACKWARD, LOW);
      analogWrite(PWM, map(lastSPEED, 0, -255, 40, 70));
      print(side, SPEED, map(lastSPEED, 0, -255, 40, 150));
    }
  }

  void brake(){
    digitalWrite(FORWARD, 1);
    digitalWrite(BACKWARD, 1);
    analogWrite(PWM, 0);
  }
};
