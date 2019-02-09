#include <SoftwareSerial.h>
#include <SPI.h>
#include <SD.h>
#include <TinyGPS.h> 


File myFile;

float lat = 28.5458,lon = 77.1703; // create variable for latitude and longitude object  
int year;
byte month, day, hour, minute, second, hundredths;
unsigned long chars;
unsigned short sentences, failed_checksum;

TinyGPS gps; // create gps object 

//Create software serial object to communicate with GPS
SoftwareSerial gpsSerial(5, 3);
 
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
      
      myFile = SD.open("newdata.txt", FILE_WRITE);

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
      Serial.print(hour+2, DEC);
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

      myFile.print("Latitude:"); 
      myFile.print(lat,15); 
      myFile.print(";"); 
      myFile.print("Longitude:"); 
      myFile.print(lon,15);
      myFile.print(";"); 
      myFile.print("Speed in kmph:"); 
      myFile.println(gps.f_speed_kmph()); 
      myFile.print("Date: ");
      myFile.print(month, DEC);
      myFile.print("/");
      myFile.print(day, DEC);
      myFile.print("/");
      myFile.print(year);
      myFile.print(" Time: ");
      myFile.print(hour+10, DEC);
      myFile.print(":");
      myFile.print(minute, DEC);
      myFile.print(":");
      myFile.print(second, DEC);
      myFile.print(".");
      myFile.println(hundredths, DEC);   
//    // close the file:
    myFile.close();
//    Serial.println("done.");
//  } else {
//    // if the file didn't open, print an error:
//    Serial.println("error opening test.txt");
  }
   
  }
  //Read Arduino IDE Serial Monitor inputs (if available) and send them to SIM800
}
