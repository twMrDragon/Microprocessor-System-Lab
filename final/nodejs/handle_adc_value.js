const { exec } = require("child_process");
const { parentPort } = require("worker_threads");

const PREVIOUS_NUM = 60;
let zeroCount = 0;
const last60ADCValue = new Array(PREVIOUS_NUM).fill(1);

// call python read ADC value
function get_ADC_value() {
  return new Promise((resolve, reject) => {
    exec("sudo python3 ../script/get_adc_value.py", (error, stdout, stderr) => {
      if (error) {
        // console.error(`执行Python脚本时出错: ${error}`);
        reject(error);
        return;
      }
      let value = stdout.replace("adc_value= ", "").replace("\n", "").trim();
      resolve(value);
    });
  });
}

function get_sleep_status_by_adc() {
  return zeroCount < 50;
}

setInterval(async () => {
  let value = await get_ADC_value();
  if (value == "0") {
    zeroCount += 1;
  }
  last60ADCValue.push(value);

  let firstValue = last60ADCValue.shift();
  if (firstValue == "0") {
    zeroCount -= 1;
  }
  console.log(last60ADCValue);
  // console.log(zeroCount);
}, 1000);

parentPort.on("message", (message) => {
  // console.log(message);
  parentPort.postMessage(get_sleep_status_by_adc());
});
