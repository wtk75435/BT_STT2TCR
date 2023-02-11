//Serial monitor set to NL & CR and 38400
#include <SoftwareSerial.h>

#define BT_NAME   "BT_Slave"

const int LED1 = 8; //pin 8
const int LED2 =9;

//Using RX0 and TX1 of Slave arduino
//SoftwareSerial mySerial(2, 3); // RX, TX leave out and connect to RX0 and TX0 ports

void setup()
{
  Serial.begin(38400);

  /*mySerial.begin(38400);
  Serial.println("Arduino receiver");

  mySerial.print("AT\r\n");
  delay(200);
  mySerial.print("AT+RMAAD\r\n");
  delay(200);
  mySerial.print("AT+ADDR?\r\n");
  delay(200);

  mySerial.print("AT+NAME="+String(BT_NAME)+"\r\n");
  delay(200);
  mySerial.print("AT+PSWD=\"1234\"\r\n");
  delay(200);
  mySerial.print("AT+ROLE?\r\n");
  delay(200);
  mySerial.print("AT+UART=38400,0,0\r\n");
  delay(500);*/
  
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
}

void loop()
{
  //below is the code to receive messages from the master
  /*if (mySerial.available())
    Serial.write(mySerial.read());*/
    //the below code tried and failed to control LED 8
    /*if (mySerial.read()==0)
      digitalWrite(LED, HIGH);
      delay(500);
      digitalWrite(LED, LOW);
      delay(500);*/
      
    
    //below is the code to send messages to the master. Not necessary for this project
  /*if (Serial.available())
    mySerial.write(Serial.read());*/
    
    if(Serial.available()>0)//if serial is present
      {
        char data=Serial.read();//read the data from master
        switch(data) // a=1, b=2, c=clear
        {
          case 'a':digitalWrite(8,HIGH); break; //turn on LED for s1
          case 'b':digitalWrite(9, HIGH); break; //turn on LED for s2
          case 'c':(digitalWrite(8,LOW)); (digitalWrite(9,LOW)); break; // and digitalWrite(9,LOW)); break; //turn off LEDs need one for each
          default : break;
          
        }
        Serial.println(data); //print what is received
      }
      delay(50);//wait before moving
}