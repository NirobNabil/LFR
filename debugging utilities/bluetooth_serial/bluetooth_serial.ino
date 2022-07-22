
#include <SoftwareSerial.h>

SoftwareSerial mySerial(50, 51); // RX, TX

void setup() {

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  Serial.begin(9600);
  mySerial.println("Hello Bluetooth");
  Serial.println("Hello USB");
}

void loop() {
  int sensorData = 1050;
  mySerial.print("Sensor reading: ");
  mySerial.println(sensorData);
  Serial.println("hahalol");
} 
