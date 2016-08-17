var numLines;
var xPadding;
var yPadding;

function setup() {
  createCanvas(windowWidth, windowHeight);
  numLines = 6;
  xPadding = width / numLines / 2;
  yPadding = height / numLines / 2;
}

function draw() {
  background('#ecece4');
  stroke(0);
  
  drawVerticalLines();
  drawHorizontalLines();
  drawX();
}

function drawVerticalLines() {
  for (var i = 0; i < numLines; i++) {
    var x = xPadding + i * (width / numLines);
    line(x, yPadding, x, height - yPadding);
  }
}

function drawHorizontalLines() {
  for (var i = 0; i < numLines; i++) {
    var y = yPadding + i * (height / numLines);
    line(xPadding, y, width - xPadding, y);
  }
}

function drawX() {
  // forward slash
  line(
    xPadding + (width / numLines),
    yPadding + (height / numLines),
    xPadding + (numLines - 2) * (width / numLines),
    yPadding + (numLines - 2) * (height / numLines)
  );

  // backslash
  line(
    xPadding + (numLines - 2) * (width / numLines),
    yPadding + (height / numLines),
    xPadding + (width / numLines),
    yPadding + (numLines - 2) * (height / numLines)
  );
}

function windowResized() {
  resizeCanvas(windowWidth, windowHeight);
  xPadding = width / numLines / 2;
  yPadding = height / numLines / 2;
}