var lines;
var lineLength;

function setup() {
  createCanvas(640, 640);
  lines = [];
  lineLength = 100;
}

function draw() {
  background('#ecece4');
  stroke(0);
  strokeWeight(0.25);
  
  for (var iterations = 0; iterations < 50; iterations++) {
    var angle = random(TWO_PI);
    var start = createVector(random(width), random(height));
    var newLine = {
      start: start,
      end: createVector(start.x + lineLength * cos(angle), start.y + lineLength * sin(angle))
    };
    
    var doesIntersect = false;
    for (var i = 0; i < lines.length; i++) {
      if (doLineSegmentsIntersect(newLine.start, newLine.end, lines[i].start, lines[i].end)) {
        doesIntersect = true;
        break;
      }
    }
    
    if (!doesIntersect) {
      lines.push(newLine);
    }
  }
  
  for (var j = 0; j < lines.length; j++) {
    var l = lines[j];
    line(l.start.x, l.start.y, l.end.x, l.end.y);
  }
}

// adapted from https://github.com/openframeworks/openFrameworks/blob/master/libs/openFrameworks/math/ofMath.cpp#L264
function doLineSegmentsIntersect(line1Start, line1End, line2Start, line2End) {
  var diffLine1 = p5.Vector.sub(line1End, line1Start);
  var diffLine2 = p5.Vector.sub(line2End, line2Start);
  var compareLine1 = diffLine1.x * line1Start.y - diffLine1.y * line1Start.x;
  var compareLine2 = diffLine2.x * line2Start.y - diffLine2.y * line2Start.x;
  
  return (
    (
      ((diffLine1.x * line2Start.y - diffLine1.y * line2Start.x) < compareLine1) !==
      ((diffLine1.x * line2End.y - diffLine1.y * line2End.x) < compareLine1)
    )
    &&
    (
      ((diffLine2.x * line1Start.y - diffLine2.y * line1Start.x) < compareLine2) !==
      ((diffLine2.x * line1End.y - diffLine2.y * line1End.x) < compareLine2)
    )
  );
}