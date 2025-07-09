import React, { useCallback, useContext, useEffect, useReducer } from 'react';
import PropTypes from 'prop-types';
import { getLogger } from '../core';
import { Item } from '../model/Item';
import { createItem, getItems, newWebSocket, updateItem } from '../api/itemApi';
import { useNetworkStatus } from './NetworkStatus';
import { filter } from 'ionicons/icons';
import { AuthContext } from './AuthProvider';
import { addBookToStorage, getBooksFromStorage, updateBookInStorage } from '../storage/books';

const log = getLogger('ItemProvider');

type SaveItemFn = (item: Item) => Promise<any>;

export interface Filter {
  title?: string,
  read?: boolean,
  page?: number
}

export interface ItemsState {
  items?: Item[],
  fetching: boolean,
  fetchingError?: Error | null,
  saving: boolean,
  savingError?: Error | null,
  filter: Filter,
  refresh: number,
  saveItem?: SaveItemFn,
}

interface ActionProps {
  type: string,
  payload?: any,
}

const initialState: ItemsState = {
  fetching: false,
  saving: false,
  filter: { page: 1 },
  refresh: 1
};

const NEXT_PAGE = 'ADD_PAGE';
const ADD_PAGE = 'NEXT_PAGE';
const FILTER_TITLE = 'FILTER_TITLE';
const FILTER_READ = 'FILTER_READ';
const FETCH_ITEMS_STARTED = 'FETCH_ITEMS_STARTED';
const FETCH_ITEMS_SUCCEEDED = 'FETCH_ITEMS_SUCCEEDED';
const FETCH_ITEMS_FAILED = 'FETCH_ITEMS_FAILED';
const SAVE_ITEM_STARTED = 'SAVE_ITEM_STARTED';
const SAVE_ITEM_SUCCEEDED = 'SAVE_ITEM_SUCCEEDED';
const SAVE_ITEM_FAILED = 'SAVE_ITEM_FAILED';

const reducer: (state: ItemsState, action: ActionProps) => ItemsState =
  (state, { type, payload }) => {
    switch (type) {
      case ADD_PAGE:
        return { ...state, items: state.items!.concat(payload.items) }
      case NEXT_PAGE:
        return { ...state, filter: { ...state.filter, page: state.filter.page! + 1 } }
      case FILTER_TITLE:
        return { ...state, filter: { ...state.filter, page: 1, title: payload.title } };
      case FILTER_READ:
        return { ...state, filter: { ...state.filter, page: 1, read: payload.read } };
      case FETCH_ITEMS_STARTED:
        return { ...state, fetching: true, fetchingError: null };
      case FETCH_ITEMS_SUCCEEDED:
        return { ...state, items: payload.items, fetching: false };
      case FETCH_ITEMS_FAILED:
        return { ...state, fetchingError: payload.error, fetching: false };
      case SAVE_ITEM_STARTED:
        return { ...state, savingError: null, saving: true };
      case SAVE_ITEM_SUCCEEDED:
        const items = [...(state.items || [])];
        const item = payload.item;
        if (item._id) {
          const index = items.findIndex(it => it._id == item._id);
          if (index === -1) {
            items.splice(-1, 0, item);
          } else {
            items[index] = item;
          }
        }
        return { ...state, items, saving: false };
      case SAVE_ITEM_FAILED:
        return { ...state, savingError: payload.error, saving: false };
      default:
        return state;
    }
  };

export const ItemContext = React.createContext<any>(initialState);

interface ItemProviderProps {
  children: PropTypes.ReactNodeLike,
}

export const ItemProvider: React.FC<ItemProviderProps> = ({ children }) => {

  const { token } = useContext(AuthContext);
  const [state, dispatch] = useReducer(reducer, initialState);
  const { items, fetching, fetchingError, saving, savingError, filter } = state;
  useEffect(getItemsEffect, [token, state.filter.read, state.filter.title]);
  useEffect(wsEffect, [token]);
  const value = { items, fetching, fetchingError, saving, savingError, saveItem, setTitle, setRead, clearFilter, nextPage };
  return (
    <ItemContext.Provider value={value}>
      {children}
    </ItemContext.Provider>
  );

  function getItemsEffect() {
    let canceled = false;
    fetchItems();
    return () => {
      canceled = true;
    }

    async function fetchItems() {
      try {
        log('fetchItems started');
        dispatch({ type: FETCH_ITEMS_STARTED });
        const items = await getItems(filter, token);
        if (state.filter.page == 1)
          dispatch({ type: NEXT_PAGE });
        log('fetchItems succeeded');
        if (!canceled) {
          dispatch({ type: FETCH_ITEMS_SUCCEEDED, payload: { items } });
        }
      } catch (error) {
        log('fetchItems failed');
        if (!canceled)
          dispatch({ type: FETCH_ITEMS_FAILED, payload: { error } });
        const items = await getBooksFromStorage();
        dispatch({ type: FETCH_ITEMS_SUCCEEDED, payload: { items } });
      }
    }
  }

  async function nextPage() {
    let newItems: Item[] | undefined = await getItems(filter, token);
    dispatch({ type: NEXT_PAGE });
    if (newItems instanceof Array) {
      dispatch({ type: ADD_PAGE, payload: { items: newItems } });
    }
  }

  function clearFilter() {
    try {
      log('cleared filter');
      dispatch({ type: FILTER_TITLE, payload: { title: null } });
      dispatch({ type: FILTER_READ, payload: { read: null } });
    } catch (error) {
      log('clear failed');
    }
  }

  function setTitle(title: string) {
    try {
      log('title set');
      dispatch({ type: FILTER_TITLE, payload: { title: title } });
    } catch (error) {
      log('title failed');
    }
  }

  function setRead(read: boolean) {
    try {
      log('read set');
      dispatch({ type: FILTER_READ, payload: { read: read } });
    } catch (error) {
      log('read failed');
    }
  }

  async function saveItem(item: Item) {
    try {
      log('saveItem started');
      dispatch({ type: SAVE_ITEM_STARTED });
      const savedItem = await (item._id ? updateItem(item, token) : createItem(item, token));
      log('saveItem succeeded');
      dispatch({ type: SAVE_ITEM_SUCCEEDED, payload: { item: savedItem } });
    } catch (error) {
      log('saveItem failed');
      dispatch({ type: SAVE_ITEM_FAILED, payload: { error } });
      await (item._id ? updateBookInStorage(item._id, item) : addBookToStorage(item));
    }
  }

  function wsEffect() {
    let canceled = false;
    log('wsEffect - connecting');
    const closeWebSocket = newWebSocket(token, message => {
      if (canceled) {
        return;
      }
      const { event, payload: { item } } = message;
      log(`ws message, new item ${event}`);
      log(item);
      // if (event === 'created' || event === 'updated') {
      //   dispatch({ type: SAVE_ITEM_SUCCEEDED, payload: { item } });
      // }
    });
    return () => {
      log('wsEffect - disconnecting');
      canceled = true;
      closeWebSocket();
    }
  }
};
