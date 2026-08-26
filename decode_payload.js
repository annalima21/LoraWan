// Node-RED - Function node
// Décode le message uplink reçu de TTN (via le noeud "mqtt in")
// et extrait température / humidité pour les widgets du dashboard.

let payload = msg.payload;
let temperature = payload.uplink_message.decoded_payload.temperature;
let humidite = payload.uplink_message.decoded_payload.humidite;

msg.payload = {
    temperature: temperature,
    humidite: humidite
};

return msg;
