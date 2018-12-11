void setup() {
  // put your setup code here, to run once:
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  FORWARDOR = B10000000;
  FORWARDAND = B10111111;
  BACKWARDOR = B01000000;
  BACKWARDAND = B01111111;
}

void loop() {
  // put your main code here, to run repeatedly:
  
  PORTD = PORTD | FORWARDOR;
  PORTD = PORTD & FORWARDAND;
}
