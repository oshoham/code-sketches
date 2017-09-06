//
//  Polygon.cpp
//  tiling-patterns
//
//  Created by Oren Shoham on 2/2/17.
//
//

#include "Polygon.h"

void MyPolygon::addVertex(int x, int y) {
    ofVec2f a(x, y);
    addVertex(a);
}

void MyPolygon::addVertex(ofVec2f v) {
    int nVertices = vertices.size();
    if (nVertices > 0) {
        ofPoint previous = vertices[nVertices-1];
        Edge edge = Edge(previous, v, hankinAngle, hankinDelta);
        edges.push_back(edge);
    }
    vertices.push_back(v);
}

void MyPolygon::close() {
    ofPoint last = vertices.back();
    ofPoint first = vertices.front();
    
    Edge edge = Edge(last, first, hankinAngle, hankinDelta);
    edges.push_back(edge);
}

void MyPolygon::hankin() {
    for (auto & edge : edges) {
        edge.hankin();
    }
    
    for (int i = 0; i < edges.size(); i++) {
        for (int j = 0; j < edges.size(); j++) {
            if (i != j) {
                edges[i].findEnds(edges[j]);
            }
        }
    }
}

void MyPolygon::setHankinValues(int hankinAngle, int hankinDelta) {
    hankinAngle = hankinAngle;
    hankinDelta = hankinDelta;
    
    for (auto & edge : edges) {
        edge.hankinAngle = hankinAngle;
        edge.hankinDelta = hankinDelta;
    }
}

void MyPolygon::draw() {
    for (auto edge : edges) {
        edge.draw();
    }
}
