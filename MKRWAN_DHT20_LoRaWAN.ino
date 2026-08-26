/*
  MKRWAN_DHT20_LoRaWAN.ino

  Lecture d'un capteur DHT20 (température / humidité) et envoi périodique
  des mesures via LoRaWAN (activation OTAA) vers The Things Network (TTN).

  Matériel :
    - Arduino MKR WAN 1310
    - Capteur DHT20 (I2C : VDD, SDA, GND, SCL)

  IMPORTANT :
    Les identifiants de connexion (App EUI / App Key) ne sont JAMAIS écrits
    directement dans ce fichier. Ils sont définis dans un fichier séparé
    "arduino_secrets.h" qui ne doit PAS être publié sur GitHub
    (voir .gitignore et arduino_secrets.h.template).
*/

#include <MKRWAN.h>
#include <DFRobot_DHT20.h>

LoRaModem modem;
DFRobot_DHT20 dht20;

// Décommenter si vous utilisez le module Murata en externe
// LoRaModem modem(Serial1);

#include "arduino_secrets.h"

uint32_t dur_entre_mess = 10000; // ms, intervalle entre deux envois

// Les valeurs sensibles sont définies dans l'onglet Secret / arduino_secrets.h
String appEui = SECRET_APP_EUI;
String appKey = SECRET_APP_KEY;

// Variables
String msg = "";
unsigned long duree;
int compteur = 0;

void setup() {
  Serial.begin(115200);

  while (dht20.begin()) {
    Serial.println("Initialise sensor failed");
    delay(1000);
  }

  Serial.setTimeout(1500);

  if (!modem.begin(EU868)) {
    Serial.println("Pb avec le module LoRa !");
    while (1) {}
  }

  int connected = modem.joinOTAA(appEui, appKey);
  if (!connected) {
    Serial.println("Pb pour atteindre une gateway LoRa. Déplacez-vous pour être dans la zone de réception d'une gateway. Avez-vous rentré les bonnes clés ?");
    while (1) {}
  } else {
    Serial.println("\r\nConnexion en OTAA réussie !");
  }

  modem.minPollInterval(60);
}

void loop() {
  duree = millis();
  while (millis() - duree < dur_entre_mess) {
    // attente entre deux mesures
  }

  float temperature = dht20.getTemperature();
  float humidite = dht20.getHumidity() * 100;

  Serial.print("temperature:"); Serial.print(temperature); Serial.print("°C");
  Serial.print("   humidity:"); Serial.print(humidite); Serial.println(" %RH");

  msg = String(temperature) + "!" + String(humidite);

  modem.beginPacket();
  modem.print(msg);
  modem.endPacket(true);

  Serial.println(msg);
}
