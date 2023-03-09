#include <Keypad.h>
#include <LiquidCrystal.h>

LiquidCrystal p(12,11,10,A1,A2,A3,A4);
const byte filas=4; 
const byte columnas=4;
char teclas[filas][columnas]=
{
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
   
byte pinFilas[filas]={9,8,7,6};
byte pinColumnas[columnas]={5,4,3,2};

Keypad teclado = Keypad(makeKeymap(teclas),pinFilas,pinColumnas,filas,columnas);
char tecla;
char clave[7];
char CA[7]="123456";
byte indice =0;
char clave2[2];
char EV[2]="1";
char EL[2]="2";
char ET[2]="3";
char AV[2]="4";
char AL[2]="5";
char ATB[2]="*";
byte indicador=0;
byte prueba=0;
byte menu=0;
byte luces=0;
byte vent=0;

void setup()
{
  Serial.begin(9600);
  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);

  p.begin(16,2);
  p.clear();
  p.setCursor(0,0);
  p.print("CLAVE ACCESO");
  
}

void loop()
{
  tecla= teclado.getKey();
  if(tecla)
  {
    clave[indice]= tecla; 
    p.setCursor(indicador,1);
    p.print(tecla);
    indicador++;
    indice++;
  }
  
  if (indice == 6)
  {
     if(!strcmp(clave, CA))
     {
      p.clear();
      p.setCursor(0,0);
      p.print("CORRECTA");
      p.setCursor(0,1);
      p.print("BIENVENIDO");
      delay(500);
      indice=0;
      indicador=0;
      p.clear();
      menu++;
     }
     else
     {
      p.clear();
      p.setCursor(0,0);
      p.print("INCORRECTO");
      delay(500);
      p.setCursor(0,0);
      p.print("CLAVE ACCESO");
      indice=0;
      indicador=0;
      }
  }
  
  if(menu==1)
  {
      p.setCursor(0,0);
      p.print("MENU:1-VENTILADOR");
      p.setCursor(0,1);
      p.print("2-LUZ *-BLOQUEAR");
    
    if(tecla)
    {
      clave2[prueba]= tecla; 
      p.setCursor(indicador,1);
      p.print(tecla);
      p.clear();
    }
    if(!strcmp(clave2, EV))
      {
        p.clear();
        p.setCursor(0,0);
        p.print("VENTILADORES ENCENDIDO");
        delay(500);
        clave2[prueba]=0;
        indicador=0;
        indice=0;
        vent=1;
        Serial.write(1);
      }
      if(!strcmp(clave2, EL))
      {
        p.clear();
        p.setCursor(0,0);
        p.print("LUCES ENCENDIDAS");
        delay(500);
        clave2[prueba]=0;
        indicador=0;
        indice=0;
        luces=1;
        Serial.write(2);
      }
    
      if(!strcmp(clave2, ET))
      {
        p.clear();
        p.print("TODO ENCENDIDO");
        delay(500);
        clave2[prueba]=0;
        indicador=0;
        indice=0;
        Serial.write(3);
       }
      if(!strcmp(clave2, AV))
      {
        p.clear();
        p.print("VENTILADORES APAGADOS");
        delay(500);
        clave2[prueba]=0;
        indicador=0;
        indice=0;
        Serial.write(50);
      }
      if(!strcmp(clave2, AL))
      {
        p.clear();
        p.print("LUCES APAGADAS");
        delay(1000);
        clave2[prueba]=0;
        indicador=0;
        indice=0;
        Serial.write(60);
      }
      if(!strcmp(clave2, ATB))
      {
        p.clear();
        p.print("APAGANDO Y BLOQUEANDO");
        delay(1000);
        clave2[prueba]=0;
        menu=0;
        indicador=0;
        indice=0;
        Serial.write(40);
        p.setCursor(0,0);
        p.print("CLAVE ACCESO");
      }
  }
}
