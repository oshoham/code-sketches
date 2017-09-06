#pragma once

#include "ofMain.h"
#include "Hankin.h"

const int DEFAULT_HANKIN_ANGLE = 75;
const int DEFAULT_HANKIN_DELTA = 10;

class Edge {
    public:
        Edge(ofVec2f a, ofVec2f b) : Edge(a, b, DEFAULT_HANKIN_ANGLE, DEFAULT_HANKIN_DELTA) {}
        Edge(ofVec2f a, ofVec2f b, int hankinAngle, int hankinDelta) : a(a), b(b), hankinAngle(hankinAngle), hankinDelta(hankinDelta) {}
    
        void hankin();
        void findEnds(Edge edge);
        void draw();
    
        ofVec2f a;
        ofVec2f b;
        Hankin h1;
        Hankin h2;
        int hankinAngle;
        int hankinDelta;
};
