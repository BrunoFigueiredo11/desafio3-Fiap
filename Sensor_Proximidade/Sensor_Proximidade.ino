#include <ArduinoJson.h>
const int LED = 13;
const int TAMANHO = 200;
///// Sensor DTH
#include "DHT.h"
#define DHTPIN  7  //define o pino usado no arduino
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE); //declara a objeto da classe

////// Outras declarações
#define led 13 //define led conectado no pino 13
int pinoTrigger = 10; // Pino trigger 
// ligado ao trigger do sensor
int pinoEcho = 11; // Pino echo do sensor

void setup() 
{
  //inicialia c sensor
  dht.begin();
  
  pinMode(pinoTrigger, OUTPUT); // Define pino como saída
  pinMode(pinoEcho, INPUT); // Define pino como entrada
  
  //inicializa comunicação serial
  Serial.begin(9600);
  Serial.setTimeout(10);
  pinMode(LED,OUTPUT);

}

void loop() 
{
  StaticJsonDocument<TAMANHO> json; //Aloca buffer para objeto json

  // Faz a leitura da temperatura  
  float temp = dht.readTemperature();
  // faz a leitura da humidade
  float umi = dht.readHumidity();

  //formato de escrita do json


   digitalWrite(pinoTrigger, LOW); // Coloca nível baixo na saída
  delayMicroseconds(2); // Atraso de 2 us
  
  // Início da transmissão de pulsos
  digitalWrite(pinoTrigger, HIGH); // Coloca nível alto na saída
  delayMicroseconds(10); // Atraso de 10 us
  
  // Depois disso, são enviados 8 pulsos de 40kHz
  digitalWrite(pinoTrigger, LOW);
  
  long duracaoAlto = pulseIn(pinoEcho, HIGH); // Obtém duracao de tempo
  long distancia = usParaCm(duracaoAlto); // Obtém distância
  
  json["temperatura"] = temp;
  json["umidade"] = umi;
  json["distancia"] = distancia;

  serializeJson(json, Serial);
  Serial.println();

  //delay
  delay(500);

  if (Serial.available() > 0) {
      analogWrite(LED, 200);
    }else{
       analogWrite(LED, 0);
      }
  } 
  long usParaCm(long duracaoAlto) {
  
  long d = (duracaoAlto / 2) * .0343; // Calcula distância, 
  
  return d; // Retorna distância para chamador
  
}

  
