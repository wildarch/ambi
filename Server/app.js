const express = require('express');
const http = require('http');
const url = require('url');
const WebSocket = require('ws');

const app = express();

app.use(function (req, res) {
  res.send({ msg: "hello" });
});

const server = http.createServer(app);
const wss = new WebSocket.Server({ server });

var store = {
    alerts: {
        temperature: false,
        oxygen: true,
        humidity: false,
        light: false,
        noise: false
    },
    progress: 50,
    expression: 'happy'
}

wss.on('connection', function connection(ws) {
  const location = url.parse(ws.upgradeReq.url, true);
  // You might use location.query.access_token to authenticate or share sessions
  // or ws.upgradeReq.headers.cookie (see http://stackoverflow.com/a/16395220/151312)
    ws.send(JSON.stringify(store));

  ws.on('message', function incoming(message) {
      var parsed = JSON.parse(message);
      store.alerts = parsed.alerts;
      store.progress = parsed.progress;
      store.expression = parsed.expression
      console.log("New store:");
      console.log(store);
      wss.clients.forEach(function each(client) {
      if (client !== ws && client.readyState === WebSocket.OPEN) {
        client.send(JSON.stringify(store));
      }
    });
  });

});

server.listen(8888, function listening() {
  console.log('Listening on %d', server.address().port);
});
