import axios from "axios";

export interface Item {
  code: number;
  name: string;
}

export const getItems = async () => {
  const response = await axios.get("http://localhost:3000/Items");
  return response.data;
};
export const postItem = async (item: Item) => {
  const response = await axios.post("http://localhost:3000/Items", item);
  return response.data;
};

//pt cache
export const cacheItems = async (item: Item[]) => {
  localStorage.setItem("items", JSON.stringify(item));
};
export const addToCachedItems = async (item: Item) => {
  const items = getCachedItems();
  items.push(item);
  localStorage.setItem("items", JSON.stringify(items));
};
export const getCachedItems = (): Item[] => {
  const items = localStorage.getItem("items");
  if (items === null) {
    return [];
  }
  return JSON.parse(items);
};

export interface Note {
  id: number;
  text: string;
  date: string;
}

export interface NoteResponse {
  total: number;
  page: number;
  notes: Note[];
}

let lastModified: string | null = null;

export const getNotes = async (page: number): Promise<NoteResponse> => {
  const headers = lastModified ? { 'If-Modified-Since': lastModified } : {};
  const response = await axios.get(`http://localhost:3000/note?page=${page}`, { headers });
  if (response.status === 304) {
    return getCachedNotesByPage(page);
  }
  const lastModifiedHeader = response.headers['last-modified'];
  if (lastModifiedHeader && !response.data.more) {
    alert('No more notes available');
    lastModified = lastModifiedHeader;
  }
  cacheNotesByPage(page, response.data);
  return response.data;
};

export const getLastModified = (): string | null => {
  return lastModified;
};

export const cacheNotes = async (notes: Note[]) => {
  localStorage.setItem("notes", JSON.stringify(notes));
};

export const getCachedNotes = (): Note[] => {
  const notes = localStorage.getItem("notes");
  if (notes === null) {
    return [];
  }
  return JSON.parse(notes);
};

export const cacheNotesByPage = async (page: number, data: NoteResponse) => {
  localStorage.setItem(`notes-page-${page}`, JSON.stringify(data));
};

export const getCachedNotesByPage = (page: number): NoteResponse => {
  const notes = localStorage.getItem(`notes-page-${page}`);
  if (notes === null) {
    return { total: 0, page, notes: [] };
  }
  return JSON.parse(notes);
};

export const deleteNote = async (id: number): Promise<void> => {
  const response = await axios.delete(`http://localhost:3000/note/${id}`);
  return response.data;
};

export const cacheDeletedNotes = async (notes: Note[]) => {
  localStorage.setItem("deleted-notes", JSON.stringify(notes));
};

export const getCachedDeletedNotes = (): Note[] => {
  const notes = localStorage.getItem("deleted-notes");
  if (notes === null) {
    return [];
  }
  return JSON.parse(notes);
};