                                                                          
#include <PID_v1.h>
#include <SoftwareSerial.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display


#include "definitions.h"



SoftwareSerial mySerial(50, 51); // RX, TX

double input = 0, setPoint = 0, output = 0, kp = 1.5, ki = 0, kd = 0.01, errorSum = 0;
 
PID pid(&input, &output, &setPoint, kp, ki, kd, DIRECT);



motor motorL('L');
motor motorR('R');

void setup() {
  
  flag = 0;
  dir_flag = 1;      // dir_flag needs to have an initial meaningful value otherwise handlewhite stops the bot because dir_flag is not equal 1 or 2
  block_flag_change = 0;

  Serial.begin(9600);  
//  mySerial.begin(9600);
  pid.SetMode(AUTOMATIC);
  pid.SetOutputLimits(-255, 255);

  lcd.init();                      // initialize the lcd 
  lcd.backlight();
  
}

 

void misc();
volatile unsigned long current_time;

unsigned long lcd_clear_last = 0;

void loop() {
  
  last_flag = flag;
  last_sensor = sensor;
  
  kp = mapf(analogRead(A6), 0, 1024, 0, 3);
  pid.SetTunings(kp, kd, ki);

//    lcd.setCursor(12, 0);
//    lcd.print(kp);
  
  current_time = millis();

  if( current_time > lcd_clear_last + 300 ) {
    lcd.clear();
    lcd_clear_last = current_time;
  }
  
  readSensor();

  

  mandatory_set_flag();
  if( !block_flag_change )
    set_flag();

  
  
  pid.Compute();

  
  lcd.setCursor(0,0);
  lcd.print(output);
//  lcd.setCursor(0,1);
//  lcd.print(input);
  lcd.setCursor(9,1);
  lcd.print(flag);
  lcd.setCursor(12,1);
  lcd.print(dir_flag);

  lcd.setCursor(9, 0);
  lcd.print(sensor_s);
  
  
  

  if( flag == 1 ) {
    handle_white();
  } else if( flag == 2 || flag == 3 ) {
    handle_sharp_angle();
  } else {
    pidControl();   
  }

//  delay(200);
  
}




int pos = 0;





int SL = 17, SR = 25;
void motor_set(int l, int r) {
  motorL.run(l);
  motorR.run(r);
}


void misc() {

//  else if (sum == 1 || sum == 2) 
//    {  //straight line
//      
//    }
    
}
