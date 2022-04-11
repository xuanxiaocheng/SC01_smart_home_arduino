const path = require('path')
const aedes = require('aedes')()
const httpServer = require('http').createServer()
const ws = require('websocket-stream')
const wsPort = 7000
const port = 1883
const broker = require('net').createServer(aedes.handle);
const express = require('express')
var http = require('http');
var app = express()

broker.listen(port, function() {
    console.log('broker listening on port', port)
});

ws.createServer({ server: httpServer }, aedes.handle)

httpServer.listen(wsPort, function() {
    console.log('server started and listening on port ', wsPort)
});

// 身份验证
aedes.authenticate = function(client, username, password, callback) {
    callback(null, (username === 'user' && password.toString() === '123456'));
}

// 客户端连接
aedes.on('client', function(client) {
    console.log('Client Connected: \x1b[33m' + (client ? client.id : client) + '\x1b[0m', 'to broker', aedes.id);
});

// 客户端断开
aedes.on('clientDisconnect', function(client) {
    console.log('Client Disconnected: \x1b[31m' + (client ? client.id : client) + '\x1b[0m', 'to broker', aedes.id);
});

app.use(express.static(path.join(__dirname, 'public')));
var server = http.createServer(app);
server.listen(5000);