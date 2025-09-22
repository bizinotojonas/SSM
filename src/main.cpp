#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Ultrasonic.h>
#define col 16
#define lin 2
#define ende 0x27

LiquidCrystal_I2C
lcd(ende,col,lin);
void sensorref();
void displaywrite();
void sensoread();
void inversor();
void sisoutput();
void sduni();
void sname();
void suni();
// sensor ultrasonico
Ultrasonic 
ultrasonic(A3, A2);
int const sent = A1; //tipo de sensor
int const sens = A2; //leitura do sensor
int const sensa = A3; //sensor auxiliar
int const sc = A0; //shutdown config
int const inv= 2; //inversor
int const invoff = 8;
int const invon = 12;
int const sisexit = 7; //saida digital do sistema
int invorder = 0; //solicitação de inversor
int invmode = LOW;
int sensorstate = 0; //leitura do sensor
int sensortype = 0; //tipo do sensor
int sensorauxstate = 0; //leitura do sensor auxiliar
int shutdownpercent = 0; //percentual de shutdown
int sensoroutput = 0; //valor final do sensor
int shutdownstate = 0; //leitura do shutdown
int shutdownstateinunit = 0; //valor do shutdown em unidades
const char* sensorunit = ""; //unidade do sensor
const char* sensortypename = ""; //nome do tipo de sensor
void setup() {
  pinMode(sc,INPUT);
  pinMode(inv, INPUT_PULLUP);
  pinMode(invon, OUTPUT);
  pinMode(invoff, OUTPUT);
  pinMode(sisexit, OUTPUT);
  lcd.init();
  lcd.backlight();
  lcd.clear();

}

void loop() {
  sensoread();
  inversor();
  sensorref();
  suni();
  sname();
  sduni();
  sisoutput();
  displaywrite();
}



void sisoutput()
{
  // definir saida do sistema
  if (sensoroutput >= shutdownstateinunit && invmode == LOW)
  {
    digitalWrite(sisexit, HIGH);
  }
  else if (sensoroutput < shutdownstateinunit && invmode == LOW)
  {
    digitalWrite(sisexit, LOW);
  }
  else if (sensoroutput >= shutdownstateinunit && invmode == HIGH)
  {
    digitalWrite(sisexit, LOW);
  }
  else if (sensoroutput < shutdownstateinunit && invmode == HIGH)
  {
    digitalWrite(sisexit, HIGH);
  }
}

void sensoread()
{
  // fazer as leituras dos sensores analogicos:
  shutdownstate = analogRead(sc);
  sensorstate = analogRead(sens);
  sensortype = analogRead(sent);
  sensorauxstate = analogRead(sensa);
  shutdownpercent = (map(shutdownstate, 0, 1023, 0, 100));
}
void inversor()
{
  // controlar o inversor
  void inversor();
  if (invmode == LOW)
  {
    digitalWrite(invon, LOW);
    digitalWrite(invoff, HIGH);
  }
  else if (invmode == HIGH)
  {
    digitalWrite(invon, HIGH);
    digitalWrite(invoff, LOW);
  }
  invorder = digitalRead(inv);
  if (invorder == LOW)
  {
    invmode = !invmode;
    delay(200);
  }
}

void displaywrite()
{
  // escrever no diplay lcd
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("S:");
  lcd.print(sensortypename);
  lcd.setCursor(0, 1);
  lcd.print("SP:");
  lcd.print(shutdownstateinunit);
  lcd.print(sensorunit);
  lcd.setCursor(8, 1);
  lcd.print("V:");
  lcd.print(sensoroutput);
  lcd.print(sensorunit);
  delay(250);
}

void sensorref()
{
  // refinar sinais para unicos e em unidades determinadas
  if (sensortypename == "Ultrassonico")
  {
    sensorstate = sensorstate / 1023;
    sensorauxstate = sensorauxstate / 1023;
    sensoroutput = ultrasonic.read(CM);
  }
  else if (sensortypename == "Luminosidade")
  {
    sensorstate = map(sensorstate, 0, 1023, 0, 100);
    sensoroutput = sensorstate;
  }
  else if (sensortypename == "Temperatura")
  {
    sensorstate = map(sensorstate, 0, 1023, -55, 150);
    sensoroutput = sensorstate;
  }
}

void suni()
{
  // definir unidade do sensor
  if (sensortypename == "Luminosidade")
    sensorunit = "%";
  else if (sensortypename == "Ultrassonico")
    sensorunit = "cm";
  else if (sensortypename == "Temperatura")
    sensorunit = "C";
}

void sname()
{
  // definir nome do sensor
  if (sensortype == 1023)
    sensortypename = "Luminosidade";
  else if (sensortype == 512)
    sensortypename = "Ultrassonico";
  else if (sensortype == 0)
    sensortypename = "Temperatura";
}

void sduni()
{
  // definir valor do shutdown em unidades
  if (sensortypename == "Ultrassonico")
  {
    shutdownstateinunit = map(shutdownstate, 0, 1023, sensorauxstate, 400);
  }
  else if (sensortypename == "Temperatura")
  {
    shutdownstateinunit = map(shutdownstate, 0, 1023, -55, 150);
  }
  else if (sensortypename == "Luminosidade")
  {
    shutdownstateinunit = map(shutdownstate, 0, 1023, 0, 100);
  }
}
