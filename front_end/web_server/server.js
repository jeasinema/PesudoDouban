const io = require('socket.io')();
const server = require('http').createServer();

// server relate
function start(_port, app) {
    server.on('request', app.callback());
    io.listen(server);
    let port = _port || process.env.PORT || 8088;
    server.listen(port);
}
var web_socket = null, cpp_socket = null;

function get_cpp_socket() {
    return cpp_socket;
}

function get_web_socket() {
    return cpp_socket;
}

// socket.io
function register_callbacks() {
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
    });
}


module.exports =  {
    start : start,
    server : server,
    web_socket : web_socket,
    cpp_socket : cpp_socket,
    start : start,
    register_callbacks : register_callbacks,
    get_cpp_socket : get_cpp_socket,
    get_web_socket : get_web_socket
};
