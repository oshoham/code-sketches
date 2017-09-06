#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    hankinAngle = 75;
    hankinDelta = 10;
    
    int inc = 100;
    for (int x = 0; x < ofGetWidth(); x += inc) {
        for (int y = 0; y < ofGetHeight(); y += inc) {
            MyPolygon poly;
            poly.addVertex(x, y);
            poly.addVertex(x + inc, y);
            poly.addVertex(x + inc, y + inc);
            poly.addVertex(x, y + inc);
            poly.close();
            polygons.push_back(poly);
        }
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    hankinAngle = ofMap(sin(ofGetElapsedTimef() * 0.5), -1, 1, 0, 90);
    hankinDelta = ofMap(sin(ofGetElapsedTimef()), -1, 1, 0, 25);
    
    for (auto & poly : polygons) {
        poly.setHankinValues(hankinAngle, hankinDelta);
        poly.hankin();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    for (auto & poly : polygons) {
        poly.draw();
    }
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
