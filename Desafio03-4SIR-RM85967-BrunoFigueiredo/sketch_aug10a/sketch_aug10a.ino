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

void setup() 
{
  //inicialia c sensor
  dht.begin();

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
  json["temperatura"] = temp;
  json["umidade"] = umi;

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
