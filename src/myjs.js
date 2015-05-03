var getWeather = function() {
    navigator.geolocation.getCurrentPosition(findMe);
   function findMe(pos) {
    var lat = pos.coords.latitude;
     var dict = {"KEY_LATITUDE" : lat};
    Pebble.sendAppMessage(dict);
   }
};

Pebble.addEventListener("ready",
  function(e) {
    //App is ready to receive JS messages
    getWeather();
  }
);

