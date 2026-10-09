
#include "DHTesp.h"

const int DHT_PIN = 15;
const int LDR_PIN = 34;

const int BOTAO_N = 18;
const int BOTAO_P = 19;
const int BOTAO_K = 21;

const int RELE_PIN = 23;

DHTesp dhtSensor;

void setup() {
  Serial.begin(115200);

  dhtSensor.setup(DHT_PIN, DHTesp::DHT22);

  pinMode(BOTAO_N, INPUT_PULLUP);
  pinMode(BOTAO_P, INPUT_PULLUP);
  pinMode(BOTAO_K, INPUT_PULLUP);

  pinMode(RELE_PIN, OUTPUT);
  digitalWrite(RELE_PIN, HIGH);

  Serial.println("Sistema de Irrigacao Inteligente");
  Serial.println("--------------------------------");
}

void loop() {
  TempAndHumidity dados = dhtSensor.getTempAndHumidity();

  int leituraLDR = analogRead(LDR_PIN);

  bool nitrogenio = digitalRead(BOTAO_N) == LOW;
  bool fosforo = digitalRead(BOTAO_P) == LOW;
  bool potassio = digitalRead(BOTAO_K) == LOW;
  Serial.print("Leitura dos botoes: ");
 Serial.print(digitalRead(BOTAO_N));
 Serial.print(" ");
 Serial.print(digitalRead(BOTAO_P));
 Serial.print(" ");
Serial.println(digitalRead(BOTAO_K));

  float pH = (leituraLDR / 4095.0) * 14.0;
  float umidade = dados.humidity;

  bool bombaLigada = umidade < 40.0;

  digitalWrite(RELE_PIN, bombaLigada ? LOW : HIGH);

  Serial.println("\n--- Dados da plantacao ---");

  Serial.print("Temperatura: ");
  Serial.print(dados.temperature);
  Serial.println(" C");

  Serial.print("Umidade: ");
  Serial.print(umidade);
  Serial.println("%");

  Serial.print("pH estimado: ");
  Serial.println(pH);

  Serial.print("Nitrogenio (N): ");
  Serial.println(nitrogenio ? "Presente" : "Ausente");

  Serial.print("Fosforo (P): ");
  Serial.println(fosforo ? "Presente" : "Ausente");

  Serial.print("Potassio (K): ");
  Serial.println(potassio ? "Presente" : "Ausente");

  Serial.print("Bomba: ");
  Serial.println(bombaLigada ? "LIGADA" : "DESLIGADA");

  delay(2000);
}
