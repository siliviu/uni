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
  if (item[0])
    localStorage.setItem("items", JSON.stringify(item));
};

export const getCachedItems = (): Item[] => {
  const items = localStorage.getItem("items");
  if (items === null) {
    return [];
  }

  return items[0] ? JSON.parse(items) : (items ? [items] : []);
};
