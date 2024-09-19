const axios = require("axios");
const TOKEN = "REVeRNHoXRdST7I0tqFE32zxcnVpq44tIxTCh5gfURc";
const { parentPort } = require("worker_threads");

function send_messag_to_line(message) {
  let config = {
    method: "post",
    maxBodyLength: Infinity,
    url: `https://notify-api.line.me/api/notify?message=${message}`,
    headers: {
      Authorization: `Bearer ${TOKEN}`,
    },
  };

  axios
    .request(config)
    .then((response) => {
    //   console.log(JSON.stringify(response.data));
    })
    .catch((error) => {
    //   console.log(error);
    });
}

parentPort.on("message", (message) => {
  send_messag_to_line(message);
});
