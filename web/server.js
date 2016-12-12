var express = require('express');
var fs = require('fs');
var app = express();
var http = require('http').Server(app);
var io = require('socket.io')(http);
var bodyParser = require('body-parser');
var path = require('path');
var multipart = require('connect-multiparty');
var multipartMiddleware = multipart();

app.use(bodyParser.json());
app.use(bodyParser.urlencoded({extended: true}));
app.use(express.static(__dirname));

app.get('/', function(req, res){
  res.sendFile(path.join(__dirname, 'static/html/base.html'));
});

app.post('/', multipartMiddleware, function(req, res, next) {
	io.emit('data', new Buffer(
		fs.readFileSync(req.files.image.path)
	).toString('base64'));
	res.send();
});

io.on('connection', function(socket){
  console.log('websocket -> connected');
});

http.listen(8080, function(){});
