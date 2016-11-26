var kNbrDots;
var rStart;
var timeSinceLastUpdate;
  
function setup() {
  createCanvas(512, 512);
  // smooth();
  kNbrDots = 128;
  rStart = 30.0 + random(60);
  timeSinceLastUpdate = 0;
  background(0);
  rectMode(CENTER);
  noFill();
}
  
function setDayglowColor(myHue) {
  var ph = sin(millis() * 0.0001);
  
  var rr = parseInt(sin(myHue) * 127 + 128);
  var gg = parseInt(sin(myHue + (2*ph) * PI/3) * 127 + 128);
  var bb = parseInt(sin(myHue + (4*ph) * PI/3) * 127 + 128);
  stroke(rr,gg,bb);
}
  
function draw() {
  background(0); // try blur here at smaller sizes...
  stroke(255);
  // filter(BLUR);
  // filter(ERODE);
    
  var n = millis() * 0.0001;// + rStart;
  var rad = width * 0.97/2;
  var cx = width / 2;
  var cy = height / 2;
  
  for (var i = 0; i <= kNbrDots; ++i) {
    var theta = i * PI * 2 / kNbrDots;
    // setDayglowColor(n + theta / 6);
    var r = rad * sin(n * theta);
    var px = cx + cos(theta) * r;
    var py = cy + sin(theta) * r;
    // ellipse(px, py, 4, 4);
    var size = map(theta, 0, 6.3, 4, 16);
    var vectorTowardsCenter = p5.Vector.sub(createVector(width / 2, height / 2), createVector(px, py));

    push();
    translate(px, py);
    rotate(vectorTowardsCenter.heading() + HALF_PI);
    triangle(
      0, -size,
      -size, size,
      size, size
    );
    rotate(vectorTowardsCenter.heading() + HALF_PI);
    triangle(
      0, -size,
      -size, size,
      size, size
    );
    rotate(vectorTowardsCenter.heading() + HALF_PI);
    triangle(
      0, -size,
      -size, size,
      size, size
    );
    rotate(vectorTowardsCenter.heading() + HALF_PI);
    triangle(
      0, -size,
      -size, size,
      size, size
    );
    pop();
  }
}