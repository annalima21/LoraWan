// Node-RED - Function node
// Convertit l'état d'un bouton du dashboard (switch on/off) en une commande
// downlink TTN, encodée en base64 façon Cayenne LPP ([canal, type, valeur]).

let digitalValue = msg.payload ? 1 : 0;
let payload = Buffer.from([1, 0, digitalValue * 100]).toString("base64");

msg.payload = {
    "downlinks": [
        {
            "f_port": 1,
            "frm_payload": payload,
            "priority": "NORMAL"
        }
    ]
};

return msg;
