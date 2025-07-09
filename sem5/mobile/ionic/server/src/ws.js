import WebSocket from "ws";
import jwt from "jsonwebtoken";
import { jwtConfig } from "./utils.js";

let wss;

export const initWs = value => {
    wss = value;
    wss.on('connection', ws => {
        ws.on('message', message => {
            const { type, payload: { token } } = JSON.parse(message);
            console.log("MSG: " + message);
            if (type !== 'authorization') {
                ws.close();
                return;
            }
            console.log("TOKEN IS: " + token);
            try {
                ws.user = jwt.verify(token, jwtConfig.secret);
            } catch (err) {
                ws.close();
            }
        })
    });
};

export const broadcast = (userId, data) => {
    if (!wss) {
        return;
    }
    wss.clients.forEach(client => {
        if (client.readyState === WebSocket.OPEN && userId === client.user._id) {
            console.log(`broadcast sent to ${client.user.username}`);
            client.send(JSON.stringify(data));
        }
    });
};
