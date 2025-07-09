import { Storage } from "@ionic/storage";
import { Item, ItemOffline } from "../model/Item";
import { createItem, getItems, updateItem } from "../api/itemApi";

const booksStorage = new Storage({
    name: 'books',
})

booksStorage.create();

export const backOnline = async (token: string, data: Item[], refresh: any) => {
    console.log('back');
    const books: Item[] = []
    const booksAdded: Item[] = []
    const booksUpdated: Item[] = []
    await booksStorage.forEach((value: ItemOffline) => {
        if (value.state === "created") {
            booksAdded.push(value.item)
        } else if (value.state === "updated") {
            booksUpdated.push(value.item)
        }
        books.push(value.item)
    })
    for (const magazin of booksAdded)
        await createItem(magazin, token);
    for (const magazin of booksUpdated)
        await updateItem(magazin, token);

    console.log("[BACK ONLINE] books added: ", booksAdded)
    console.log("[BACK ONLINE] books updated: ", booksUpdated)
    console.log("[BACK ONLINE] books: ", books)
    refresh();
    await booksStorage.clear()
    if (data)
        data.forEach(async (item: Item) => await booksStorage.set(item._id!, new ItemOffline(item)));
    else {
        data = await getItems({}, token);
        data.forEach(async (item: Item) => await booksStorage.set(item._id!, new ItemOffline(item)));
    }
}

export const getBooksFromStorage = async () => {
    const books: Array<Item> = []
    await booksStorage.forEach((value: ItemOffline) => {
        books.push(value.item!)
    })
    return books;
}

export const getBookFromStorage = async (id: string) => {
    const res = await booksStorage.get(id);
    return res.item;
}

export const addBookToStorage = async (book: Item) => {
    let randomId = Math.floor(Math.random() * 1000000000000000000).toString();
    while (await booksStorage.get(randomId)) {
        randomId = Math.floor(Math.random() * 1000000000000000000).toString();
    }
    book._id = randomId;
    await booksStorage.set(randomId, new ItemOffline(book, "created"));
    console.log(booksStorage);
}

export const updateBookInStorage = async (id: string, book: Item) => {
    await booksStorage.set(id, new ItemOffline(book, "updated"));
}

export { booksStorage }