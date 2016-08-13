#include "sine.h"

//--------------------------------------------------------------
sine::sine(ofPoint position, int w, float theta, float amplitude, float period, ofColor color): position(position), xspacing(1.0), w(w), theta(theta), amplitude(amplitude), period(period), color(color) {
    dx = (TWO_PI / period) * xspacing;
    
    float x = theta;
    for (int i = 0; i < floor(w / xspacing); i++) {
        yvalues.push_back(sin(x) * amplitude);
        x += dx;
    }
}

//--------------------------------------------------------------
void sine::update() {
    //    theta += 0.02;
    
    float x = theta;
    for (int i = 0; i < yvalues.size(); i++) {
        yvalues[i] = sin(x) * amplitude;
        x += dx;
    }
}

//--------------------------------------------------------------
void sine::draw() {
    line.clear();
    
    for (int x = 0; x < yvalues.size(); x++) {
        line.addVertex((position.x + x) * xspacing, position.y + yvalues[x]);
    }
    
    ofSetLineWidth(2);
    ofSetColor(color);
    line.draw();
}