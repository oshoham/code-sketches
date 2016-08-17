var radii;
var t;

function setup() {
  createCanvas(640, 640);
  radii = [];
  for (var i = 0; i < 50; i++) {
    radii.push(i * 50);
  }
  t = 0;
}

function draw() {
  background('#ecece4');
  stroke(0);
  strokeWeight(0.1);
  noFill();
  
  var centerX = width / 2;
  var centerY = height / 2;
  
  for (var i = 0; i < radii.length; i++) {
    var radius = radii[i];
    
    // circles in the center
    ellipse(centerX, centerY, radius, radius);
    
    // arcs from the top
    arc(width / 2, 0, radius, radius, 0, PI);
    
    // arcs from the bottom
    arc(width / 2, height, radius, radius, PI, 0);
    
    // arcs from the left
    arc(0, height / 2, radius, radius, 3 * HALF_PI, HALF_PI);
    
    // arcs from the right
    arc(width, height / 2, radius, radius, HALF_PI, 3 * HALF_PI);
    
    radii[i] += 0.1;
  }
  
  if (radii[0] > 50) {
    radii.unshift(0);
  }
}