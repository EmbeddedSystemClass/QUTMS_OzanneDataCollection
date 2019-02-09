#include <SoftwareSerial.h>
#include <SPI.h>
#include <SD.h>
#include <TinyGPS.h> 


const int xpin = A0;
const int ypin = A1;
const int zpin = A2;


File myFile,speedd,latt,lonn,accel_x,accel_y,accel_z;

float lat = 28.5458,lon = 77.1703; // create variable for latitude and longitude object  
int year;
byte month, day, hour, minute, second, hundredths;
unsigned long chars;
unsigned short sentences, failed_checksum;

TinyGPS gps; // create gps object 

//Create software serial object to communicate with GPS
SoftwareSerial gpsSerial(8, 3);
 
void setup() {
  //Begin serial comunication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);
  while(!Serial);
   
  //Being serial communication witj Arduino and GPS Module //Important rate must be 9600
  gpsSerial.begin(9600);
  delay(1000);
   
  Serial.println("GPS Setup Complete!");

  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
}
 
void loop() {
  //Read SIM800 output (if available) and print it in Arduino IDE Serial Monitor
  if(gpsSerial.available()){

//    Serial.write(gps.read());

    if(gps.encode(gpsSerial.read())){
      

      gps.f_get_position(&lat,&lon);
      Serial.print("Latitude:"); 
      Serial.print(lat,15); 
      Serial.print(";"); 
      Serial.print("Longitude:"); 
      Serial.print(lon,15);
      Serial.print(";"); 
      Serial.print("Speed in kmph:"); 
      Serial.println(gps.f_speed_kmph()); 
      gps.crack_datetime(&year,&month,&day,&hour,&minute,&second,&hundredths); 
      Serial.print("Date: ");
      Serial.print(month, DEC);
      Serial.print("/");
      Serial.print(day, DEC);
      Serial.print("/");
      Serial.print(year);
      Serial.print(" Time: ");
      Serial.print(hour-2, DEC);
      Serial.print(":");
      Serial.print(minute, DEC);
      Serial.print(":");
      Serial.print(second, DEC);
      Serial.print(".");
      Serial.println(hundredths, DEC);
//      }


//    if (myFile) {
//    Serial.print("Writing to test.txt...");
//    myFile.print(gps.read());

      speedd = SD.open("speed3.txt", FILE_WRITE);
      speedd.println(gps.f_speed_kmph()); 
      speedd.close();

      lonn = SD.open("lon3.txt", FILE_WRITE);

      lonn.println(lon,15); 
      lonn.close();

      latt = SD.open("lat3.txt", FILE_WRITE);
      latt.println(lat,15); 
      latt.close();



      
      myFile = SD.open("time.txt", FILE_WRITE);
      myFile.print(hour-2, DEC);
      myFile.print(":");
      myFile.print(minute, DEC);
      myFile.print(":");
      myFile.println(second, DEC);
//    // close the file:
    myFile.close();

      int x = analogRead(xpin);
  int y = analogRead(ypin);
  int z = analogRead(zpin);

  float zero_G = 512.0;
 
  float scale = 102.4;

  accel_x = SD.open("accel_x.txt", FILE_WRITE);
  Serial.print(((float)x - 331.5)/65*9.8);
  accel_x.println(((float)x - 331.5)/65*9.8);
  accel_x.close();
  Serial.print(",");
  accel_y = SD.open("accel_y.txt", FILE_WRITE);
  Serial.print(((float)y - 329.5)/68.5*9.8);
  accel_y.print(((float)y - 329.5)/68.5*9.8);
  accel_y.close();
  Serial.print(",");
  accel_z = SD.open("accel_z.txt", FILE_WRITE);
  Serial.println(((float)z - 340)/68*9.8);
  accel_z.println(((float)z - 340)/68*9.8);
  accel_z.close();
  
//    Serial.println("done.");
//  } else {
//    // if the file didn't open, print an error:
//    Serial.println("error opening test.txt");
  }
   
  }
  //Read Arduino IDE Serial Monitor inputs (if available) and send them to SIM800
}
