#include <Ultrasonic.h>
#include <LiquidCrystal_I2C.h>


Ultrasonic sonar_front(40, 41);
Ultrasonic sonar_right(44, 45);
Ultrasonic sonar_left(38, 39);

LiquidCrystal_I2C lcd(0x27,20,4);


void setup() {
  // put your setup code here, to run once:
  lcd.init();
  lcd.backlight();
   
//  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
//  digitalWrite(2, HIGH);

  
  delay(200);
lcd.clear();
  Serial.print("  L: ");
  Serial.print( sonar_left.read() );
  Serial.print("  R: ");
  Serial.print( sonar_right.read() );
  Serial.print("  F: ");
  Serial.println( sonar_front.read() );

  lcd.setCursor(0,0);
  lcd.print(sonar_front.read());
  
  lcd.setCursor(5,1);
  lcd.print(sonar_right.read());
  
  lcd.setCursor(0,1);
  lcd.print(sonar_left.read());
}
