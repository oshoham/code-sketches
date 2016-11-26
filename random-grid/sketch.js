function setup() {
  createCanvas(640, 640);
}

function draw() {
  background('#020100'); // Textured
  noSmooth();
  stroke('#A53643'); // Cranberry
  strokeWeight(15);
  noFill();
  
  randomSeed(mouseX);
  
  var m = 84;
  
  for (var y = 0; y < height; y += m) {
    for (var x = 0; x < width; x += m) {
      var j = round(random(9));
      if (j === 1) {
        ellipse(x + 0.5 * m, y + 0.5 * m, m, m);
      } else if (j === 2) {
        line(x, y + 0.5 * m, x + 0.5 * m, y + 0.5 * m);
        line(x + 0.5 * m, y + 0.5 * m, x + 0.5 * m, y);
      }  else if (j === 3) {
        line(x + m, y + 0.5 * m, x + 0.5 * m, y + 0.5 * m);
        line(x+0.5*m, y+0.5*m, x+0.5*m, y+m);
      } else if (j === 4) {
        line(x, y+0.5*m, x+0.5*m, y+m);
        line(x+0.5*m, y+m, x+m, y+0.5*m);
      } else if (j === 5) {
        line(x+0.5*m, y, x+m, y+0.5*m);
        line(x+0.5*m, y, x, y+0.5*m);
      } else if (j === 6) {
        line(x+0.5*m, y+0.5*m, x+m, y+0.5*m);
        line(x+0.5*m, y+0.5*m, x+0.5*m, y);
      } else if (j === 7) {
        line(x+0.5*m, y+0.5*m, x, y+0.5*m);
        line(x+0.5*m, y+0.5*m, x+0.5*m, y+m);
      }
    }
  }
}

function windowResized() {
  resizeCanvas(windowWidth, windowHeight);
}