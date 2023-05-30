import express from "express";
import http from "http";
import { Server } from "socket.io";
import { client, insertData } from "./db/db.js";

const app = express();
const server = http.createServer(app);
const io = new Server(server);

app.get("/", (req, res) => {
  res.sendFile(__dirname + "/index.html");
});

// endpoint que vai receber os dados da esp
// é pra acontecer aqui o que está acontecendo no setInterval
app.post("data", (req, res) => {
  let data = req.body;
  // fazer a emissao pelo IO e inserir no banco
});

const random = (min, max) => Math.floor(Math.random() * (max - min)) + min;

io.on("connection", (socket) => {
  console.log("a user connected");
});

// testando emissao pelo socket e inserção no banco
setInterval(async () => {
  let arr = new Array(16).fill(null).map(() => random(200, 300));
  const collection = client.db().collection("data");
  try {
    const res = await insertData(collection, arr);
    io.emit("chart_data", arr);
    console.log(res);
  } catch (error) {
    console.error(error);
  }
}, 300022);

server.listen(3000, () => {
  console.log("listening on *:3000");
});
