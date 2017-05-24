const router = require('koa-router')();
const server = require('../server');
const waitEvents = require('wait-events');

router.prefix('/index');

router.get('/', async (ctx, next) => {
    console.log("get /");
    if (server.cpp_socket) {
        console.log("cpp_socket exist");
        server.cpp_socket.emit("server_get_index", {
            region : 'china'
        });
        let ret = await waitEvents(server.cpp_socket, ['cpp_send_index'], ['err']);
        console.log("Recv cpp_send_index china");
        ctx.response.body = ret;
    }
});

router.get('/china', async (ctx, next) => {
    console.log("get /");
    if (server.cpp_socket) {
        console.log("cpp_socket exist");
        server.cpp_socket.emit("server_get_index", {
            region : 'china'
        });
        let ret = await waitEvents(server.cpp_socket, ['cpp_send_index'], ['err']);
        console.log("Recv cpp_send_index china");
        ctx.response.body = ret;
    }
});

router.get('/us', async (ctx, next) => {
    console.log("get /");
    if (server.cpp_socket) {
        console.log("cpp_socket exist");
        server.cpp_socket.emit("server_get_index", {
            region : 'us'
        });
        let ret = await waitEvents(server.cpp_socket, ['cpp_send_index'], ['err']);
        console.log("Recv cpp_send_index us");
        ctx.response.body = ret;
    }
});

router.get('/japan', async (ctx, next) => {
    console.log("get /");
    if (server.cpp_socket) {
        console.log("cpp_socket exist");
        server.cpp_socket.emit("server_get_index", {
            region : 'japan'
        });
        let ret = await waitEvents(server.cpp_socket, ['cpp_send_index'], ['err']);
        console.log("Recv cpp_send_index japan");
        ctx.response.body = ret;
    }
});

module.exports = router
