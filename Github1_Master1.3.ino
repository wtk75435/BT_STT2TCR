//serial monitor set to NL &CR and 38400
#include <SoftwareSerial.h>

#define BT_NAME   "BT_Master"

#define SLAVE_ADDRESS "98d3,31,F65CE0"  //98d3:F65CE0

const int SNAP1=8; //master pin 8 has NC SNAP sensor on it
const int SNAP2=9; //master pin 9 has NC Snap sensor on it
const int ERRER=7;


SoftwareSerial mySerial(2, 3); // RX, TX pins

//digitalWrite(LED,LOW); //start with LED off

void setup()
{
  pinMode(SNAP1,INPUT); //Snap sensor will receive a 3.3v or GND
  pinMode(SNAP2,INPUT); //second socket tray
  pinMode(ERRER,OUTPUT); //socket tray will show that there
  Serial.begin(38400);

  mySerial.begin(38400);
  //Serial.println("Arduino Sender");

//Below are commands for setting up HC-05
//  mySerial.print("AT\r\n");
//  updateSerial();
//  delay(200);
//  mySerial.print("AT+RMAAD\r\n");
//  updateSerial();
//  delay(200);
//  mySerial.print("AT+ROLE=1\r\n");
//  updateSerial();
//  delay(200);  
//  mySerial.print("AT+NAME="+String(BT_NAME)+"\r\n");
//  updateSerial();
//  delay(200);
//  mySerial.print("AT+PSWD=\"1234\"\r\n");
//  updateSerial();
//  delay(200);
//  mySerial.print("AT+BIND="+String(SLAVE_ADDRESS)+"\r\n");
//  updateSerial();
//  delay(200);
//  mySerial.print("AT+UART=38400,0,0\r\n");
//  updateSerial();
//  delay(500);
//  mySerial.print("AT+UART?\r\n");
//  //updateSerial();
//  delay(200);
//}
//
//void updateSerial(void)
//{

//begin variables at zero

//sets up loop's variables
int s1=digitalRead(SNAP1); //read and save data. Is byte large enouggh??
int s2=digitalRead(SNAP2); //could this part be put into void setup()?
int error=(s1+s2); //sum of all
s1=0;
s2=0;
error=0;
}

void loop()
{
//below is used to RECEIVE code from Slave---->Not necessary for this application
//  if (mySerial.available())
//      Serial.write(mySerial.read());


//sets up loop's variables
int s1=digitalRead(SNAP1); //read and save data. Is byte large enouggh??
int s2=digitalRead(SNAP2); //could this part be put into void setup()?
int error=(s1+s2); //sum of all




//Error control and Sending which socket is chosen
  if (error>1) //coding for errors. If more than 1 signal is receive. Flash the error
    {
      digitalWrite(ERRER, HIGH); //Light RED LED on pin 7 if more than one socket is removed
      delay(500); //flash half a second
      digitalWrite(ERRER, LOW); //turn it back off
      s1=0;//clear variables
      s2=0;
    }
  else //here we will check each state. a=1, b=2, and c=clear
    {
          if (s1==1) //if socket value is high, send message to signal TCR
            {
              mySerial.write('a');
              delay(500);
              mySerial.write('c');
              Serial.print("s1 is");
              Serial.println(s1);
              Serial.print("s2 is");
              Serial.println(s2);
              s1=0;
            }
          else if (s2==1)
          {
            mySerial.write('b');
            delay(500);
            mySerial.write('c');
            s2=0;
          }
          else //if no socket is taken out, send the ideal signal to TCR
          {
            mySerial.write('c'); 
            delay(500);
          }
    }

    
    //below is used to SEND code to Slave------> this shouldn't be needed since code has individual write statements
//  if (Serial.available()) //sends anything available
//    mySerial.write(Serial.read());

     
}
