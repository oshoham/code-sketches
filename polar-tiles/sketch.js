var backgroundColor;
var greens;
var grays;

function setup() {
  createCanvas(500, 500);
  backgroundColor = '#ACA6B2';
  greens = ['#819E88', '#97C0A2', '#819E88', '#819E88'];
  grays = ['#C4BBB7', '#E1D4C4', '#D7CBCB', '#C1BFCA', '#E0D5D2'];
}

function draw() {
  randomSeed(200);
  background(backgroundColor);
  
  drawTiledCircle(718, 72, grays, true);
  drawTiledCircle(671, 72, grays, false);
  drawTiledCircle(623, 72, grays, true);
  drawTiledCircle(575, 72, ['#819E88'], false);
  drawTiledCircle(528, 72, grays, true);
  drawTiledCircle(481, 72, grays, false);
  drawTiledCircle(434, 72, grays, true);
  drawTiledCircle(387, 72, grays, false);
  drawTiledCircle(340, 72, grays, true);
  drawTiledCircle(293, 72, grays, false);
  drawTiledCircle(247, 72, grays, true);
  drawTiledCircle(200, 72, grays, false);
  drawTiledCircle(153, 12, greens, true);
  drawTiledCircle(107, 12, greens, false);
  drawTiledCircle(63, 12, greens, true);
  
  // draw center circle
  fill('#819E88');
  stroke('#819E88');
  ellipse(width / 2, height / 2, 20, 20);
}

function drawTiledCircle(radius, numTiles, colors, clockwise) {
  var tileHeight = 40;
  var centerX = width / 2;
  var centerY = height / 2;
  var tileSpacing = QUARTER_PI;
  var tileWidth = (TWO_PI / numTiles) - (tileSpacing / (numTiles - 1));
  var rotation = millis() / 5000 * random(0.1, 1);
  if (!clockwise) {
    rotation *= -1;
  }
  
  push();
  translate(centerX, centerY);
  rotate(rotation);
  translate(-centerX, -centerY);
  for (var i = 0; i < numTiles; i++) {
    var angle = map(i, 0, numTiles, 0, TWO_PI);
    var c = random(colors);
    stroke(c);
    fill(c);
    arc(centerX, centerY, radius, radius, angle, angle + tileWidth);
  }
  pop();
  
  fill(backgroundColor);
  stroke(backgroundColor);
  ellipse(centerX, centerY, radius - tileHeight, radius - tileHeight);
}