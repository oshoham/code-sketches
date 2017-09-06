#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    numLines = 4000;
    for (int i = 1; i <= numLines; i++) {
        
        float a = sin((14.0 * PI * i) / numLines) * (pow(sin((16.0 * PI * i) / numLines), 2) + pow(sin((14.0 * PI * i) / numLines), 2));
        float b = cos((14.0 * PI * i) / numLines) * (pow(sin((16.0 * PI * i) / numLines), 2) + pow(sin((14.0 * PI * i) / numLines), 2));
        float c = sin((30.0 * PI * i) / numLines) * (pow(sin((16.0 * PI * i) / numLines), 2) + pow(sin((14.0 * PI * i) / numLines), 2));
        float d = cos((30.0 * PI * i) / numLines) * (pow(sin((16.0 * PI * i) / numLines), 2) + pow(sin((14.0 * PI * i) / numLines), 2));
        
        ofPoint start(a, b);
        ofPoint end(c, d);
        
        ofPolyline line;
        line.addVertex(start);
        line.addVertex(end);
        lines.push_back(line);
    }
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(ofColor::black);
    
    ofPushMatrix();
    ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);
    ofScale(150, 150);
    
    float time = ofGetElapsedTimef();

    for (int i = 0; i < numLines; i++) {
        ofPolyline line = lines[i];
        vector<ofPoint> vertices = line.getVertices();
        ofPoint start = vertices[0];
        ofPoint end = vertices[1];
        
        start.x += ofMap(sin(time), -1, 1, 0, 10);
        start.y += ofMap(cos(time), 0, 1, 0, 10);
        
        ofSetColor(ofColor::fromHsb(start.angle(end), 255, 255));
        line.draw();
    }
    
    ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
