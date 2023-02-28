//Serial monitor set to NL & CR and 38400
#include <SoftwareSerial.h>

#define BT_NAME   "BT_Slave"

const int LED1 = 4; //pin 8
const int LED2 =5;
const int LED3 =6;
const int LED4 =7;
const int LED5 =8;
const int LED6 =9;
const int LED7 =10;
const int LED8 =11;

//Using RX0 and TX1 of Slave arduino

void setup()
{
  Serial.begin(38400);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(LED6, OUTPUT);
  pinMode(LED7, OUTPUT);
  pinMode(LED8, OUTPUT);
  
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
          case 'i': (digitalWrite(LED1,LOW));(digitalWrite(LED2,LOW));(digitalWrite(LED3,LOW));(digitalWrite(LED4,LOW));(digitalWrite(LED5,LOW));(digitalWrite(LED6,LOW));(digitalWrite(LED7,LOW));(digitalWrite(LED8,LOW)); break;
          case 'a':digitalWrite(LED1,HIGH); break; //turn on LED for s1
          case 'b':digitalWrite(LED2, HIGH); break; //turn on LED for s2
          case 'd':digitalWrite(LED3, HIGH); break;
          case 'e':digitalWrite(LED4, HIGH); break;
          case 'f':digitalWrite(LED5, HIGH); break;
          case 'g':digitalWrite(LED6, HIGH); break;
          case 'h':digitalWrite(LED7, HIGH); break;
          case 'k':digitalWrite(LED8, HIGH); break;
          //case 'c':(digitalWrite(8,LOW)); (digitalWrite(9,LOW)); break; // and digitalWrite(9,LOW)); break; //turn off LEDs need one for each
          default : break;
          
        }
        Serial.println(data); //print what is received
      }
      delay(50);//wait before moving
}
