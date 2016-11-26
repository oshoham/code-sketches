var linePoints;
var yStart;
var colors;

function setup() {
  createCanvas(640, 640);
  linePoints = [];
  colors = ['#EE434B', '#FAF301', '#008BD3'];
  yStart = 50;
  
  var t = 0.0;
  for (var i = 0; i < width; i++) {
    linePoints.push(createVector(i, yStart + map(noise(t), 0, 1, -20, 20)));
    t += 0.1;
  }
}

function draw() {
  background(255);
  
  var weight = 5;
  strokeWeight(weight);
  
  stroke(0);
  beginShape();
  linePoints.forEach(function (linePoint) {
    vertex(linePoint.x, linePoint.y);
  });
  endShape();
  
  var colorIndex = 0;
  for (var yoffset = yStart; yoffset < height; yoffset += (weight + weight * 2)) {
    stroke(colors[colorIndex]);
    beginShape();
    for (var i = 0; i < linePoints.length; i++) {
      vertex(linePoints[i].x, yoffset + linePoints[i].y);
    }
    endShape();
    colorIndex = (colorIndex + 1) % colors.length;
  }
}