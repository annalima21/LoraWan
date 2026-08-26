/*
  config_application_TEMPLATE.h

  Fichier de configuration pour l'émetteur STM32 (Séance 01 - Mise en place
  d'une communication LoRa).

  Copiez ce fichier en "config_application.h" dans le projet STM32CubeIDE
  et remplissez les valeurs récupérées dans la console TTN (onglet
  "Activation information" de votre End Device).

  NE JAMAIS committer un "config_application.h" contenant de vraies clés :
  ce fichier ne doit servir que de modèle (template).
*/

//#define ACTIVATION_MODE       ABP    //ABP or OTAA
#define ACTIVATION_MODE          OTAA   //ABP or OTAA
#define CLASS                    CLASS_A //CLASS_A or CLASS_C
#define SPREADING_FACTOR         7
#define ADAPTIVE_DR              false
#define CONFIRMED                false
#define APP_PORT                 15

#define SEND_BY_PUSH_BUTTON      false
#define FRAME_DELAY              10000
#define PAYLOAD_HELLO            true
#define PAYLOAD_TEMPERATURE      false
#define PAYLOAD_HUMIDITY         false
#define CAYENNE_LPP              false
#define LOW_POWER                false

// --------------------------------------------------------------------
// Identifiants du device (à récupérer dans la console TTN)
// --------------------------------------------------------------------

#define devEUI_                  { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 }

// Configuration pour le mode d'activation ABP
#define devAddr_                 ( uint32_t )0x00000000
#define nwkSKey_                 00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00
#define appSKey_                 00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00

// Configuration pour le mode d'activation OTAA
#define appKey_                  00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00
#define appEUI_                  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }
