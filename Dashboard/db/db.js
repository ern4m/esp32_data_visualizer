import { MongoClient } from "mongodb";
import { config } from "dotenv";

const uri =
  config({ path: "Dashboard/.env" }).parsed.DB_URI + "/esp_data" || "";

export const client = new MongoClient(uri);

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

// const collection = client.db().collection("data");

// collection
//   .find()
//   .toArray()
//   .then((documents) => {
//     console.log("Retrieved documents:", documents);
//   })
//   .catch((err) => {
//     console.error("Error retrieving documents:", err);
//   });
