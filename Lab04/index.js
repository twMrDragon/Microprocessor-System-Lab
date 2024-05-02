const GPIO = require("onoff").Gpio;
const bodyParser = require("body-parser");
const express = require("express");
const app = express();

const LEDs = [
  new GPIO(466, "out"),
  new GPIO(255, "out"),
  new GPIO(481, "out"),
  new GPIO(254, "out"),
];

app.use(express.static("./public"));
app.use(bodyParser.json());

app.get("/index", (req, res) => {
  res.send("Hello World!");
});

app.post("/switchLED", (req, res) => {
  req.body.selected.forEach((element) => {
    LEDs[element].writeSync(req.body.state == "ON" ? 1 : 0);
  });
  res.sendStatus(200);
});

app.post("/shineMode", (req, res) => {
  for (let i = 0; i < req.body.times * 2; i++) {
    setTimeout(() => {
      var flag = i % 2 == 0;
      for (let j = 0; j < LEDs.length; j++) {
        if (j == LEDs.length / 2) flag = !flag;
        LEDs[j].writeSync(flag ? 1 : 0);
      }
    }, i * 500);
  }
  setTimeout(() => {
    for (let i = 0; i < LEDs.length; i++) {
      LEDs[i].writeSync(0);
    }
  }, req.body.times * 2 * 500);
  res.sendStatus(200);
});

const PORT = process.env.PORT || 8080;

app.listen(PORT, () => {
  console.log(`Server is running on port ${PORT}`);
});
