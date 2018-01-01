#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    frameRate = 30;
    minDelay = 0.1;
    maxDelay = 1;
    
    grabber.setDesiredFrameRate(frameRate);
    grabber.setup(320, 240);
    ofSetFrameRate(frameRate);
    
    mainOutputSyphonServer.setName("Screen Output");
    
//    auto devices = soundStream.getDeviceList();
//    auto devices = soundStream.getMatchingDevices("Apple Inc.: Aggregate Device");
//    if(!devices.empty()){
//        soundStream.setDevice(devices[0]);
//    }
//    soundStream.setup(2, 2, 44100, 256, 4);
    ofSoundStreamSetup(2, 2);
    soundBuffer.allocate(256, 2);
    audioBufferDuration = 256.0 / 44100.0; // ~0.005804988662
    
    soundDelayBuffer.setup(44100, 2);
    
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
void ofApp::audioIn(ofSoundBuffer &inBuffer) {
//    soundBuffer = inBuffer;
    ofSoundBuffer tone;
    tone.allocate(inBuffer.getNumFrames(), inBuffer.getNumChannels());
    tone.fillWithTone();
    soundDelayBuffer.addSamples(tone);
}

//--------------------------------------------------------------
void ofApp::audioOut(ofSoundBuffer &outBuffer) {
//    outBuffer = soundBuffer;
    int numChannels = outBuffer.getNumChannels();
    for (int i = 0; i < outBuffer.getNumFrames(); i++) {
        for (int j = 0; j < numChannels; j++) {
            outBuffer[i * numChannels + j] = soundDelayBuffer.getDelayedSample(22050 + i, j);
        }
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
