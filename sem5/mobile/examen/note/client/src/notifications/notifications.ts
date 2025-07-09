import { Note } from "../data/item";

export const connect = (callback: (event: string, note: Note) => void) => {
  const ws = new WebSocket("ws://localhost:3000");
  ws.onopen = () => {
    console.log("connected");
  };
  ws.onmessage = (message) => {
    const msg = JSON.parse(message.data);
    callback(msg.event, msg.note);
  };
  ws.onclose = () => {
    console.log("disconnected");
  };
  ws.onerror = () => {
    console.log("error");
  };
  return ws;
};
