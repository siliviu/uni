export interface Item {
  _id?: string;
  title: string;
  author: string;
  launched: Date;
  price: number;
  read: boolean;
  lat: number;
  lng: number;
  image?: string;
}

export class ItemOffline {
  item: Item;
  state: "read" | "created" | "updated";

  constructor(item: Item, state: "read" | "created" | "updated" = "read") {
      this.item = item;
      this.state = state;
  }
}