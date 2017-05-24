const router = require('koa-router')();
const server = require('../server');
const waitEvents = require('wait-events');

router.prefix('/search');

router.post('/:keyword', async (ctx, next) => {
    console.log('post /search/');
    var m_keyword = ctx.params.keyword;
    //var m_keyword = ctx.request.body.keyword;
    if (server.cpp_socket) {
        console.log('cpp_socket exist');
        server.cpp_socket.emit('server_get_search', {
            keyword : m_keyword
        });
        let ret = await waitEvents(server.cpp_socket, ['cpp_send_search'], ['err']);
        console.log('Recv cpp_send_search');
        ctx.response.body = ret;
    }
});

module.exports = router
