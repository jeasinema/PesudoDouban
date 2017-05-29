const router = require('koa-router')();
const server = require('../server');
const waitEvents = require('wait-events');

router.prefix('/index');

router.get('/', async (ctx, next) => {
    console.log("get /");
    if (server.get_cpp_socket()) {
        console.log("cpp_socket exist");
        server.get_cpp_socket().emit("server_get_index", {
            region : 'china'
        });
        let ret = await waitEvents(server.get_cpp_socket(), ['cpp_send_index'], ['err']);
        console.log("Recv cpp_send_index china");
        ctx.response.body = String(ret);
    }
});

router.get('/china', async (ctx, next) => {
    console.log("get /index/china");
    if (server.get_cpp_socket()) {
        console.log("cpp_socket exist");
        server.get_cpp_socket().emit("server_get_index", {
            region : 'china'
        });
        let ret = await waitEvents(server.get_cpp_socket(), ['cpp_send_index'], ['err']);
        console.log("Recv cpp_send_index china");
        ctx.response.body = String(ret);
    }
});

router.get('/us', async (ctx, next) => {
    console.log("get /index/us");
    if (server.get_cpp_socket()) {
        console.log("cpp_socket exist");
        server.get_cpp_socket().emit("server_get_index", {
            region : 'us'
        });
        let ret = await waitEvents(server.get_cpp_socket(), ['cpp_send_index'], ['err']);
        console.log("Recv cpp_send_index us");
        ctx.response.body = String(ret);
    }
});

router.get('/japan', async (ctx, next) => {
    console.log("get /index/japan");
    if (server.get_cpp_socket()) {
        console.log("cpp_socket exist");
        server.get_cpp_socket().emit("server_get_index", {
            region : 'japan'
        });
        let ret = await waitEvents(server.get_cpp_socket(), ['cpp_send_index'], ['err']);
        console.log("Recv cpp_send_index japan");
        ctx.response.body = String(ret);
    }
});

module.exports = router
