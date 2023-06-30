import { MongoClient } from "mongodb";
import { config } from "dotenv";

// configura o .env
await config()
// console.log(process.env)
const uri = process.env.DB_URI || "";
console.log(uri)

export const client = new MongoClient("mongodb://0.0.0.0:27017");

export const insertData = async (collection, data) => {
  // no momento o doc só ta aceitando um array de data
  // o ideal vai ser receber 2 arrays do esp e armazenar aqui
  const doc = {
    timestamp: new Date(),
    data: data,
  };
  const result = await collection.insertOne(doc);
  return result;
};

export const deleteAll = async (collection) => {
  const result = await collection.deleteMany();
  return result;
}


// Clear db
// const collection = client.db("esp").collection("data");
// deleteAll(collection)