const path = require('path')
const express = require('express')
var http = require('http');
var app = express()

app.use(express.static(path.join(__dirname, 'public')));
var server = http.createServer(app);
server.listen(5000);