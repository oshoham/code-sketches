var points;
var intersectionStack;
var radius;

function setup() {
  points = [];
  intersectionStack = [];
  radius = 10;
  
  points.push(createVector(0, 0));
  points.push(createVector())
}

function draw() {
  background(0);
  
  points.forEach(function (p)) {
    ellipse(p.x, p.y, radius, radius)
  }
}