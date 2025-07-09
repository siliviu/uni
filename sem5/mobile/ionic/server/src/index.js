import Koa from 'koa'
import { createServer } from 'http';
import { jwtConfig, timingLogger, exceptionHandler } from './utils.js';
import jwt from 'koa-jwt';
import WebSocket from 'ws';
import cors from 'koa-cors';
import bodyparser from 'koa-bodyparser';
import { initWs } from './ws.js';


import { router } from './routers/books.js'
import { authRouter } from './routers/users.js'
export const app = new Koa();

app
  .use(bodyparser())
  .use(cors());

app
  .use(async (ctx, next) => {
    await new Promise(resolve => setTimeout(resolve, 300));
    await next();
  })
  .use(timingLogger)
  .use(exceptionHandler);

const server = createServer(app.callback());
const wss = new WebSocket.Server({ server });
initWs(wss);

app
  .use(authRouter.routes())
  .use(authRouter.allowedMethods());

app.use(jwt(jwtConfig))
  .use(router.routes())
  .use(router.allowedMethods());

server.listen(3000);
