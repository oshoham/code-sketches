#include "ofApp.h"

using namespace ofxCv;
using namespace cv;

// see https://github.com/kylemcdonald/ofxCv/blob/13f08a234fec795bb2114c7a593b74bd9f6588d7/libs/ofxCv/include/ofxCv/Tracker.h for an explanation of how the ofxCv blob tracker works

// see https://github.com/kylemcdonald/ofxCv/blob/13f08a234fec795bb2114c7a593b74bd9f6588d7/example-contours-tracking/src/ofApp.cpp for an example of how to use the ofxCv blob tracker

//--------------------------------------------------------------
void ofApp::setup(){
    bLearnBackground = false;
    
    vidGrabber.setDeviceID(0);
    vidGrabber.setVerbose(true);
    vidGrabber.initGrabber(320,240);
    
    colorImg.allocate(320,240);
    grayImage.allocate(320,240);
    grayBg.allocate(320,240);
    grayDiff.allocate(320,240);
    
    threshold = 30;
    
    contourFinder2.setMinAreaRadius(5);
    contourFinder2.setMaxAreaRadius((340*240)/4);
    contourFinder2.setThreshold(15);
    // wait for half a frame before forgetting something
    contourFinder2.getTracker().setPersistence(15);
    // an object can move up to 32 pixels per frame
    contourFinder2.getTracker().setMaximumDistance(32);
    
    tracker.setPersistence(15);
    tracker.setMaximumDistance(32);
}

//--------------------------------------------------------------
void ofApp::update(){
    // Ask the video player to update itself
    vidGrabber.update();
    
    //do we have a new frame?
    if (vidGrabber.isFrameNew()){
        
        // Copy the data from the video player into an ofxCvColorImage
        colorImg.setFromPixels(vidGrabber.getPixels());
        
        // Make a grayscale version of colorImg in grayImage
        grayImage = colorImg;
        
        // If it's time to learn the background;
        // copy the data from grayImage into grayBg
        if (bLearnBackground == true) {
            grayBg = grayImage; // Note: this is 'operator overloading'
            bLearnBackground = false; // Latch: only learn it once.
        }
        
        // Take the absolute value of the difference
        // between the background and incoming images.
        grayDiff.absDiff(grayBg, grayImage);
        
        // Perform an in-place thresholding of the difference image.
        grayDiff.threshold(threshold);
//        grayDiff.adaptiveThreshold(50);
        
        // erode the image to remove tiny specks
        grayDiff.erode();
        
        // 2nd argument is min blob area
        // 3rd argument is max blob area
        // 4th argument tells the contour finder to try to determine whether there are holes within any blob detected
//        contourFinder.findContours(grayDiff, 5, (340*240)/4, 10, false);
//        blobTracker.track(contourFinder.blobs);
        contourFinder2.findContours(grayDiff);
        tracker.track(contourFinder2.getBoundingRects());
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetHexColor(0xffffff);
//    colorImg.draw(0, 0, 320, 240);
    grayDiff.draw(0, 240, 320, 240);
    ofDrawRectangle(320, 0, 320, 240);
//    contourFinder.draw(320, 0, 320, 240);
//    ofColor c(255, 255, 255);
//    for(int i = 0; i < blobTracker.trackedBlobs.size(); i++) {
//        BlobWithId b = blobTracker.trackedBlobs.at(i);
//        ofRectangle r = b.blob.boundingRect;
//        r.x += 320; r.y += 240;
//        c.setHsb(i * 64, 255, 255);
//        ofSetColor(c);
//        ofDrawRectangle(r);
//        ofDrawBitmapString(ofToString(b.id), r.x, r.y);
//    }
    
//    contourFinder2.draw();
    for (auto polyline : contourFinder2.getPolylines()) {
        polyline.draw();
    }
//    RectTracker& tracker = contourFinder2.getTracker();
    ofColor c(255, 255, 255);
    for(int i = 0; i < contourFinder2.size(); i++) {
        ofRectangle r = toOf(contourFinder2.getBoundingRect(i));
        r.x += 320; r.y += 240;
        c.setHsb(i * 64, 255, 255);
        ofSetColor(c);
        ofDrawRectangle(r);
        int label = contourFinder2.getLabel(i);
        string msg = ofToString(label) + ":" + ofToString(tracker.getAge(label));
        ofDrawBitmapString(msg, r.x, r.y);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    bLearnBackground = true;
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
