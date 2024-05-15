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

LEDs.forEach((gpio) => {
  gpio.writeSync(1)
})

GPIO_CLOCK = new GPIO(427, "out");
GPIO_MOSI = new GPIO(429, "out");
GPIO_MISO = new GPIO(428, "in");
GPIO_CS = new GPIO(430, "out");

// GPIO_LED1 = new GPIO(466, "out");
// GPIO_LED2 = new GPIO(397, "out");

app.use(express.static("./public"));
app.use(bodyParser.json());

app.get("/index", (req, res) => {
  res.send("Hello World!");
});

// 手動控制 LED API
app.post("/switchLED", (req, res) => {
  req.body.selected.forEach((element) => {
    LEDs[element].writeSync(req.body.state == "ON" ? 0 : 1);
  });
  res.sendStatus(200);
});

app.post("/shineMode", (req, res) => {
  var times = req.body.times * 2
  shineLED(times)
  res.sendStatus(200);
});

async function shineLED(times) {
  for (let i = 0; i < times; i++) {
    var flag = i % 2 == 0;
    for (let j = 0; j < LEDs.length; j++) {
      if (j == LEDs.length / 2) flag = !flag;
      LEDs[j].writeSync(flag ? 0 : 1);
    }
    var adc_value = readadc(0, GPIO_CLOCK, GPIO_MOSI, GPIO_MISO, GPIO_CS);
    var sleep_time = Math.min(Math.max(100, adc_value), 500)
    await sleep(sleep_time);
  }
  for (let i = 0; i < LEDs.length; i++) {
    LEDs[i].writeSync(1);
  }
}

function sleep(ms) {
  return new Promise(resolve => setTimeout(resolve, ms))
}

// 讀取光敏電阻數值
app.get("/adc", (req, res) => {
  var adc_value = readadc(0, GPIO_CLOCK, GPIO_MOSI, GPIO_MISO, GPIO_CS);
  if (adc_value > 100) {
    LEDs[0].writeSync(0);
  } else {
    LEDs[0].writeSync(1);
  }
  if (adc_value > 200) {
    LEDs[1].writeSync(0);
  } else {
    LEDs[1].writeSync(1);
  }
  res.send({ adc_value: adc_value });
});

function readadc(adcnum, GPIO_CLOCK, GPIO_MOSI, GPIO_MISO, GPIO_CS) {
  if (adcnum > 7 || adcnum < 0) return -1;

  GPIO_CS.writeSync(1);
  GPIO_CLOCK.writeSync(0);
  GPIO_CS.writeSync(0);

  var commandout = adcnum;
  commandout |= 0x18;
  commandout <<= 3;

  for (let index = 0; index < 5; index++) {
    if ((commandout & 0x80) > 0) {
      GPIO_MOSI.writeSync(1);
    } else {
      GPIO_MOSI.writeSync(0);
    }
    commandout <<= 1;
    GPIO_CLOCK.writeSync(1);
    GPIO_CLOCK.writeSync(0);
  }

  adcout = 0;
  for (let index = 0; index < 12; index++) {
    GPIO_CLOCK.writeSync(1);
    GPIO_CLOCK.writeSync(0);

    adcout <<= 1;
    if (GPIO_MISO.readSync() != 0) {
      adcout |= 0x1;
    }
  }
  GPIO_CS.writeSync(1);
  adcout >>= 1;

  return adcout;
}

const PORT = process.env.PORT || 8080;

app.listen(PORT, () => {
  console.log(`Server is running on port ${PORT}`);
});

