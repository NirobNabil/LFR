

/* using every variable as global because passing parameters take extra cpu cycle
   checkWhite can actually be placed inside setMotorSpeed function's if(output>0) part
   have to merge the functions to make them inline functions


*/


                                                                          
#include <PID_v1.h>

#define IRminValueWhenOnBlack 700 
#define IRmaxValueWhenOnWhite 300
#define whiteRangeLow 12
#define whiteRangeHigh 18
#define onWhiteCountdownThreshold1 300   //the amount of milliseconds it'll wait before it takes actions to get on the track
#define onWhiteCountdownThreshold2 1000 //this should be longer than the time taken to rotate 180deg
#define waitThesholdForFlagReset 1800
#define waitThresholdBeforeCheckForRightLeft 300
#define waitAfterTurn 1000
#define fullBlackCountdownThreshold 1000



//change the timing values according to speed or set a function the void setup to chanege the timing values according to set speeds

int waitCountdown = -waitThresholdBeforeCheckForRightLeft;
int fullBlackCountdown = 0;
int speedValLow = 0;
int speedValHigh = 110;
int waitForWhite = 0;

double input = 0, setPoint = 380, output = 0, kp = 1.5, ki = 0, kd = 0, errorSum = 0;
 
PID pid(&input, &output, &setPoint, kp, ki, kd, DIRECT);

//flags
char flags = 0b00000000;  
/*  8th bit onWhite
 *  7th bit toTurnLeft
 *  6th bit toTurnRight
 */



class motor{
  public:
  byte FORWARDOR, FORWARDAND, BACKWARDOR, BACKWARDAND, PWM, lastSPEED;
  char side;
  motor(byte pwm, char motorSIDE){
    if(motorSIDE == 'R'){
      side = motorSIDE;
      PWM = pwm;
      FORWARDOR = B10000000;
      FORWARDAND = B10111111;
      BACKWARDOR = B01000000;
      BACKWARDAND = B01111111;
    }else if(motorSIDE == 'L'){
      side = motorSIDE;
      PWM = pwm;
      FORWARDOR = B00010000;
      FORWARDAND = B11011111;
      BACKWARDOR = B00100000;
      BACKWARDAND = B11101111;
    }
  }
  void run(signed int SPEED){
    lastSPEED = SPEED;
    if(SPEED>0){
      PORTD = PORTD | FORWARDOR;
      PORTD = PORTD & FORWARDAND;
      analogWrite(PWM, map(SPEED, 0, 255, speedValLow, speedValHigh));
      Serial.print(side);
      Serial.print(" ");
      Serial.print(SPEED);
      Serial.print(" ");
      Serial.print(map(SPEED, 0, 255, 0, 100));
      Serial.print("\t");
    }else if(SPEED<0){
      Serial.print("\t");
      PORTD = PORTD | BACKWARDOR;
      PORTD = PORTD & BACKWARDAND;
      analogWrite(PWM, map(SPEED, 0, -255, speedValLow, speedValHigh));
      Serial.print(side);
      Serial.print(" ");
      Serial.print(SPEED);
      Serial.print(" ");
      Serial.print(map(SPEED, 0, -255, 0, 100));
      Serial.print("\t");
    }else if(SPEED == 0){
      Serial.print("\t");
      //PORTD = PORTD | BACKWARDOR;
      //PORTD = PORTD & BACKWARDAND;
      analogWrite(PWM, map(SPEED, 0, -255, speedValLow, speedValHigh));
      Serial.print(side);
      Serial.print(" ");
      Serial.print(SPEED);
      Serial.print(" ");
      Serial.print(0);
      Serial.print("\t");
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
      PORTD = PORTD | BACKWARDOR;
      PORTD = PORTD & BACKWARDAND;
      analogWrite(PWM, map(lastSPEED, 0, 255, 40, 100));
      Serial.print(side);
      Serial.print(" ");
      Serial.print("LS");
      Serial.print(lastSPEED);
      Serial.print(" ");
      Serial.print(map(lastSPEED, 0, 255, 40, 100));
      Serial.print("\t");
      Serial.print("\t");
      Serial.println(" ");
    }else if(lastSPEED<0){
      PORTD = PORTD | FORWARDOR;
      PORTD = PORTD & FORWARDAND;
      analogWrite(PWM, map(lastSPEED, 0, -255, 40, 70));
      Serial.print(side);
      Serial.print(" ");
      Serial.print(lastSPEED);
      Serial.print(" L ");
      Serial.print(map(lastSPEED, 0, -255, 40, 150));
      Serial.print("\t");
      Serial.print("\t");
      Serial.println("\n");
    }
  }

  void brake(){
    analogWrite(PWM, 255);
    PORTD = PORTD | BACKWARDOR;
    PORTD = PORTD & BACKWARDAND;
    delay(5);
    analogWrite(PWM, 0);
  }
};
motor motorL(9, 'L');
motor motorR(10, 'R');


double IR[8];

void printBinary(char val){
    for (int i = 0; i < 8; i++) {
      Serial.print(!!((val << i) & 0x80));
    }
    //Serial.print("\n");
}


short int countdownStart;
void checkings(){                                               //does all the checkings
  char tempFlag = 0b00000000;                                   /* tempFlag is a temporary flag variable write all the flag bits to
                                                                *  at end of the checkings function tempFlag will be written to main flag variable
                                                                */
                                                                
                                                                //check if bot is on white                                                  
  if(output>whiteRangeLow && output>whiteRangeHigh){            //whiteRangeLow and whtieRamgeHigh need to be calibrated
    tempFlag |= 1<<7;                                           //set 8th bit of tempFlag to 1
  }else{ 
    tempFlag &= ~(1<<7);                                        //set 8th bit of tempFlag to 0
    countdownStart = millis();                                  //mark the start of the countdown to count till the onwhite wait threshold
  }

  //Serial.print("");
  //flags = tempFlag; 
  //printBinary(flags);
  
}




byte accelerating; //0 if not accelerating and anything greater than 0 for accelerating(higher value means faster accleration)
byte PWML=9, PWMR=10;
//have some problem here

byte BACKWARD = B10100000; //replaced clockwise and anticlockwise with forward and backward
byte FORWARD = B01010000;

byte base = 255;
int waitTurnCountdown = 0;
void setMotorSpeed(){
  printBinary(flags);                                           //printing the flags
  Serial.print("\t");
  if(1){                                                        //check if any of the flags is 1
    char gg1;
    if((flags & 0b10000000) > 0){                               //check if first bit of flags is 1 which means bot is on white
        int spent = millis() - countdownStart;                    //count the spent time
        if(spent > onWhiteCountdownThreshold1){                    
         if((flags & 0b01000000) > 0){                             //bot is qeued to turn left
          gg1 = 01000000;
          while(analogRead(A5) < IRminValueWhenOnBlack){
            //digitalWrite(LED_BUILTIN, HIGH);
            Serial.print("C");
            Serial.print(analogRead(A0));
            Serial.println("\t");
            if(analogRead(A0) > IRminValueWhenOnBlack){
              //digitalWrite(LED_BUILTIN, HIGH);
              //motorL.brake();
              //motorR.brake();
            }else{
              //digitalWrite(LED_BUILTIN, LOW);
              motorL.run(-170); 
              motorR.run(170);
            } 
          }
        }else if((flags & 0b00100000)>0){                       //bot is qeued to turn right
          gg1 = 00100000;
          while(analogRead(A2) < IRminValueWhenOnBlack){
            //digitalWrite(LED_BUILTIN, LOW);
            Serial.print("C");
            Serial.print(analogRead(A7));
            Serial.println("\t");
            if(analogRead(A7) > IRminValueWhenOnBlack){
              //digitalWrite(LED_BUILTIN, LOW);
            }else{
              //digitalWrite(LED_BUILTIN, LOW);
            }
            motorL.run(170);
            motorR.run(-170);          
         }
         waitTurnCountdown = millis();
       }        
        waitTurnCountdown = millis();
        waitForWhite = 0;  
        flags &= 0b10011111;
        waitCountdown = millis();
      }
      if(spent > onWhiteCountdownThreshold2){                 //if the waiting threshold is crossed go to reverse gear
        motorR.reverseRun();
        motorL.reverseRun();
        return;                                               //returns because it doesn't need to check for left or right roads when going backward
      }                                                       //if the bot was qeued to turn left or right do it
    return;
    }
    if( (flags & 0b00010000) > 0 && (millis() - fullBlackCountdown) < fullBlackCountdownThreshold){
      digitalWrite(LED_BUILTIN, HIGH);
      //flags &= 0b10011111;
      motorL.run(motorL.lastSPEED);
      motorR.run(motorR.lastSPEED);
      Serial.print(millis() - fullBlackCountdown);
      return;
    }else if((millis() - fullBlackCountdown) > fullBlackCountdownThreshold){
      Serial.print("came");
      //motorL.run(0);
      //motorR.run(0);
      return;
    }
    
    if( ( (flags & 0b01000000) > 0 || (flags & 0b00100000)>0 ) && waitForWhite == 0 ){
       
      if((flags & 0b00100000)>0){                       //bot is qeued to turn right
        gg1 = 00100000;
        delay(400);
        motorL.run(170);
        motorR.run(-170);
        delay(200);
        while(analogRead(A2) < IRminValueWhenOnBlack){
          //digitalWrite(LED_BUILTIN, LOW);
          Serial.print("C");
          Serial.print(analogRead(A7));
          Serial.println("\t");
          if(analogRead(A7) > IRminValueWhenOnBlack){
            //digitalWrite(LED_BUILTIN, LOW);
          }else{
            //digitalWrite(LED_BUILTIN, LOW);
          }
          motorL.run(170);
          motorR.run(-170);          
       }
       waitTurnCountdown = millis();
       flags &= 0b10011111;
       waitCountdown = millis();
      
       return; //returns because bot is on white                 //and finally RETURN here because there is nothing else to do if bot is on white
     }          
   }
 }

  /*
  if((flags & 0b01000000) > 0 && analogRead(A7) > IRminValueWhenOnBlack){     //this MAY cause problems later
    delay(200);                                                 
    while(analogRead(A6) < IRminValueWhenOnBlack){
      motorR.run(170);
      motorL.run(-170);
    }
    delay(100);
  }*/
                                                                /*       base is actually the highest speed        */
  if(output<0){                                                 //if output less than 0 turn left                                           
    motorR.run(base);                                           //set the right motor to highest speed and reduce left motor speed
    motorL.run(base + (output));                                //had to use "base + output" because output is negative here 
  }else if(output>0){                                           //if output greater than 0 turn right
    motorR.run(base - (output));                                //set the left motor to highest speed and reduce right motor speed
    motorL.run(base);                                           //used "base - output" here because output is positive
  }else if(output==0){                                          //if output is equal to 0 go straight
    motorR.run(base);                                           //set both motors to highest speed
    motorL.run(base);
  }
}


void setup()
{  
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT); //this is standby pin
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  digitalWrite(8, HIGH);
  pid.SetMode(AUTOMATIC);
  pid.SetOutputLimits(-255,255);
  //thePID.SetMode(AUTOMATIC);
  //thePID.SetSampleTime(1);
  //thePID.SetOutputLimits(-1024, 1024); //need to change this later
  Serial.begin(9600);
}

int lastgg = 0;
int time = 0;
bool x = true;
void loop()
{
  time = millis();
  setVals();
  PIDcompute();
  setMotorSpeed();
  //x = !x;
}


//waitCountdown = -waitThresholdBeforeCheckForRightLeft;
int flagCountdown=0;
void setVals() {
  IR[0] = analogRead(A0);                                       //A0 is the rightmost IR
  IR[1] = analogRead(A1);
  IR[2] = analogRead(A2);
  IR[3] = analogRead(A3);
  IR[4] = analogRead(A4);
  IR[5] = analogRead(A5);
  IR[6] = analogRead(A6);
  IR[7] = analogRead(A7);                                       //A7 is the leftmost IR

  //sets the 1st bit to 1 when finds full white
  if(IR[1] < IRmaxValueWhenOnWhite && IR[3] < IRmaxValueWhenOnWhite && IR[5] < IRmaxValueWhenOnWhite && IR[7] < IRmaxValueWhenOnWhite){
    flags |= 0b10000000;
  }else{
    countdownStart = millis();
    flags &= 0b01111111; 
  }

  //sets the 4th bit to to 1 when finds a black stripe
  if(IR[7] > IRminValueWhenOnBlack && IR[5] > IRminValueWhenOnBlack && IR[3] > IRminValueWhenOnBlack && IR[1] > IRminValueWhenOnBlack){
      flags |= 0b00010000;
      waitForWhite = 1;
      //digitalWrite(LED_BUILTIN, HIGH);
  }else{
      fullBlackCountdown = millis();
      flags &= 0b11101111;
  }

  //detects left or right
  if( (millis() - waitCountdown) > waitThresholdBeforeCheckForRightLeft){
    if(IR[1] > IRminValueWhenOnBlack){
        if(IR[5] > IRminValueWhenOnBlack){
          waitCountdown = millis();
          flagCountdown = millis();
          //speedValHigh = 50;
          flags |= 0b00100000;
          flags &= 0b10111111;
        }
    }else if(IR[7] > IRminValueWhenOnBlack){
        if(IR[3] > IRminValueWhenOnBlack){
          waitCountdown = millis();
          flagCountdown = millis();
          //speedValHigh = 50;
          flags |= 0b01000000;
          flags &= 0b11011111;
        } 
     }
  }

  
  //resets flag after a certain time
  if(millis() - flagCountdown > waitThesholdForFlagReset){
    if(flags & 0b10000000 > 0){
      //Serial.println("reset flag");
      flags &= 0b10000000; 
    }else{
      //Serial.println("reset flag");
      flags &= 0b00000000;
    }
  }
  //Serial.print("\tCAME2");
  //printBinary(flags);

  //turn the LEDs on or off according to the left right flags
  if( (flags & 0b01000000) > 0){
    digitalWrite(3, LOW);
    digitalWrite(2, HIGH);
  }else if( (flags & 0b00100000) > 0){
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);
  }else if( (flags & 0b00010000) > 0 ){
    digitalWrite(LED_BUILTIN, HIGH);
  }
  else{
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
  }

    

  
  input = (IR[0] * 1 + IR[1] * 100 + IR[2] * 200 + IR[3] * 300 + IR[4] * 400 + IR[5] * 500 + IR[6] * 600 + IR[7] * 700) / (IR[0] + IR[1] + IR[2] + IR[3] + IR[4] + IR[5] + IR[6] + IR[7]);
}


double lastErr;
int lastvals[5] = {0,0,0,0,0};                                  //this name is important because it is a global variable

/*
void push(int val){
  int arrlength = sizeof(lastvals)/sizeof(lastvals[0]);
  for(int i=0; i<arrlength-1; i++){
    lastvals[i] = lastvals[i+1];
  }
  lastvals[arrlength-1] = val;
}
*/


void PIDcompute(){
  pid.Compute();
  Serial.print(input);
  Serial.print("\t");
  Serial.print(output);
  Serial.println("\t \t");
  //push(output);
}



/*
  //implementing the PID manually
  //will do this later if i have time
  unsigned long now; //now is a global variable being updated on every loop
  double timeChange;


  //PID part
  double error; //for proportional
  double errorSum; //for integral
  double lastError, diffError; //for differentiation
  double input, output, setPoint, kp, ki, kd, callTimeDiff;  //for PID calibration
  unsigned long lastTimePID, timeChangePID, nowPID; //storing lasttime val for PID only

  void thePID(){
  nowPID = millis();
  timeChangePID = nowPID - lastTimePID;
  if(timeChangePID >= callTimeDiff){
    error = setPoint - input; //getting the error
    errorSum = (error*timeChange); //storing information for integral part
    diffError = (error - lastError)/timeChange; //storing information for differentitaion part

    output = kp*error + ki*errorSum + kd*diffError;
  }
  }
*/

/*
   this one was for digital pins :'(
  void setVals(){
  //Serial.print(PINC); 00010111
  //Serial.print("  ");
  char val = PINC;
  //val >>= 3;
  for(int i=4; i>=0; i--){
      IR[i] = val & 1;
      val >>= 1;
  };
  input = (IR[0] *100)+(IR[1] *200)+(IR[2] *300)+(IR[3] *400);
  Serial.print(IR[0]);
  Serial.print(IR[1]);
  Serial.print(IR[2]);
  Serial.print(IR[3]);
  Serial.print(IR[4]);
  Serial.print("  ");
  Serial.print(digitalRead(11));
  Serial.println(digitalRead(12));
  }
*/
