#include "Edge.h"

void Edge::hankin() {
    ofVec2f mid = a.getMiddle(b);
    ofVec2f v1 = a - mid;
    ofVec2f v2 = b - mid;
    
    ofVec2f offset1 = mid;
    ofVec2f offset2 = mid;
    
    if (hankinDelta > 0) {
        v1.scale(hankinDelta);
        v2.scale(hankinDelta);
        
        offset1 = mid + v2;
        offset2 = mid + v1;
    }

    v1.normalize();
    v2.normalize();
    
    v1.rotate(-hankinAngle);
    v2.rotate(hankinAngle);

    h1 = Hankin(offset1, v1);
    h2 = Hankin(offset2, v2);
}

void Edge::findEnds(Edge edge) {
    h1.findEnd(edge.h1);
    h1.findEnd(edge.h2);
    h2.findEnd(edge.h1);
    h2.findEnd(edge.h2);
}

void Edge::draw() {
//    ofSetColor(255);
//    ofDrawLine(a, b);
    h1.draw();
    h2.draw();
}
