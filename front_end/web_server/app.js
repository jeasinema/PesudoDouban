const Koa = require('koa');
const app = new Koa();
const server = require('./server');
const views = require('koa-views');
const json = require('koa-json');
const onerror = require('koa-onerror');
const bodyparser = require('koa-bodyparser')();
const logger = require('koa-logger');
const serve = require('koa-static');
const mount = require('koa-mount');
const path = require('path');

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
// static resources
app.use(mount('/js', serve(path.join(__dirname, 'views', 'static', 'js'))));
app.use(mount('/css', serve(path.join(__dirname, 'views', 'static', 'css'))));
app.use(mount('/img', serve(path.join(__dirname, 'views', 'static', 'img'))));
app.use(mount('/index/js', serve(path.join(__dirname, 'views', 'static', 'js'))));
app.use(mount('/index/css', serve(path.join(__dirname, 'views', 'static', 'css'))));
app.use(mount('/index/img', serve(path.join(__dirname, 'views', 'static', 'img'))));
app.use(mount('/detail/js', serve(path.join(__dirname, 'views', 'static', 'js'))));
app.use(mount('/detail/css', serve(path.join(__dirname, 'views', 'static', 'css'))));
app.use(mount('/detail/img', serve(path.join(__dirname, 'views', 'static', 'img'))));
app.use(mount('/search/js', serve(path.join(__dirname, 'views', 'static', 'js'))));
app.use(mount('/search/css', serve(path.join(__dirname, 'views', 'static', 'css'))));
app.use(mount('/search/img', serve(path.join(__dirname, 'views', 'static', 'img'))));

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

console.log("use all routes!");

module.exports = app;
