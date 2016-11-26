function setup() {
  createCanvas(windowWidth, windowHeight);
}

function draw() {
  background('#ecece4');
  stroke(0);
  
  translate(width / 2, height / 2);
  
  drawPupil();
  
  // drawEye();
  
  drawSpikes();
  
  drawMiscLines();
}

function drawPupil() {
  for (var i = 0; i < 26; i++) {
    push();
    rotate(map(i, 0, 26, 0, TWO_PI));
    line(0, 0, 0, -40);
    pop();
  }
}

function drawEye() {
  for (var i = 0; i < 10; i++) {
    var angle = map(i, 0, 10, 0, TWO_PI);
    push();
    translate(37 * 4 * cos(angle), 37 * sin(angle));
    drawHorizontalLines(0, 0, 4, 120, 13, 0);
    pop();
  }
}

function drawSpikes() {
  for (var i = 0; i < 24; i++) {
    push();
    rotate(map(i, 0, 24, 0, TWO_PI));
    translate(0, -250);
    drawTriangleLines(0, 0, 80);
    if (i % 2 === 0) {
      drawHorizontalLines(0, 0, 5, 80, 10);
    }
    pop();
  }
}

function drawMiscLines() {
  for (var i = 0; i < 2; i++) {
    push();
    rotate(map(i, 0, 2, 0, TWO_PI));
    translate(0, -200);
    drawVerticalLines(0, 0, 10, 60, 9);
    pop();
    
    push();
    rotate(map(i, 0, 2, 0, TWO_PI));
    translate(0, -150);
    for(var j = 0; j < 14; j++) {
      
    }
    pop();
    
    // push();
    // rotate(map(i, 0, 2, HALF_PI, PI + HALF_PI));
    // translate(0, -200);
    // drawVerticalLines(0, 0, 10, 60, 9);
    // pop();
  }
}

function drawHorizontalLines(px, py, numLines, lineLength, spacing, lineAngle) {
  var distance = 0.5 * lineLength;
  for (var i = 0; i < numLines; i++) {
     line(px - distance, py + spacing * i, px + distance, py + spacing * i);
  }
}

function drawTriangleLines(px, py, r) {
  line(px, py - r, px - 0.25 * r, py);
  line(px, py - r, px - 0.15 * r, py);
  line(px, py - r, px - 0.05 * r, py);
  line(px, py - r, px + 0.05 * r, py);
  line(px, py - r, px + 0.15 * r, py);
  line(px, py - r, px + 0.25 * r, py);
}

function drawVerticalLines(px, py, numLines, lineLength, spacing) {
  var distance = 0.5 * lineLength;
  for (var i = -(numLines * 0.5); i < (numLines * 0.5); i++) {
    line(px + spacing * i + (spacing / 2), py, px + spacing * i + (spacing / 2), py + distance);
  }
}

function windowResized() {
  resizeCanvas(windowWidth, windowHeight);
}