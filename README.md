# Réseau LoRaWAN — Système de mesure et supervision environnementale

Projet BUT2 GEII (IUT Saint-Étienne / Université Jean Monnet) : capture de
données environnementales (température, humidité) via un capteur DHT20,
transmission longue portée en LoRaWAN, traitement Node-RED et pilotage
d'un relais 220V.

## Architecture

```
Capteur DHT20 --I2C--> Arduino MKR WAN 1310 --LoRaWAN--> Gateway --> TTN --> Node-RED --> Dashboard
                                                                                  |
                                                                                  v
                                                                     Downlink --> Relais 220V (lampe)
```

## Matériel utilisé

- Arduino MKR WAN 1310 (antenne LoRa intégrée)
- Capteur DHT20 (I2C : VDD, SDA, GND, SCL)
- Gateway LoRaWAN Stratagem
- Carte PCB personnalisée (relais 220V, transistor BC337, diode de roue libre 1N4148)
- Serveur The Things Network (TTN), Frequency Plan Europe 863-870 MHz

## Contenu du dépôt

- `arduino/MKRWAN_DHT20_LoRaWAN.ino` — sketch principal : lecture du DHT20 et envoi LoRaWAN (OTAA)
- `arduino/arduino_secrets.h.template` — modèle du fichier de clés (à copier en `arduino_secrets.h`, non versionné)
- `stm32/config_application_TEMPLATE.h` — configuration de l'émetteur STM32 utilisé en séance 01 (test point à point)
- `node-red/decode_payload.js` — function node : décodage du message uplink (température / humidité)
- `node-red/encode_downlink_command.js` — function node : encodage d'une commande downlink (pilotage du relais)

## Configuration de la Gateway (TTN)

| Paramètre | Valeur |
|---|---|
| Server URL | eu1.cloud.thethings.network |
| Port Up / Down | 1700 |
| Frequency Plan | Europe 863-870 MHz, SF9 recommandé |

## Sécurité

Les identifiants de connexion (App EUI, App Key, DevEUI, clés de session)
ne sont **jamais** committés dans ce dépôt. Ils doivent être placés dans
`arduino/arduino_secrets.h` (copié depuis le `.template`) ou dans
`stm32/config_application.h` (copié depuis le `_TEMPLATE`), tous deux
listés dans `.gitignore`.

## Étapes du projet

1. **Étude de concept** — choix de la technologie LoRaWAN et des composants
2. **Prototypage** — connexion DHT20 + Arduino MKR WAN 1310, configuration TTN
3. **Intégration Node-RED** — débogage des flux, validation de bout en bout
4. **Dashboard** — visualisation température / humidité en temps réel
5. **Développement électronique** — conception d'une carte PCB pour piloter un relais
6. **Carte de commande** — fabrication physique de la carte (schéma Proteus, PCB, boîtier)
7. **Système en fonctionnement** — chaîne complète capteur → TTN → Node-RED → relais, protocole Cayenne LPP
