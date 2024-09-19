// module
const bodyParser = require("body-parser");
const { Worker } = require("worker_threads");
const express = require("express");
const cors = require('cors');
const app = express();
const LED_worker = new Worker("./handle_LED.js");
const ADC_worker = new Worker("./handle_adc_value.js");
const Line_notify_worker = new Worker("./handle_line_notify.js");

// const adc = require("./handle_adc_value");
// const LED = require("./handle_LED");

let adcStatus = false;
let isShine = false;

app.use(cors());
app.use(express.static("./public"));
app.use(bodyParser.json());

// express
app.get("/hello", (req, res) => {
  res.send("Hello World!");
});

app.post("/line_notify", (req, res) => {
  Line_notify_worker.postMessage(req.body.message);
  res.sendStatus(200);
});

app.get("/isDancing", (req, res) => {
  res.send(isShine);
});

app.post("/dancing", (req, res) => {
  isShine = req.body.isShine;
  LED_worker.postMessage(req.body.isShine);
  res.sendStatus(200);
});

app.get("/get_ADC_status", (req, res) => {
  res.send(adcStatus);
});

// get data from worker
// adc
setInterval(() => {
  ADC_worker.postMessage("給我資料!");
}, 1000);
ADC_worker.on("message", (message) => {
  adcStatus = message;
});

// 掛載到 poat 8080
const PORT = process.env.PORT || 8080;

app.listen(PORT, () => {
  console.log(`Server is running on port ${PORT}`);
});

const https = require("https");
