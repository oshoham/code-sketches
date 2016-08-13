#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    int paddingWidth = 25;
    int w = ofGetWidth() - paddingWidth * 2;
    float periodToAmplitudeRatio = 4.5;
    ofPoint position(paddingWidth, ofGetHeight() / 2);
    
    sineWaves = {
        // look at ratio of width / period and make sure each sine has the same ratio
        sine(position, w, 3, (w / periodToAmplitudeRatio), w, ofColor::fromHex(0xF38BB2)),
        sine(position, w, 2.85, ((w / 2.0) / periodToAmplitudeRatio), w / 2.0, ofColor::fromHex(0xBAF3AB)),
        sine(position, w, 2.7, ((w / 3.0) / periodToAmplitudeRatio), w / 3.0, ofColor::fromHex(0xFABD8F)),
        sine(position, w, 2.55, ((w / 4.0) / periodToAmplitudeRatio), w / 4.0, ofColor::fromHex(0xFFD2DE)),
        sine(position, w, 2.4, ((w / 5.0) / periodToAmplitudeRatio), w / 5.0, ofColor::fromHex(0xD7746C)),
        sine(position, w, 2.25, ((w / 6.0) / periodToAmplitudeRatio), w / 6.0, ofColor::fromHex(0x7385B0)),
        sine(position, w, 2.1, ((w / 7.0) / periodToAmplitudeRatio), w / 7.0, ofColor::fromHex(0xF4E6A3)),
        sine(position, w, 1.95, ((w / 8.0) / periodToAmplitudeRatio), w / 8.0, ofColor::fromHex(0xDDA87F)),
        sine(position, w, 1.8, ((w / 9.0) / periodToAmplitudeRatio), w / 9.0, ofColor::fromHex(0xBA7593)),
        sine(position, w, 1.65, ((w / 10.0) / periodToAmplitudeRatio), w / 10.0, ofColor::fromHex(0xFDFDF7)),
        sine(position, w, 1.5, ((w / 11.0) / periodToAmplitudeRatio), w / 11.0, ofColor::fromHex(0x61D3D1)),
        sine(position, w, 1.35, ((w / 12.0) / periodToAmplitudeRatio), w / 12.0, ofColor::fromHex(0xD7746C))
    };
}

//--------------------------------------------------------------
void ofApp::update(){
    for (auto & s : sineWaves) {
//        s.theta -= 0.005;
        s.update();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    
//    ofPushMatrix();
//    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
//    ofRotate(90);
//    ofTranslate(-(ofGetWidth() / 2), -(ofGetHeight() / 2));
//    ofScale(0.5, 0.5, 1);
//    ofTranslate((ofGetWidth() / 2), (ofGetHeight() / 2));
    
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    for (auto & s : sineWaves) {
        s.draw();
    }
    ofDisableBlendMode();
    
//    ofPopMatrix();
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
