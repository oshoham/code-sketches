var r;
var b;
var y;
var squareSize;
var t;

function setup() {
  createCanvas(640, 640);
  r = '#DD5857';
  b = '#367ED3';
  y = '#F4D40E';
  squareSize = 80;
  t = 0.0;
}

function draw() {
  // background('#EDEDEA');
  background(255);
  noFill();

  randomSeed(0);

  var numSquares = ceil(width / squareSize);
  for (var i = 0; i < numSquares; i++) {
    for (var j = 0; j < numSquares; j++) {
      stroke(0);
      strokeWeight(0.05);

      var rPoint = createVector(i * squareSize, j * squareSize);
      rect(rPoint.x, rPoint.y, squareSize, squareSize);

      var numRed = round(random(1, 4));
      var numBlue = round(random(1, 4));
      var numYellow = round(random(1, 4));
      strokeWeight(1);

      for (var k = 0; k < numRed; k++) {
        stroke(r);
        var points = getRandomPointsOnRect(rPoint.x, rPoint.y, squareSize, squareSize);
        var start = points[0];
        var end = points[1];
        drawNoisyLine(start, end);
      }

      for (var l = 0; l < numBlue; l++) {
        stroke(b);
        var points = getRandomPointsOnRect(rPoint.x, rPoint.y, squareSize, squareSize);
        var start = points[0];
        var end = points[1];
        drawNoisyLine(start, end);
      }

      for (var m = 0; m < numYellow; m++) {
        stroke(y);
        var points = getRandomPointsOnRect(rPoint.x, rPoint.y, squareSize, squareSize);
        var start = points[0];
        var end = points[1];
        drawNoisyLine(start, end);
      }
    }
  }
  
  t += 0.005;
}

function drawNoisyLine(start, end) {
  var numIntermediatePoints = 10;
  
  beginShape();
  vertex(start.x, start.y);
  for (var i = 0; i < numIntermediatePoints; i++) {
    vertex(lerp(start.x, end.x, i / numIntermediatePoints) + random(-1, 1), lerp(start.y, end.y, i / numIntermediatePoints) + random(-1, 1));
  }
  vertex(end.x, end.y);
  endShape();
}

function getRandomPointsOnRect(rectX, rectY, rectWidth, rectHeight) {
  var wallPair = generateWallPair();
  var startingWall = wallPair[0];
  var endingWall = wallPair[1];
  var startPoint = getRandomPointOnWall(rectX, rectY, rectWidth, rectHeight, startingWall);
  var endPoint = getRandomPointOnWall(rectX, rectY, rectWidth, rectHeight, endingWall);
  return [startPoint, endPoint];
}

function generateWallPair() {
  var walls = [0, 1, 2, 3];
  var startingWall = random(walls);
  walls.splice(startingWall, 1);
  var endingWall = random(walls);
  return [startingWall, endingWall];
}

function getRandomPointOnWall(rectX, rectY, rectWidth, rectHeight, wall) {
  var p = createVector();
  var noisePermutation = random(0, 2);
  var n = map(noise(t + noisePermutation), 0, 1, -100, 100);
  switch (wall) {
    case 0:
      p.set(rectX, constrain(random(rectY, rectY + rectHeight) + n, rectY, rectY + rectHeight));
      break;
    case 1:
      p.set(constrain(random(rectX, rectX + rectWidth) + n, rectX, rectX + rectWidth), rectY);
      break;
    case 2:
      p.set(rectX + rectWidth, constrain(random(rectY, rectY + rectHeight) + n, rectY, rectY + rectHeight));
      break;
    case 3:
      p.set(constrain(random(rectX, rectX + rectWidth) + n, rectX, rectX + rectWidth), rectY + rectHeight);
      break;
  }
  return p;
}