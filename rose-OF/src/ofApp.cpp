#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    kNbrDots = 512;
    rStart = 30.0 + ofRandom(60);
    ofSetCircleResolution(100);
    ofNoFill();
    
    mode = 0;
}

//--------------------------------------------------------------
void ofApp::update() {
    rStart = 30 + ofMap(ofGetMouseX(), 0, ofGetWidth(), 0, 60, true);
}

//--------------------------------------------------------------
void ofApp::setDayglowColor(float myHue) {
    float ph = sin(ofGetElapsedTimeMillis() * 0.0001);
    
    int rr = (int)(sin(myHue) * 127 + 128);
    int gg = (int)(sin(myHue + (2*ph) * PI/3) * 127 + 128);
    int bb = (int)(sin(myHue + (4*ph) * PI/3) * 127 + 128);
    ofSetColor(rr,gg,bb);
}

//--------------------------------------------------------------
void ofApp::draw() {
    ofBackground(0); // try blur here at smaller sizes...
    ofSetColor(255);
    // filter(BLUR);
    // filter(ERODE);
    
    float n = ofGetElapsedTimeMillis() * 0.0001 + rStart;
    float rad = ofGetWidth() * 0.97 / 2;
    float cx = ofGetWidth() / 2;
    float cy = ofGetHeight() / 2;
    
    for (int i = 0; i <= kNbrDots; ++i) {
        float theta = i * PI * 2 / kNbrDots;
        // setDayglowColor(n + theta / 6);
        float r = rad * sin(n * theta);
        float px = cx + cos(theta) * r;
        float py = cy + sin(theta) * r;
        
        if (mode == 0) {
            ofFill();
            ofDrawCircle(px, py, 1);
        } else if (mode == 1) {
            ofNoFill();
            ofSetRectMode(OF_RECTMODE_CENTER);
            ofDrawRectangle(px, py, ofMap(theta, 0, 6.3, 4, 16), ofMap(theta, 0, 6.3, 4, 16));
        } else if (mode == 2) {
            ofNoFill();
            ofDrawCircle(px, py, 100);
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == '1') {
        mode = 0;
    } else if (key == '2') {
        mode = 1;
    } else if (key == '3') {
        mode = 2;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
