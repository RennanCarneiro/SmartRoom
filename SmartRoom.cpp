#include <Servo.h>
#define pinServo 13

Servo myservo;
int sensorLuz = 4;
float echo = 11;
int trigger = 12;
int ledLuz = 6;
int estadoBotao = 0;
const int temperaturaPin = A5; 
const int ledFrioPin = 5;      
const int ledQuentePin = 2;
const int ledAmbientePin = 3;
int posicao_inicial_servo = 0;

void setup()
{
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(sensorLuz, INPUT);
  pinMode(ledLuz, OUTPUT);
  pinMode(ledFrioPin, OUTPUT);    
  pinMode(ledQuentePin, OUTPUT); 
  pinMode(ledAmbientePin, OUTPUT);
  myservo.attach(pinServo);
  Serial.begin(9600);  
  myservo.write(0);
}

void loop()
{
  
  
  //sensor luz
  estadoBotao = digitalRead(sensorLuz) ;
  if (estadoBotao == HIGH) {
    digitalWrite(ledLuz, HIGH);
    delayMicroseconds(10);
  } 
  else {
    digitalWrite(ledLuz, LOW);
  }
  //sensor temperatura
  int temperatura = analogRead(temperaturaPin);
  float temperaturaC = (temperatura * 5.0 / 1024.0 - 0.5) * 100.0; 

  if (temperaturaC <= 19.0) {       
    digitalWrite(ledFrioPin, HIGH);  
    digitalWrite(ledQuentePin, LOW);
    digitalWrite(ledAmbientePin, LOW);
  }
  else if(temperaturaC > 20 && temperaturaC < 36){ 
    digitalWrite(ledFrioPin, LOW); 
    digitalWrite(ledQuentePin, LOW);
    digitalWrite(ledAmbientePin, HIGH); 
  } else {                         
    digitalWrite(ledFrioPin, LOW); 
    digitalWrite(ledAmbientePin, LOW);
    digitalWrite(ledQuentePin, HIGH);
  }
  //sensor porta
   digitalWrite(trigger, LOW);        
  delay(2);              
  digitalWrite(trigger, HIGH);       
  delay( 10 );             
  digitalWrite(trigger, LOW);        
  long duration = pulseIn(echo, HIGH); 
  double distancia = duration/58 ;

  if(distancia < 60)
  	myservo.write(90);
  else 
    myservo.write(0);   }
