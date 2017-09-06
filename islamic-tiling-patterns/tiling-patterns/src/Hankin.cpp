#include "Hankin.h"

void Hankin::findEnd(Hankin h) {
//    ofPoint intersection;
//    if (ofLineSegmentIntersection(ofPoint(a), ofPoint(b), ofPoint(h.a), ofPoint(h.b), intersection)) {
//        end = ofVec2f(intersection);
//    }
    
    float den = (h.v.y * v.x) - (h.v.x * v.y);
    if (den == 0) {
        return;
    }
    float numa = (h.v.x * (a.y - h.a.y)) - (h.v.y * (a.x - h.a.x));
    float numb = (v.x * (a.y - h.a.y)) - (v.y * (a.x - h.a.x));
    float ua = numa / den;
    float ub = numb / den;
    float x = a.x + (ua * v.x);
    float y = a.y + (ua * v.y);
    
    if (ua > 0 && ub > 0) {
        ofVec2f candidate(x, y);
        
        float d1 = candidate.distance(a);
        float d2 = candidate.distance(h.a);
        float d = d1 + d2;
        float diff = abs(d1 - d2);
        if (diff < 0.001) {
            if (!foundEnd) {
                end = candidate;
                prevD = d;
                foundEnd = true;
            } else if (d < prevD) {
                prevD = d;
                end = candidate;
            }
        }
    }
}

void Hankin::draw() {
    ofSetColor(255, 0, 255);
    ofDrawLine(a, end);
//    ofDrawLine(a, b);
//    ofSetColor(255);
//    ofFill();
//    ofDrawCircle(a, 4);
//    
//    if (foundEnd) {
//        ofSetColor(255, 255, 0);
//        ofDrawCircle(end, 4);
//    }
}
