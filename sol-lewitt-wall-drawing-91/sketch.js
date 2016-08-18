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
  background(255);
  noFill();

  randomSeed(0);

  // figure out how many squares we can fit on the screen
  var numSquares = ceil(width / squareSize);
  for (var i = 0; i < numSquares; i++) {
    for (var j = 0; j < numSquares; j++) {
      stroke(0);
      strokeWeight(0.05);

      // rPoint is where we draw the square
      var rPoint = createVector(i * squareSize, j * squareSize);
      rect(rPoint.x, rPoint.y, squareSize, squareSize);

      // need at least one line of each color
      var numRed = round(random(1, 4));
      var numBlue = round(random(1, 4));
      var numYellow = round(random(1, 4));
      
      strokeWeight(1);
      
      var points;
      var start;
      var end;
      
      // draw the lines betweenly randomly chosen points
      // on two of the walls of the square

      for (var k = 0; k < numRed; k++) {
        stroke(r);
        drawLineBetweenWalls(rPoint.x, rPoint.y, squareSize, squareSize);
      }

      for (var l = 0; l < numBlue; l++) {
        stroke(b);
        drawLineBetweenWalls(rPoint.x, rPoint.y, squareSize, squareSize);
      }

      for (var m = 0; m < numYellow; m++) {
        stroke(y);
        drawLineBetweenWalls(rPoint.x, rPoint.y, squareSize, squareSize);
      }
    }
  }
  
  // increment time
  t += 0.005;
}

function drawLineBetweenWalls(rectX, rectY, rectWidth, rectHeight) {
  // generate a start and end point, each of which are on different walls
  // of the square
  points = getRandomPointsOnRect(rectX, rectY, rectWidth, rectHeight);
  start = points[0];
  end = points[1];
  drawNoisyLine(start, end);
}

function drawNoisyLine(start, end) {
  // draw a line between start and end with some random perturbation
  var numIntermediatePoints = 10;
  
  beginShape();
  vertex(start.x, start.y);
  for (var i = 0; i < numIntermediatePoints; i++) {
    vertex(
      lerp(start.x, end.x, i / numIntermediatePoints) + random(-1, 1),
      lerp(start.y, end.y, i / numIntermediatePoints) + random(-1, 1)
    );
  }
  vertex(end.x, end.y);
  endShape();
}

function getRandomPointsOnRect(rectX, rectY, rectWidth, rectHeight) {
  // pick the two walls that we'll be drawing between
  var wallPair = generateWallPair();
  var startingWall = wallPair[0];
  var endingWall = wallPair[1];
  // pick random points on the starting and ending walls
  var startPoint = getRandomPointOnWall(rectX, rectY, rectWidth, rectHeight, startingWall);
  var endPoint = getRandomPointOnWall(rectX, rectY, rectWidth, rectHeight, endingWall);
  return [startPoint, endPoint];
}

function generateWallPair() {
  // pick a starting wall at random, then remove it
  // from the list of available walls and pick an ending wall
  var walls = [0, 1, 2, 3];
  var startingWall = random(walls);
  walls.splice(startingWall, 1);
  var endingWall = random(walls);
  return [startingWall, endingWall];
}

function getRandomPointOnWall(rectX, rectY, rectWidth, rectHeight, wall) {
  // pick a random point on the specified wall of the square
  // then move it around using Perlin noise
  // use constrain() to make sure the point doesn't leave the wall
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