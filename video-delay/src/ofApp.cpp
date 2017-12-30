#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    frameRate = 30;
    minDelay = 0.5;
    maxDelay = 3;
    
    grabber.setDesiredFrameRate(frameRate);
    grabber.setup(320, 240);
    ofSetFrameRate(frameRate);
    
    mainOutputSyphonServer.setName("Screen Output");
    
    buffers.resize(NUM_BUFFERS);
    for (int i = 0; i < buffers.size(); i++) {
        bufferDurations[i] = ofMap(i, 0, buffers.size(), minDelay, maxDelay);
        bufferFrameLengths[i] = frameRate * bufferDurations[i];
        VideoRingBuffer & buffer = buffers[i];
        buffer.setup(bufferFrameLengths[i]);
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    grabber.update();
    
    if (grabber.isFrameNew()) {
        ofPixels pixels = grabber.getPixels();
        pixels.mirror(false, true);
        pixels.crop((pixels.getWidth() - pixels.getHeight()) / 2, 0, pixels.getHeight(), pixels.getHeight());
        currentFrame.setFromPixels(pixels);
        
        for (VideoRingBuffer & buffer : buffers) {
            buffer.addFrame(pixels);
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    ofSetColor(255);

    if (currentFrame.isAllocated()) {
        currentFrame.draw(0,0);
    }
        
    int frameWidth = currentFrame.getWidth();
    int frameHeight = currentFrame.getHeight();
    
    int w = frameWidth;
    int h = 0;
    for (int i = 0; i < buffers.size(); i++) {
        ofTexture tex;
        ofPixels & pixels = buffers[i].getDelayedPixels(bufferFrameLengths[i] - 1);
        if (pixels.isAllocated()) {
            tex.loadData(pixels);
            tex.draw(w, h);
        }
        
        w += frameWidth;
        if (w >= ofGetWidth()) {
            w = 0;
            h += frameHeight;
        }
    }
    
    mainOutputSyphonServer.publishScreen();
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
