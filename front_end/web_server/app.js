const Koa = require('koa');
const app = new Koa();
const server = require('./server');
const views = require('koa-views');
const json = require('koa-json');
const onerror = require('koa-onerror');
const bodyparser = require('koa-bodyparser')();
const logger = require('koa-logger');

const index = require('./routes/index');
const search = require('./routes/search');
const detail = require('./routes/detail');

// server
server.start(3000, app);
server.register_callbacks();

// error handler
onerror(app);
// middlewares
app.use(bodyparser);
app.use(json());
app.use(logger());
app.use(require('koa-static')(__dirname + '/public'));

//app.use(views(__dirname + '/views', {
//  extension: 'pug'
//}));

// logger
app.use(async (ctx, next) => {
  const start = new Date();
  await next();
  const ms = new Date() - start;
  console.log(`${ctx.method} ${ctx.url} - ${ms}ms`);
});

// routes
app.use(index.routes(), index.allowedMethods());
app.use(search.routes(), search.allowedMethods());
app.use(detail.routes(), detail.allowedMethods());


module.exports = app;
