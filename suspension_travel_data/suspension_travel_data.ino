//include required library header files
#include<Wire.h>
#include<SPI.h>
#include<SD.h>

//setup some global variables
int dist, val, potPin;
char address = 0x08; // Run I2C Scanner to get address
const int chipSelect = 4;

//run chip setup
void setup() {
  Wire.begin(); //join i2c bus as master/slave
  Serial.begin(9600); //set data rate for serial transmiossion
  sd_setup();
  
}

//main loop
void loop() {
  tof_read();
  sd_write("tof.txt", val);
  linear_read(); 
  sd_write("linear_pot.txt", dist);
  
  delay(10);
}

//setup the sd card
void sd_setup(){
  while(!Serial){
    ;
  }
  Serial.print("Initialising SD card...");

  if(!SD.begin(chipSelect)){
    Serial.println("Card failed, or not present");
    while(1);
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

void sd_write(String file_name, int sensor_val){

  String data = "";

  for(int analogPin = 0; analogPin <3; analogPin++){
    data += String(sensor_val);
    if(analogPin < 2){
      data += ",";
    }
  }

  File file = SD.open(file_name, FILE_WRITE);

  if (file) {
    file.println(data);
    file.close();
    // print to the serial port too:
    Serial.println(data);
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening data file");
  }

}
