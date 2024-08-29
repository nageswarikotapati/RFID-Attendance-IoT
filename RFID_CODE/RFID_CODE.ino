#include <ESP8266WiFi.h>
#include "ThingSpeak.h"

const char* ssid = "project01";   // your network SSID (name) 
const char* password = "project01";   // your network password

WiFiClient  client;

unsigned long myChannelNumber = 2509288;
const char * myWriteAPIKey = "IOKAQQ37J715OKF9";

#include<SoftwareSerial.h>
SoftwareSerial rfid(D7,D8);
String data=" ";

#include<LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);  // SCL-D1   SDA-D2

#define buzzer D5

#include<Servo.h>
Servo servo;

String name=" ";
String number=" ";


void setup()
{
  Serial.begin(9600);
  rfid.begin(9600);

  lcd.init();
  lcd.backlight();

  pinMode(buzzer,OUTPUT);
  digitalWrite(buzzer,LOW);

  servo.attach(D6);
  delay(1000);
  servo.write(0);
  delay(1000);

  // Connect to WiFi
  Serial.print("Connecting to WiFi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  ThingSpeak.begin(client);
  
  Serial.println("Connected!");
  Serial.println(WiFi.localIP());
}
void beep()
{
  digitalWrite(buzzer,HIGH);delay(500);digitalWrite(buzzer,LOW);delay(500);
  digitalWrite(buzzer,HIGH);delay(500);digitalWrite(buzzer,LOW);delay(500);
}
void loop()
{
  lcd.clear();
  lcd.print(" SCAN YOUR CARD ");
  delay(100);
  ThingSpeak.setField(1,name);
  ThingSpeak.setField(2,number);
  ThingSpeak.writeFields(myChannelNumber,myWriteAPIKey);
  
  if(rfid.available()>0)
  {
    beep();
    data=" ";
    name=" ";
    number=" ";
    data=rfid.readString();
    Serial.print("RFID data : ");Serial.println(data);
  }
  if(data=="01006BD83D8F")   //55357
  {
    beep();
    data=" ";
    name="    KEERTHANA   ";
    number="   22B01A0455   ";
    
    lcd.clear();
    lcd.print(" ATTENDENCE  OK ");
    delay(2000);
    lcd.clear();
    lcd.print(name);
    lcd.setCursor(0,1);
    lcd.print(number);
    servo.write(90);
    delay(3000);
    servo.write(0);
    delay(1000);
  }
  else if(data=="0100660F147C")   //03860
  {
    beep();
    data=" ";
    name="    NAGESWARI   ";
    number="   22B01A0456   ";
    
    lcd.clear();
    lcd.print(" ATTENDENCE  OK ");
    delay(2000);
    lcd.clear();
    lcd.print(name);
    lcd.setCursor(0,1);
    lcd.print(number);
    lcd.print(number);
    servo.write(90);
    delay(3000);
    servo.write(0);
    delay(1000);
  }
  else if(data=="54007170B5E0")   //28853
  {
    beep();
    data=" ";
    name="    LASYA   ";
    number="   22B01A0452   ";
    
    lcd.clear();
    lcd.print(" ATTENDENCE  OK ");
    delay(2000);
    lcd.clear();
    lcd.print(name);
    lcd.setCursor(0,1);
    lcd.print(number);
    lcd.print(number);
    servo.write(90);
    delay(3000);
    servo.write(0);
    delay(1000);
  }
  else if(data=="01006B07167B")   //01814
  {
    beep();
    data=" ";
    name="    SRAVANI   ";
    number="   22B01A0453   ";
    
    lcd.clear();
    lcd.print(" ATTENDENCE  OK ");
    delay(2000);
    lcd.clear();
    lcd.print(name);
    lcd.setCursor(0,1);
    lcd.print(number);
    lcd.print(number);
    servo.write(90);
    delay(3000);
    servo.write(0);
    delay(1000);
  }
  else if(data=="01006EE68A03")   //59018
  {
    beep();
    data=" ";
    name="    MAHITHA   ";
    number="   22B01A0451   ";
    
    lcd.clear();
    lcd.print(" ATTENDENCE  OK ");
    delay(2000);
    lcd.clear();
    lcd.print(name);
    lcd.setCursor(0,1);
    lcd.print(number);
    lcd.print(number);
    servo.write(90);
    delay(3000);
    servo.write(0);
    delay(1000);
  }
  else if(data=="01006F141D67")  //05149
  {
    beep();
    data=" ";
    name="    SWAROOPA   ";
    number="   22B01A0454   ";
    
    lcd.clear();
    lcd.print(" ATTENDENCE  OK ");
    delay(2000);
    lcd.clear();
    lcd.print(name);
    lcd.setCursor(0,1);
    lcd.print(number);
    lcd.print(number);
    servo.write(90);
    delay(3000);
    servo.write(0);
    delay(1000);
  }
}
