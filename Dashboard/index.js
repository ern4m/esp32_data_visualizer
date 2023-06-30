import express from "express";
import http from "http";
// import bodyParser from "bod"
import { Server } from "socket.io";
import { client, insertData } from "./db/db.js";
import { fileURLToPath } from 'url';
import { dirname, join } from 'path';


const app = express();
app.use(express.json());

const server = http.createServer(app);
const io = new Server(server);

const __filename = fileURLToPath(import.meta.url);
const __dirname = dirname(__filename);


const sampleRate = 44100;

// Freq and Mag function:
const frequencyAndMagnitude = (fftOutput, sampleRate) => {
  var maxMagnitude = 0;
  var fundamentalFreq = 0;

  for (var k = 1; k < fftOutput.size / 2; k++) {
    /*A parte real de uma magnitude em uma frequência é seguida pela parte imaginária correspondente na saída*/
    var mag = Math.sqrt(Math.pow(fftOutput[2 * k], 2) + Math.pow(fftOutput[2 * k + 1], 2)) / 1;
    var freq = k * 1.0 / 0.0001;

    // Verificar se a magnitude atual é maior do que a maior magnitude registrada
    if (mag > maxMagnitude) {
      maxMagnitude = mag;
      fundamentalFreq = freq;
    }
  }
  return maxMagnitude;
}


const collection = client.db("esp").collection("data");

app.get("/", (req, res) => {
  const filePath = join(__dirname, 'index.html');
  res.sendFile(filePath);
});

// endpoint que vai receber os dados da esp
// é pra acontecer aqui o que está acontecendo no setInterval
app.post('/data', async (req, res) => {
  try {
    let data = req.body;
    var db = 20 * Math.log10(data["maxMag"]);
    data["maxDb"] = db;
    console.log(data)
    io.emit("chart_data", data);
    const resDb = await insertData(collection, data);
    res.status(200).send('Received');
  } catch (error) {
    console.error('Error:', error);
    res.status(500).send('Internal Server Error');
  }
});
const random = (min, max) => Math.floor(Math.random() * (max - min)) + min;

io.on("connection", (socket) => {
  console.log("a user connected");
});

server.listen(3000, '0.0.0.0', () => {
  console.log("listening on *:3000");
});
