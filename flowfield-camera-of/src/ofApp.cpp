#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    grabber.setup(ofGetWidth(), ofGetHeight());
    vectorField.setup(ofGetWidth(), ofGetHeight(), 4);
    
    for (int i = 0; i < 100000; i++) {
        particle p;
        p.setInitialCondition(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()), 0.0, 0.0);
        particles.push_back(p);
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    grabber.update();
    
    if (grabber.isFrameNew()) {
        ofPixels pixels = grabber.getPixels();
        pixels.mirror(false, true);
        image.setFromPixels(pixels);
        vectorField.setFromImage(image);
        vectorField.normalize();
//        vectorField.scale(3);
        vectorField.blur();
    }

    for(int i = 0; i < particles.size(); i++) {
        ofVec2f force = vectorField.getVectorInterpolated(particles[i].pos.x, particles[i].pos.y, ofGetWidth(), ofGetHeight());
        particles[i].resetForce();
        particles[i].addForce(force.x, force.y);
        particles[i].addDampingForce();
        particles[i].update();
        particles[i].bounceOffWalls();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    ofSetColor(255);
//    grabber.draw(0, 0);
//    vectorField.draw();
    ofPixels pixels = grabber.getPixels();
    pixels.mirror(false, true);
    
    for (auto & particle: particles) {
        if (particle.pos.x < 0 || particle.pos.x >= ofGetWidth() || particle.pos.y < 0 || particle.pos.y >= ofGetHeight()) {
            continue;
        }
//        ofSetColor(pixels.getColor(floor(particle.pos.x), floor(particle.pos.y)));
        particle.draw();
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
