#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
// Modification des bytes d'horloge
const byte OC1A_PIN = 9;
const byte OC1B_PIN = 10;

const word PWM_FREQ_HZ = 20000; //Adjust this value to adjust the frequency
const word TCNT1_TOP = 16000000/(2*PWM_FREQ_HZ);

int deviceCount = 0;
float tempC;
// I/O settings
#define ONE_WIRE_BUS 4
#define FAN2 0
#define FAN 1
#define OPTO 2
#define BP 3
#define PWR 5
#define GND 7

//________________
OneWire oneWire(ONE_WIRE_BUS);	
DallasTemperature sensors(&oneWire);

//Variables
float T1 = 0;
float T2 = 0;

//Ajustable 
float Temp1 = 30;
float Temp2 = 80;

void setup() {
  pinMode (FAN,OUTPUT);
  pinMode (FAN2,OUTPUT);
  pinMode (OPTO,OUTPUT);
  pinMode (BP,INPUT);
  pinMode (PWR,OUTPUT);
  pinMode(GND,OUTPUT);
  digitalWrite(GND,LOW);
  digitalWrite(BP,HIGH); //Activation Pull-Up Bouton 
  sensors.begin(); //Activation Capteurs
  //Debug Atmega328p Arduino Nano
  Serial.begin(9600);
  Serial.print("Locating devices...");
  Serial.print("Found ");
  deviceCount = sensors.getDeviceCount();
  Serial.print(deviceCount, DEC);
  Serial.println(" devices.");
  Serial.println("");
 //_____________________

  //deviceCount = sensors.getDeviceCount();
}

void loop() {

//bouton   
int BP_State = digitalRead(BP);

if(BP_State == LOW){
  digitalWrite(OPTO,HIGH);
  delay(10); //anti rebond virtuel
}
else{
  digitalWrite(OPTO,LOW);
}
//______________


//Aquisition Temp 
sensors.requestTemperatures(); 
T1 = sensors.getTempCByIndex(0);
T2 = sensors.getTempCByIndex(1);
Serial.print("T1= ");
Serial.print(T1);
Serial.print(" , T2= ");
Serial.println(T2);
//______________

//FAN Temps régulation 
if (T1==-127)
{
 digitalWrite(13,HIGH);
}
else if (T2==-127)
{
  digitalWrite(13,HIGH);
}
else
{
  digitalWrite(13,LOW);
}


 

delay(100);

}