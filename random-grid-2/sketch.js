function setup() {
  createCanvas(640, 640);
}

function draw() {
  // Talma, Spectrum 7 Colors
  background('#487A9C'); // Teal
  noSmooth();
  stroke('#E1C779'); // Pollen 
  strokeWeight(20);
  noFill();
  
  randomSeed(mouseX);
  
  var m = 84; 
  
  for (var y=0; y < height; y+=m) {
    for (var x = 0; x < width; x+=m) {
      var j = round(random(5));
      if (j === 1) {
        line(x, y, x+m, y+m);
        line(x, y+m, x+m, y);
      } else if (j === 2) {
        line(x, y, x+m, y+m);
      } else if (j === 3) {
        line(x, y+m, x+m, y);
      } else if (j === 4) {
      }
    }
  }

}