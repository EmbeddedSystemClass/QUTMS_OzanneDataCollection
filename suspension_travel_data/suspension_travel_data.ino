//include required library header files
#include<Wire.h>
#include<SPI.h>
#include<SD.h>

//setup some global variables
int dist, val, potPin;
char address = 0x08; // Run I2C Scanner to get address
const int chipSelect = 10;
File myFile;

//run chip setup
void setup() {
  Wire.begin(); //join i2c bus as master/slave
  Serial.begin(9600); //set data rate for serial transmiossion
  sd_setup();
  
}

//main loop
void loop() {
  
  tof_read();
  myFile = SD.open("tof.txt", FILE_WRITE);
  if(myFile){
    Serial.print("Writing to tof.txt");
    myFile.println(dist);
    myFile.close();
    Serial.println("done");
  }
  else{
    Serial.println("error opening tof.txt");
  }
  
  linear_read();
  myFile = SD.open("linear.txt", FILE_WRITE);
  if(myFile){
    Serial.print("Writing to linear.txt");
    myFile.println(val);
    myFile.close();
    Serial.println("done");
  }
  else{
    Serial.println("error opening linear.txt");
  }
  
  delay(500);
}

//setup the sd card
void sd_setup(){
  while(!Serial){
    ;
  }
  Serial.print("Initialising SD card...");

  if(!SD.begin(chipSelect)){
    Serial.println("Card failed, or not present");
    return;
  }
  Serial.println("Card initiliased");

}

// read in the distance from the mappydot+ and print it
void tof_read(){  
  Wire.requestFrom(address, 2);
  dist = Wire.read() << 8; dist |= Wire.read();
  Serial.println(dist);
}

//read in the value of the potentiometer scaled from 0-1023
//and print it
void linear_read(){
  val = analogRead(potPin);
  Serial.println(val);
}
