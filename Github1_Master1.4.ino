//serial monitor set to NL &CR and 38400
#include <SoftwareSerial.h>

#define BT_NAME   "BT_Master"

#define SLAVE_ADDRESS "98d3,31,F65CE0"  //98d3:F65CE0

const int SNAP1=4; //master pin 8 has NC SNAP sensor on it.  
const int SNAP2=5; //each pin has 2 SNAP sensors in series to act as an AND gate
const int SNAP3=6; 
const int SNAP4=7;
const int SNAP5=8;
const int SNAP6=9;
const int SNAP7=10;
const int SNAP8=11;

const int ERRER=12; //pin outputs to LED if more than 1 socket is pulled

SoftwareSerial mySerial(2, 3); // RX, TX pins



void setup()
{
  pinMode(SNAP1,INPUT); //Snap sensor will receive a 3.3v or GND
  pinMode(SNAP2,INPUT); //second socket tray slot
  pinMode(SNAP3,INPUT);
  pinMode(SNAP4,INPUT);
  pinMode(SNAP5,INPUT);
  pinMode(SNAP6,INPUT);
  pinMode(SNAP7,INPUT);
  pinMode(SNAP8,INPUT);
  
  pinMode(ERRER,OUTPUT); //LED will show that there is an placement error
  
  Serial.begin(38400); //38400 baud rate is used in BT
  mySerial.begin(38400);
  

//sets up loop's variables
int s1=digitalRead(SNAP1); //read and save data. Is byte large enouggh??
int s2=digitalRead(SNAP2); //could this part be put into void setup()?
int s3=digitalRead(SNAP3);
int s4=digitalRead(SNAP4);
int s5=digitalRead(SNAP5);
int s6=digitalRead(SNAP6);
int s7=digitalRead(SNAP7);
int s8=digitalRead(SNAP8);

int error=(s1+s2+s3+s4+s5+s6+s7+s8); //sum of all
s1=0;
s2=0;
s3=0;
s4=0;
s5=0;
s6=0;
s7=0;
s8=0;
error=0;
}

void loop()
{
  
//sets up loop's variables...is it necessary to have this in setup and loop?
int s1=digitalRead(SNAP1); //read and save data. Is byte large enouggh??
int s2=digitalRead(SNAP2); //could this part be put into void setup()?
int s3=digitalRead(SNAP3);
int s4=digitalRead(SNAP4);
int s5=digitalRead(SNAP5);
int s6=digitalRead(SNAP6);
int s7=digitalRead(SNAP7);
int s8=digitalRead(SNAP8);

int error=(s1+s2+s3+s4+s5+s6+s7+s8); //sum of all

//Error control if more than one socket is removed
  if (error>1) //coding for errors. If more than 1 signal is receive. Flash the error
    {
      mySerial.write('i'); //don't tell the TCR that anything is wrong. Stay ideal
      digitalWrite(ERRER, HIGH); //Light RED LED on pin 7 if more than one socket is removed
      delay(500); //flash half a second
      digitalWrite(ERRER, LOW); //turn it back off
      error=0;
    }
  else //here we will check each state. a-h and k are for sockets. c=clear. i=ideal
    {
          if (s1==1) //if socket value is high, send message to signal TCR
            {
              mySerial.write('a');
              delay(500);
              //mySerial.write('c'); //code was originally placed to turn of LED
              s1=0; //reset value after
            }
          else if (s2==1)
          {
            mySerial.write('b');
            delay(500);
            //mySerial.write('c');
            s2=0;
          }
          else if (s3==1)
          {
            mySerial.write('d');
            delay(500);
            //mySerial.write('c');
            s3=0;
          }
          else if (s4==1)
          {
            mySerial.write('e');
            delay(500);
            //mySerial.write('c');
            s4=0;
          }
          else if (s5==1)
          {
            mySerial.write('f');
            delay(500);
            //mySerial.write('c');
            s4=0;
          }
          else if (s6==1)
          {
            mySerial.write('g');
            delay(500);
            //mySerial.write('c');
            s6=0;
          }
          else if (s7==1)
          {
            mySerial.write('h');
            delay(500);
            //mySerial.write('c');
            s7=0;
          }
          else if (s8==1)
          {
            mySerial.write('k'); //don't use i. i may be used for an ideal signal
            delay(500);
            //mySerial.write('c');
            s8=0;
          }
          else //if no socket is taken out, send the ideal signal to TCR
          {
            mySerial.write('i'); 
            delay(500);
          }
    }    
}
