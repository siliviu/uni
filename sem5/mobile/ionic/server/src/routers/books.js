import Router from 'koa-router'
import { broadcast } from '../ws.js';
import { Service } from '../service.js'
import { Book } from '../book.js'
const router = new Router();

const service = new Service("./db/books.json", true);


router.get('/books', async ctx => {
    const userId = ctx.state.user._id;
    const read = ctx.request.query.read;
    const title = ctx.request.query.title;
    const page = ctx.request.query.page;
    if (!userId) {
        ctx.response.body = "No userId";
        ctx.response.status = 400; //  BAD REQUEST
    }
    const parameters = { userId: userId };
    if (read)
        parameters.read = read == "true";
    if (title)
        parameters.title = title;
    if (!page)
        ctx.response.body = await service.get(parameters);
    else {
        console.log(parameters);
        ctx.response.body = await service.getPaginated(parameters, page);
    }
    ctx.response.status = 200;
});

router.get('/books/:id', async (ctx) => {
    const userId = ctx.state.user._id;
    if (!userId) {
        ctx.response.body = "No userId";
        ctx.response.status = 400; //  BAD REQUEST
    }
    const itemId = ctx.params.id;
    const item = await service.getOne({ userId: userId, _id: itemId });
    if (item) {
        ctx.response.body = item;
        ctx.response.status = 200; // ok
    } else {
        ctx.response.body = { message: `book with id ${itemId} not found` };
        ctx.response.status = 404; // NOT FOUND (if you know the resource was deleted, then return 410 GONE)
    }
});

router.post('/books', async (ctx) => {
    const userId = ctx.state.user._id;
    if (!userId) {
        ctx.response.body = "No userId";
        ctx.response.status = 400; //  BAD REQUEST
    }
    const item = ctx.request.body;
    if (!item.title | !item.author | !item.price) { // validation
        ctx.response.body = { message: 'Book value is bad' };
        ctx.response.status = 400; //  BAD REQUEST
        return;
    }
    if (!item.read)
        item.read = false;
    item.userId = userId;
    item.version = 1;
    ctx.response.body = await service.save(item);
    ctx.response.status = 201; // CREATED
    broadcast(userId, { event: 'created', payload: { item } });
});

router.put('/books/:id', async (ctx) => {
    const userId = ctx.state.user._id;
    if (!userId) {
        ctx.response.body = "No userId";
        ctx.response.status = 400; //  BAD REQUEST
    }
    const id = ctx.params.id;
    const item = ctx.request.body;
    let storedItem = await service.getOne({ _id: id });
    if (!storedItem) {
        ctx.response.body = { issue: [{ error: `item with id ${id} not found` }] };
        ctx.response.status = 400;
        return;
    }
    // update item
    if (!item.title | !item.author | !item.price) {
        ctx.response.body = { issue: e.errors };
        ctx.response.status = 400;
        return;
    }
    item.userId = userId;
    await service.update(id, item);
    ctx.response.body = item;
    ctx.response.status = 200;
    broadcast(userId, { event: 'updated', payload: { item } });
});

router.del('/books/:id', async ctx => {
    const userId = ctx.state.user._id;
    if (!userId) {
        ctx.response.body = "No userId";
        ctx.response.status = 400; //  BAD REQUEST
    }
    const id = ctx.params.id;
    try { await service.remove(id); }
    catch (e) {
        ctx.response.body = { message: 'Book value is bad' };
        ctx.response.status = 400;
        return;
    }
    ctx.response.status = 204;
});


// setInterval(async () => {
//     let lastId = Math.floor(Math.random() * 100);
//     let item = new Book({ id: lastId, title: `book ${lastId}`, author: `author ${lastId}`, launched: new Date(Date.now()), price: 2 * lastId, read: lastId % 2 == 0, version: 1 });
//     item = await service.save(item);
//     console.log(`New book: ${item.title}`);
//     console.log(item);
//     broadcast({ event: 'created', payload: { item } });
// }, 5000);


export { router };