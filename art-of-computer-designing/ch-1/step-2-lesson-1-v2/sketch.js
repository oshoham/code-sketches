var numLines;
var xPadding;
var yPadding;
var t;

function setup() {
  createCanvas(windowWidth, windowHeight);
  numLines = 6;
  xPadding = width / numLines / 2;
  yPadding = height / numLines / 2;
  t = 0;
}

function draw() {
  background('#ecece4');
  stroke(0);
  
  if (t > 0) {
    drawVerticalLines(xPadding, yPadding, width, height - yPadding, numLines);
    // drawVerticalLines(xPadding, yPadding, width / 2, height - yPadding, numLines / 2);
    push();
    translate(width / 2, height / 2);
    rotate(PI);
    translate(-(width / 2), -(height / 2));
    // drawVerticalLines(xPadding, yPadding, width / 2, height - yPadding, numLines / 2);
    pop();
    // drawVerticalLines(width / 2 + xPadding, yPadding, width / 2, height - yPadding, numLines / 2);
  }
  
  if (t > 25) {
    // drawHorizontalLines(xPadding, yPadding, width / 2, height, numLines);
    push();
    translate(width / 2, height / 2);
    rotate(PI);
    translate(-(width / 2), -(height / 2));
    // drawHorizontalLines(xPadding, yPadding, width / 2, height, numLines);
    pop();
    drawHorizontalLines(xPadding, yPadding, width - xPadding, height, numLines);
  }
  
  if (t > 50) {
    drawX(xPadding, yPadding, width, height, numLines);
    push();
    translate(width / 2, height / 2);
    rotate(PI);
    translate(-(width / 2), -(height / 2));
    // drawHalfX(xPadding, yPadding - 1, width, height, numLines);
    pop();
  }
  
  t = (t + 0.5) % 75;
}

function drawVerticalLines(x, y, w, h, n) {
  for (var i = 0; i < n; i++) {
    var lineX = x + i * (w / n);
    line(lineX, y, lineX, h);
  }
}

function drawHorizontalLines(x, y, w, h, n) {
  for (var i = 0; i < n; i++) {
    var lineY = y + i * (h / n);
    line(x, lineY, w, lineY);
  }
}

function drawX(x, y, w, h, n) {
  // forward slash
  line(
    x + (w / n),
    y + (h / n),
    x + (n - 2) * (w / n),
    y + (n - 2) * (h / n)
  );

  // backslash
  line(
    x + (w / n),
    y + (n - 2) * (h / n),
    x + (n - 2) * (w / n),
    y + (h / n)
  );
}

function drawHalfX(x, y, w, h, n) {
  // forward slash
  line(
    x + (w / n),
    y + (h / n),
    x + (n - 1) / 2 * (w / n),
    y + (n - 1) / 2 * (h / n)
  );

  // backslash
  line(
    x + (w / n),
    y + (n - 2) * (h / n),
    x + (n - 1) / 2 * (w / n),
    y + (n - 1) / 2 * (h / n)
  );
}

function windowResized() {
  resizeCanvas(windowWidth, windowHeight);
  xPadding = width / numLines / 2;
  yPadding = height / numLines / 2;
}