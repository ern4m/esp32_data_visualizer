const express = require('express');
const app = express();
const http = require('http');
const { userInfo } = require('os');
const server = http.createServer(app);

const { Server } = require("socket.io");
const io = new Server(server);

app.get('/', (req, res) => {
  res.sendFile(__dirname + '/index.html');
});


const random = (min, max) => Math.floor(Math.random() * (max - min)) + min;

io.on('connection', (socket) => {
  console.log('a user connected');
  

  

  socket.on('chat message', (msg) => {
    let { user, text } = msg;
    console.log(JSON.parse(msg));
    io.emit('chat message', msg)
  });
});

setInterval(() => {
  let arr = new Array(16).fill(null).map(() => (random(200,300)))
  io.emit("chart_data", arr)
  console.log(arr)
}, 100);

server.listen(3000, () => {
  console.log('listening on *:3000');
});