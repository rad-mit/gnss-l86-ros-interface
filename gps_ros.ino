#include <ros.h>
#include <std_msgs/Float64.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#define rxGPS 0
#define txGPS 1

 
long lat, lon;
SoftwareSerial gpsSerial(rxGPS, txGPS);
TinyGPSPlus gps;

ros::NodeHandle nh;

std_msgs::Float64 str_msg;
ros::Publisher chatter("chatter", &str_msg);

char hello[13] = "hello world!";

void setup()
{
   nh.initNode();
   nh.advertise(chatter);
   Serial.begin(9600); // connect serial
   gpsSerial.begin(9600); // connect gps sensor
   nh.getHardware()->setBaud(9600);
}

void loop()
{
   while (gpsSerial.available())     // check for gps data
  {
    if (gps.encode(gpsSerial.read()))   // encode gps data
    {
      Serial.print("SATS: ");
      Serial.println(gps.satellites.value());
      Serial.print("LAT: ");
      Serial.println(gps.location.lat(), 6);
      Serial.print("LONG: ");
      Serial.println(gps.location.lng(), 6);
      Serial.print("ALT: ");
      Serial.println(gps.altitude.meters());
      Serial.print("SPEED: ");
      Serial.println(gps.speed.mps());
 
      Serial.print("Date: ");
      Serial.print(gps.date.day()); Serial.print("/");
      Serial.print(gps.date.month()); Serial.print("/");
      Serial.println(gps.date.year());
 
      Serial.print("Hour: ");
      Serial.print(gps.time.hour()); Serial.print(":");
      Serial.print(gps.time.minute()); Serial.print(":");
      Serial.println(gps.time.second());
      Serial.println("---------------------------");
      //delay(2000);

   str_msg.data = gps.location.lat();
   chatter.publish( &str_msg );
   }
  }

   str_msg.data = gps.location.lat();
   chatter.publish( &str_msg );
   nh.spinOnce();
   delay(1000);
}
