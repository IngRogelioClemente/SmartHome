#include <LiquidCrystal.h>

LiquidCrystal p2(5,4,3,A2,A3,A4,A5);
int led1=13;
int led2=12;
int pir1=10;
int pir2=11;
int dato1;
int dato2;
int motor1=7;
int motor2=6;
int TMP1=0;
int TMP2=1;
float temp1=0;
float temp2=0;
int luz=0;
int aire=0;

void setup() 
{
  Serial.begin(9600);
  pinMode(9,OUTPUT);
  digitalWrite(9,HIGH);
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(pir1,INPUT);
  pinMode(pir2,INPUT);
  pinMode(motor1,OUTPUT);
  pinMode(motor2,OUTPUT);
  pinMode(TMP1,INPUT);
  pinMode(TMP2,INPUT);
  p2.begin(16,2);
  p2.clear();
  p2.setCursor(0,0);
  p2.print("TEMP1      TEMP2");
}

void loop() 
{
  int rec=Serial.read();
  switch(rec)
  {
    case 1:
    aire=1;
    break;

    case 2:
    luz=1;
    break;

    case 3:
    luz=1;
    aire=1;
    break;

    case 40:
    luz=0;
    aire=0;
    break;

    case 50:
    aire=0;
    break;

    case 60:
    luz=0;
    break;
  }
  
  dato1= digitalRead(pir1);
  dato2= digitalRead(pir2);
  if (dato1 == HIGH and luz == 1)
  {
    digitalWrite(led1,HIGH);
  }
  else
  {
    digitalWrite(led1,LOW);
  }
  if (dato2 == HIGH and luz == 1)
  {
    digitalWrite(led2,HIGH);
  }
  else
  {
    digitalWrite(led2,LOW);
  }

  temp1=map(analogRead(TMP1),0,1023,-50,450);
  temp2=map(analogRead(TMP2),0,1023,-50,450);
  p2.setCursor(0,1);
  p2.print(temp1);
  p2.setCursor(10,1);
  p2.print(temp2);

  if(aire == 0)
  {
    digitalWrite(motor1,LOW);
    digitalWrite(motor2,LOW);
  }
  if(aire == 1)
  {
    if(temp1>=21 or temp1>22)
    {
      digitalWrite(motor1,HIGH);
    }
    else
    {
      digitalWrite(motor1,LOW);
    }
  }
  if(aire == 1)
  {
    if(temp2>21 or temp2>=22)
    {
      digitalWrite(motor2,HIGH);
    }
    else
    {
      digitalWrite(motor2,LOW);
    }
  }
  
  delay(10);
}
