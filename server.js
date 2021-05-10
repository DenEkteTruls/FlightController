const WebSocket = require("ws");
const fs = require("fs");
const socket = new WebSocket.Server({port: 8081});

fs.writeFile("data.json", '[]', "utf-8", function(){});

socket.on('connection', socket => {
    console.log("new connection!");
    socket.on('message', message => {
        fs.readFile("data.json", "utf-8", function(err, data) {
            if(err) console.log(err);
            else {
                let old_data = JSON.parse(data);
                var n_data = message.split("|");
    
                old_data.push({
                    "cnt": parseInt(n_data[0]),
                    "lat": parseFloat(n_data[1]),
                    "lng": parseFloat(n_data[2]),
                    "alt": parseFloat(n_data[3])
                });
                
                json = JSON.stringify(old_data);
                fs.writeFile("data.json", json, "utf-8", function(){});
            }
        });
    });
});