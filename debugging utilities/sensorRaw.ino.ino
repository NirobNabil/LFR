void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, HIGH);
  digitalWrite(11, HIGH);
  
  // put your main code here, to run repeatedly:
  Serial.print(analogRead(A0));
  Serial.print("\t");
  Serial.print(analogRead(A1));
  Serial.print("\t");
  Serial.print(analogRead(A2));
  Serial.print("\t");
  Serial.print(analogRead(A3));
  Serial.print("\t");
  Serial.print(analogRead(A4));
  Serial.print("\t");
  Serial.print(analogRead(A5));
  Serial.print("\t");
  Serial.print(analogRead(A6));
  Serial.print("\t");
  Serial.print(analogRead(A7));
  Serial.println("\t");
  delay(500);
}
