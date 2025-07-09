class Book {
    constructor({ userId, title, author, launched, price, read, version, image }) {
        this.userId = userId;
        this.title = title;
        this.author = author;
        this.launched = launched;
        this.price = price;
        this.read = read;
        this.version = version;
        this.image = image;
    }
}


export { Book };