function setup() {
  createCanvas(360, 360);
}

function draw() {
  background('#ecece4');
  stroke(0);
  
  translate(width / 2, height / 2);
  
  var time = millis() / 1000;
  
  for (var i = 0; i < 8; i++) {
    push();
    rotate(map(i, 0, 8, 0, TWO_PI));
    
    push();
    rotate(map(time, 0, 15, 0, TWO_PI))
    translate(0, -30);
    drawTriangleLines(0, 0, 30);
    pop();
    
    push();
    rotate(0.5 * QUARTER_PI)
    rotate(map(time, 0, 30, TWO_PI, 0))
    translate(0, -50);
    drawTriangleLines(0, 0, 50);
    pop();
    
    push();
    rotate(map(time, 0, 60, 0, TWO_PI))
    translate(0, -80);
    drawTriangleLines(0, 0, 80);
    pop();
    
    pop();
  }
}

function drawTriangleLines(px, py, r) {
  line(px, py - r, px - 0.3 * r, py);
  line(px, py - r, px - 0.18 * r, py);
  line(px, py - r, px - 0.06 * r, py);
  line(px, py - r, px + 0.06 * r, py);
  line(px, py - r, px + 0.18 * r, py);
  line(px, py - r, px + 0.3 * r, py);
}

// function windowResized() {
//   resizeCanvas(windowWidth, windowHeight)
// }