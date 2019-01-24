#include<Wire.h>
int distance;
char address = 0x08; // Run I2C Scanner to get address
void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(9600);

}

void loop() {
  // put your  main code here, to run repeatedly:
  Wire.requestFrom(address, 2);

  distance = Wire.read() << 8; distance |= Wire.read();

  Serial.println(distance);
  delay(10);
}
