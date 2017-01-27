#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    bLearnBackground = false;
    blobCounter = 0;
    
    vidGrabber.setDeviceID(1);
    vidGrabber.setVerbose(true);
    vidGrabber.initGrabber(320,240);
    
    colorImg.allocate(320,240);
    grayImage.allocate(320,240);
    grayBg.allocate(320,240);
    grayDiff.allocate(320,240);
}

//--------------------------------------------------------------
void ofApp::update(){
    vidGrabber.update();
    //do we have a new frame?
    if (vidGrabber.isFrameNew()){
        colorImg.setFromPixels(vidGrabber.getPixels());
        grayImage = colorImg; // convert our color image to a grayscale image
        if (bLearnBackground == true) {
            grayBg = grayImage; // update the background image
            bLearnBackground = false;
        }
        grayDiff.absDiff(grayBg, grayImage);
        grayDiff.threshold(30);
        // 2nd argument is min blob area
        // 3rd argument is max blob area
        // 4th argument tells the contour finder to try to determine whether there are holes within any blob detected
        contourFinder.findContours(grayDiff, 5, (340*240)/4, 10, false);
        
        if (trackedBlobs.empty() && contourFinder.nBlobs > 0) { // no blobs! every blob is a new blob!
            for (auto blob : contourFinder.blobs) {
                blobWithId b;
                b.id = blobCounter;
                b.blob = blob;
                b.matched = false;
                trackedBlobs.push_back(b);
                blobCounter++;
            }
        } else if (trackedBlobs.size() <= contourFinder.nBlobs) {
            vector<blobWithId> currentBlobs;
            for (auto blob : contourFinder.blobs) {
                blobWithId b;
                b.blob = blob;
                b.matched = false;
                currentBlobs.push_back(b);
            }
            
            // for each of the blobs we're tracking over time
            for (auto & tb : trackedBlobs) {
                float recordDistance = FLT_MAX;
                blobWithId* closestBlob = NULL;
                
                // find the closest blob among the blobs that we've found in this frame
                for (auto & cb : currentBlobs) {
                    // consider using distance() instead of squareDistance if this proves inaccurate
                    float distance = tb.blob.centroid.squareDistance(cb.blob.centroid);
                    if (distance < recordDistance && !cb.matched) {
                        recordDistance = distance;
                        closestBlob = &cb;
                    }
                }
                // mark the closest blob as matched so that we don't accidentally match it again
                // on another iteration of this loop
                closestBlob->matched = true;
                tb.blob = closestBlob->blob;
            }
            
            for (auto cb : currentBlobs) {
                if (!cb.matched) {
                    blobWithId b;
                    b.id = blobCounter;
                    b.blob = cb.blob;
                    b.matched = false;
                    trackedBlobs.push_back(b);
                    blobCounter++;
                }
            }
        } else if (trackedBlobs.size() > contourFinder.nBlobs) {
            vector<blobWithId> currentBlobs;
            for (auto blob : contourFinder.blobs) {
                blobWithId cb;
                cb.blob = blob;
                cb.matched = false;
                currentBlobs.push_back(cb);
            }
            
            for (auto & tb : trackedBlobs) {
                tb.matched = false;
            }
            
            for (auto & cb : currentBlobs) {
                float recordDistance = FLT_MAX;
                blobWithId* closestBlob = NULL;

                for (auto & tb : trackedBlobs) {
                    // consider using distance() instead of squareDistance if this proves inaccurate
                    float distance = cb.blob.centroid.squareDistance(tb.blob.centroid);
                    if (distance < recordDistance && !tb.matched) {
                        recordDistance = distance;
                        closestBlob = &tb;
                    }
                }
                if (closestBlob != NULL) {
                    closestBlob->matched = true;
                    closestBlob->blob = cb.blob;
                    closestBlob->resetLifespan();
                }
            }
            
            for (auto & tb : trackedBlobs) {
                if (!tb.matched) {
                    tb.updateLifespan();
                }
            }
            
            trackedBlobs.erase(std::remove_if(trackedBlobs.begin(), trackedBlobs.end(), [](blobWithId b) { return !b.matched && b.checkLifespan(); }), trackedBlobs.end());
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetHexColor(0xffffff);
    colorImg.draw(0, 0, 320, 240);
    grayDiff.draw(0, 240, 320, 240);
    ofDrawRectangle(320, 0, 320, 240);
    contourFinder.draw(320, 0, 320, 240);
    ofColor c(255, 255, 255);
    for(int i = 0; i < trackedBlobs.size(); i++) {
        blobWithId b = trackedBlobs.at(i);
        ofRectangle r = b.blob.boundingRect;
        r.x += 320; r.y += 240;
        c.setHsb(i * 64, 255, 255);
        ofSetColor(c);
        ofDrawRectangle(r);
        ofDrawBitmapString(ofToString(b.id), r.x, r.y);
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
