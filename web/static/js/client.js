var socket = io();

socket.on("data", function(obj){
	$("#intruder").html("<img height='500px' src=\"data:image/jpeg;base64," + obj.toString() + "\"/>");
});

particlesJS.load('particles', 'static/particles.json', function() {
  console.log('particles.js config loaded');
});
