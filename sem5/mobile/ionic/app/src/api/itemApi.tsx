import axios from 'axios';
import { getLogger, axiosInstance, authConfig } from '../core';
import { Item } from '../model/Item';
import { Filter } from '../features/ItemProvider';

const log = getLogger('itemApi');

const baseUrl = 'localhost:3000';
const itemUrl = `http://${baseUrl}/books`;

interface ResponseProps<T> {
  data: T;
}

function withLogs<T>(promise: Promise<ResponseProps<T>>, fnName: string): Promise<T> {
  // log(`${fnName} - started`);
  return promise
    .then(res => {
      // log(`${fnName} - succeeded`);
      return Promise.resolve(res.data);
    })
    .catch(err => {
      // log(`${fnName} - failed`);
      return Promise.reject(err);
    });
}

export const getItems: (filter: Filter, token: string) => Promise<Item[]> = (filter, token) => {
  const params = new URLSearchParams();
  if (filter.read != undefined && filter.read != null) params.append("read", filter.read.toString());
  if (filter.title != undefined && filter.title != null) params.append("title", filter.title);
  if (filter.page != undefined && filter.page != null) params.append("page", filter.page.toString());
  return withLogs(axios.get(itemUrl, { ...authConfig(token), params }), 'getItems');
}


export const getItem: (id: string, token: string) => Promise<Item> = (id, token) => {
  return withLogs(axios.get(`${itemUrl}/${id}`, { ...authConfig(token) }), 'getItems');
}


export const createItem: (item: Item, token: string) => Promise<Item[]> = (item, token) => {
  return withLogs(axios.post(itemUrl, item, { ...authConfig(token) }), 'createItem');
}

export const updateItem: (item: Item, token: string) => Promise<Item[]> = (item, token) => {
  return withLogs(axios.put(`${itemUrl}/${item._id}`, item, { ...authConfig(token) }), 'updateItem');
}

interface MessageData {
  event: string;
  payload: {
    item: Item;
  };
}

export const newWebSocket = (token: string, onMessage: (data: MessageData) => void) => {
  const ws = new WebSocket(`ws://${baseUrl}`)
  ws.onopen = () => {
    log("Connecting to WS server...");
    ws.send(JSON.stringify({ type: 'authorization', payload: { token } }));
    log("Connected to WS server");
  };
  ws.onclose = () => {
    log('web socket onclose');
  };
  ws.onerror = error => {
    log('web socket onerror', error);
  };
  ws.onmessage = messageEvent => {
    log('web socket onmessage');
    onMessage(JSON.parse(messageEvent.data));
  };
  return () => {
    ws.close();
  }
}
