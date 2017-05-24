const router = require('koa-router')();
const server = require('../server');
const waitEvents = require('wait-events');

router.prefix('/detail');

router.get('/movieinfo/:id', async (ctx, next) => {
    console.log('post /detail/movieinfo');
    var m_id = ctx.params.id;
    //var m_keyword = ctx.request.body.keyword;
    if (server.cpp_socket) {
        console.log('cpp_socket exist');
        server.cpp_socket.emit('server_get_movieinfo', {
            movie : m_id
        });
        let ret = await waitEvents(server.cpp_socket, ['cpp_send_movieinfo'], ['err']);
        console.log('Recv cpp_send_movieinfo');
        ctx.response.body = ret;
    }
});

router.get('/actorinfo/:id', async (ctx, next) => {
    console.log('post /detail/actorinfo');
    var m_id = ctx.params.id;
    //var m_keyword = ctx.request.body.keyword;
    if (server.cpp_socket) {
        console.log('cpp_socket exist');
        server.cpp_socket.emit('server_get_actorinfo', {
            movie : m_id
        });
        let ret = await waitEvents(server.cpp_socket, ['cpp_send_actorinfo'], ['err']);
        console.log('Recv cpp_send_actorinfo');
        ctx.response.body = ret;
    }
});

router.get('/relateinfo/:id', async (ctx, next) => {
    console.log('post /detail/relateinfo');
    var m_id = ctx.params.id;
    //var m_keyword = ctx.request.body.keyword;
    if (server.cpp_socket) {
        console.log('cpp_socket exist');
        server.cpp_socket.emit('server_get_relateinfo', {
            movie : m_id
        });
        let ret = await waitEvents(server.cpp_socket, ['cpp_send_relateinfo'], ['err']);
        console.log('Recv cpp_send_relateinfo');
        ctx.response.body = ret;
    }
});

module.exports = router
