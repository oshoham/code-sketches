var points;
var t;

function setup() {
  createCanvas(640, 640);
  points = [];
  for (var i = 0; i < 50; i++) {
    points.push(createVector(random(width), random(height)));
  }
  t = 0;
}

function draw() {
  background('#ecece4');
  stroke(0);
  strokeWeight(0.03);
  
  for (var i = 0; i < points.length; i++) {
    // ellipse(points[i].x, points[i].y, 1, 1);
    for (var j = 0; j < points.length; j++) {
      if (i === j) {
        continue;
      }
      line(points[i].x, points[i].y, points[j].x, points[j].y);
    }
  }
  
  if (t % 1 < 0.2) {
    points.splice(0, 1);
    points.push(createVector(random(width), random(height)));
  }
  
  t += 0.2;
}