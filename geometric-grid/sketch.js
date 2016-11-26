function setup() {
  createCanvas(640, 640);
  ellipseMode(CORNER);
}

function draw() {
  background('#6984B8'); // Buscabulla
  noStroke();
  fill('#FFE4F3'); // Pinking
  
  var w = width / 18;
  var h = height / 48;
  for (var col = 0; col < 18; col++) {
    for (var row = 0; row < 48; row++) {
      if ((row + col) % 2 === 0) {
        rect(w * col + w / 8, h * row + h / 8, w * 3 / 4, h * 3 / 4);
      } else {
        ellipse(w * col + w / 8, h * row + h / 8, w * 3 / 4, h * 3 / 4);
      }
    }
  }
}

function windowResized() {
  resizeCanvas(windowWidth, windowHeight);
}