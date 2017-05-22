const server = require('http').createServer();
const Koa = require('koa');
const io = require('socket.io')();
const waitEvents = require('wait-events');
const app = new Koa();
const views = require('koa-views');
const json = require('koa-json');
const onerror = require('koa-onerror');
const bodyparser = require('koa-bodyparser')();
const logger = require('koa-logger');

const index = require('./routes/index');
const users = require('./routes/users');

server.on('request', app.callback());
io.listen(server);
var port = process.env.PORT || 8088;
server.listen(port);

// error handler
onerror(app);

// middlewares
app.use(bodyparser);
app.use(json());
app.use(logger());
app.use(require('koa-static')(__dirname + '/public'));

app.use(views(__dirname + '/views', {
  extension: 'pug'
}));

// logger
app.use(async (ctx, next) => {
  const start = new Date();
  await next();
  const ms = new Date() - start;
  console.log(`${ctx.method} ${ctx.url} - ${ms}ms`);
});

// routes
app.use(index.routes(), index.allowedMethods());
app.use(users.routes(), users.allowedMethods());


var web_socket = null, cpp_socket = null;

// socket.io
io.on('connection', (socket) => {
    socket.emit('greetings', 'hello');
    console.log("a user connection");

    socket.on('disconnect', function(msg){
        console.log('user disconnected');
    });
    
    socket.on('web_client', function(msg){
        console.log("this is a web client");
        web_socket = socket;
    });

    socket.on('cpp_client', function(msg){
        console.log("this is a cpp client");
        cpp_socket = socket;
    });

    //socket.on('web_get_page', function(msg){
    //    console.log('web_get_page');
    //    if (!cpp_socket) {
    //        console.log("No cpp client is available");
    //    } else {
    //        cpp_socket.emit('server_get_page', msg);
    //        console.log("server_get_page is emited");
    //    }
    //});

    //socket.on('cpp_push_page', function(msg){
    //    console.log('cpp_push_page');
    //    if (!web_socket) {
    //        console.log("No web client is available");
    //    } else {
    //        // push rendered pages
    //        console.log("send sth to web_client " + msg);
    //    }
    //});
});

index.post('/string', async (ctx, next) => {
    var data = ctx.request.body.m || '';
    console.log("Recv from post to /string " +  data);
    cpp_socket.emit("server_get_page", data);
    if (cpp_socket) {
        console.log("wait event");
        var ret = await waitEvents(cpp_socket, ['cpp_push_page'], ["err"]);
        console.log('Recv!!: ' + ret);
        ctx.response.body = ret;
    }
});


module.exports = app;
