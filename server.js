const WebSocket = require("ws");
const fs = require("fs");
const socket = new WebSocket.Server({port: 8081});

function geoVinkel(lat1, long1, lat2, long2, alt1, alt2) {
    dN = lat2-lat2;
    dE = long2-long1;
    r = 6371*1000
    r2 = r*Math.cos(lat1*Math.PI/180);
    dNm = Math.sqrt(2*(r**2)-2*(r**2)*Math.cos(dE*Math.PI/180));
    dNm = Math.sqrt(2*(r2**2)-2*(r2**2)*Math.cos(dE*Math.PI/180));
    dH = alt2-alt1;

    if(dEm == 0) dEm == 0.00000000001;
    Vh1 = Math.atan(dNm/dEm)*180/Math.PI;

    if(dN >= 0) {
        if(dE >= 0) {
            Vh = 90 - Vh1
        } else {
            Vh = 270+Vh1
        }
    } if(dN < 0) {
        if(dE >= 0) {
            Vh = 90+Vh1;
        } else {
            Vh = 270+Vh1;
        }
    }

    L = Math.sqrt(dNm**2+dEm**2);
    Al = Math.sqrt(L**2+dH**2);
    Vv = Math.atan(dH/L)*180/Math.PI;

    return Al, Vv, Vh;
}

function write_to_database(new_data, filename) {
    var old_data = [];
    fs.readFile(filename, "utf-8", function(err, data) {
        if(err) console.log(err);
        else {
            old_data = JSON.parse(data);
            old_data.push(new_data.split("|"));
        }
    });

    if(old_data.length > 0) {

        flyLat = new_data.split("|")[1]
        flyLng = new_data.split("|")[2]
        flyAlt = new_data.split("|")[3]

        oLat = old_data[old_data.length-1][1]
        oLng = old_data[old_data.length-1][2]
        oAlt = old_data[old_data.length-1][3]

        avstand, vV, hV = geovinkel(flyLat, flyLng, oLat, oLng, flyAlt, oAlt);

        console.log(avstand);
        console.log(vV);
        console.log(hV);
    }

    json = JSON.stringify(old_data);
    fs.writeFile(filename, json, "utf-8", function(){});
}

socket.on('connection', socket => {
    console.log("new connection!");
    socket.on('message', message => {
        //console.log(message);
        write_to_database(message, "data.json")
    });
});