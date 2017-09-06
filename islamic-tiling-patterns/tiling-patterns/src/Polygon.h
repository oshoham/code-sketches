#pragma once

#include "ofMain.h"
#include "Edge.h"

class MyPolygon {
    public:
        MyPolygon() : hankinAngle(DEFAULT_HANKIN_ANGLE), hankinDelta(DEFAULT_HANKIN_DELTA) {}
        MyPolygon(int hankinAngle, int hankinDelta) : hankinAngle(hankinAngle), hankinDelta(hankinDelta) {}
    
        void addVertex(int x, int y);
        void addVertex(ofVec2f v);
        void close();
        void hankin();
        void setHankinValues(int hankinAngle, int hankinDelta);
        void draw();
    
        vector<Edge> edges;
        vector<ofVec2f> vertices;
        int hankinAngle;
        int hankinDelta;
};
