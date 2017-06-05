const router = require('koa-router')();
const server = require('../server');
const waitEvents = require('wait-events');
const fuzz = require('fuzzball');
var fs = require('fs');
var dict = JSON.parse(fs.readFileSync('json', 'utf8'));
var choices = dict['movie'];
const sim_limit = 40;
const size_limit = 20;
var options = {scorer: fuzz.partial_ratio};

//router.prefix('/search');

router.post('/search', async (ctx, next) => {
    console.log('post /search');
    var m_keyword = ctx.request.body.keyword;
    console.log(m_keyword);
    var results = fuzz.extract(m_keyword, choices, options);
    
    // limit
    var movies = [];
    for (var i = 0; i < size_limit; ++i) {
        if (results[i][1] > sim_limit) {
            movies.push(results[i][0]);
        } else {
            break;
        }
    }
    console.log("sim search:");
    console.log(movies);

    //var m_keyword = ctx.request.body.keyword;
    if (server.get_cpp_socket()) {
        console.log('cpp_socket exist');
        server.get_cpp_socket().emit('server_get_search', {
            keyword : movies
        });
        let ret = await waitEvents(server.get_cpp_socket(), ['cpp_send_search'], ['err']);
        console.log('Recv cpp_send_search');
        ctx.response.body = String(ret);
    }
});

module.exports = router
