#include<SoftwareSerial.h>
#include "DHT.h"
#define DHTTYPE DHT11
DHT dhtsensor(4,DHT11);
//#define DHTPIN 4

SoftwareSerial GSM(9,10);//rx,tx
String str="";
char ch;
String num;
int st_on;
int st_off;
void setup(){
  pinMode(12,OUTPUT);
  Serial.begin(9600);
  GSM.begin(9600);
  GSM.println("AT");
  delay(100);
  GSM.println("AT+CMGF=1");
  delay(100);
  dhtsensor.begin();
  GSM.println("AT+CNMI=2,2,0,0,0");
}
void loop(){
    if(GSM.available()>0){
      while(GSM.available()>0){
        ch=GSM.read();
        str=str+ch;
      }
        Serial.println(str);
        getnumber();
      }
      st_on=str.indexOf("ON");
      if(st_on != -1 && (num == "+917016587968" || num == "+919182804546")){
        digitalWrite(12,1);
        SendMessage();
        Serial.println("Bulb On");
        send_msg("Bulb On");
        }
        st_off = str.indexOf("OFF");
        if(st_off != -1 && (num == "+917016587968" ||  num == "+919182804546")) {
          digitalWrite(12,LOW);
          SendMessage1();
          Serial.println("Bulb Off");
          send_msg("Bulb Off");
          }
        SendDetails();
        delay(20000);
          str = "";
    }
void getnumber(){
  num = str.substring(9,22);
  Serial.print("Mobile num is:");
  Serial.print(num);
  delay(2000);
  }
void send_msg(String msg){
  GSM.print("AT+CMGS");
  GSM.print('"');
  GSM.print(num);
  GSM.println('"');
  delay(1000);
  GSM.print(msg);
  GSM.print(char(26));
  }
 void SendMessage()
{
  GSM.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  //GSM.println("AT+CMGS=\"s\"\r"); // Replace x with mobile number
  GSM.println("AT+CMGS=\"+917016587968\"\r");
  GSM.println("AT+CMGS=\"+919182804546\"\r");
  delay(1000);
  GSM.println("motor on");// The SMS text you want to send
  delay(100);
  GSM.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}

 void SendMessage1()
{
  GSM.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  GSM.println("AT+CMGS=\"+919182804546\"\r"); // Replace x with mobile number
  GSM.println("AT+CMGS=\"+917016587968\"\r");
  delay(1000);
  GSM.println("motor off");// The SMS text you want to send
  delay(100);
  GSM.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}
 void SendDetails()
{
  GSM.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  GSM.println("AT+CMGS=\"+919182804546\"\r"); // Replace x with mobile number
 // GSM.println("AT+CMGS=\"+917016587968\"\r");
  delay(1000);
  float t = dhtsensor.readTemperature();
  float h = dhtsensor.readHumidity();
  GSM.println(t);
  GSM.println(h);// The SMS text you want to send
  delay(100);
  GSM.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}

