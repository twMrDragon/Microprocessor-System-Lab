const { exec } = require("child_process");
const { parentPort } = require("worker_threads");

let isShine = false;

const dance = [0, 0, 0, 0];

// call c++ set led status
function set_LED_status(led, status) {
  exec(
    `sudo ../script/use_char_driver ${led} ${status}`,
    (error, stdout, stderr) => {}
  );
}

setInterval(() => {
  if (!isShine) {
    for (let index = 0; index < dance.length; index++) dance[index] = 0;
    for (let index = 0; index < dance.length; index++)
      set_LED_status(`LED${index + 1}`, "off");
  } else {
    const lastElement = dance[dance.length - 1];
    let insertElement = lastElement == 0 ? 1 : 0;
    dance.shift();
    dance.push(insertElement);

    for (let index = 0; index < dance.length; index++) {
      let ledStatus = dance[index] == 0 ? "off" : "on";
      set_LED_status(`LED${index + 1}`, ledStatus);
    }
  }
  //   console.log(isShine);
  //   console.log(dance);
}, 500);

parentPort.on("message", (message) => {
  isShine = message;
});
