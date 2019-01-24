const int xpin = 1;
const int ypin = 2;
const int zpin = 3;

void setup(){
  Serial.begin(9600);
}

void loop(){
  int x = analogRead(xpin);
  int y = analogRead(ypin);
  int z = analogRead(zpin);

  float zero_G = 512.0;
 
  float scale = 102.4;

  Serial.print(((float)x - 331.5)/65*9.8);
  Serial.print(",");
  Serial.print(((float)y - 329.5)/68.5*9.8);
  Serial.print(",");
  Serial.println(((float)z - 340)/68*9.8);
  delay(50);
}
