#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    grabber.setup(ofGetWidth(), ofGetHeight());
    colorImg.allocate(grabber.getWidth(), grabber.getHeight());
    grayImage.allocate(grabber.getWidth(), grabber.getHeight());
    grayBg.allocate(grabber.getWidth(), grabber.getHeight());
    grayDiff.allocate(grabber.getWidth(), grabber.getHeight());
    threshold = 30;
    contourFinder2.setMinAreaRadius(5);
    contourFinder2.setMaxAreaRadius((grabber.getWidth() * grabber.getHeight())/4);
    contourFinder2.setThreshold(15);
    // wait for half a frame before forgetting something
    contourFinder2.getTracker().setPersistence(15);
    // an object can move up to 32 pixels per frame
    contourFinder2.getTracker().setMaximumDistance(32);
}

//--------------------------------------------------------------
void ofApp::update(){
//    kinect.update();
    grabber.update();
    
    if (grabber.isFrameNew()) {
        // Copy the data from the video player into an ofxCvColorImage
        ofPixels pixels = grabber.getPixels();
        pixels.mirror(false, true);
        colorImg.setFromPixels(pixels);
        
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
//        grayDiff.threshold(threshold);
        grayDiff.adaptiveThreshold(50);
        
        // erode the image to remove tiny specks
        grayDiff.erode();
        
        contourFinder2.findContours(grayDiff);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    ofSetColor(255);
    ofFill();
    
    // thick, curvy shapes
    for (ofPolyline polyline : contourFinder2.getPolylines()) {
        ofPolyline smoothedPolyline = polyline.getSmoothed(25, 0);
        smoothedPolyline.close();
        smoothedPolyline.simplify();
                
        if (smoothedPolyline.getVertices().size() < ofMap(ofGetMouseX(), 0, ofGetWidth(), 10, 150)) {
            continue;
        }
        
        vector<ofPoint> vertices = smoothedPolyline.getVertices();
        
        ofBeginShape();
        for (int i = 0; i < vertices.size(); i++) {
            ofVertex(vertices.at(i).x, vertices.at(i).y);
        }
        ofEndShape();
    }
    
    // lots of detail
//    for (vector<cv::Point> contour : contourFinder2.getContours()) {
//        ofBeginShape();
//        for (cv::Point point : contour) {
//            ofVertex(point.x, point.y);
//        }
//        ofEndShape();
//    }
    
    // quads
//    for(int i = 0; i < contourFinder2.size(); i++) {
//        vector<cv::Point> quad = contourFinder2.getFitQuad(i);
//        ofBeginShape();
//        for (cv::Point point : quad) {
//            ofVertex(point.x, point.y);
//        }
//        ofEndShape();
//    }
    
    // weird rectangles
//    for(int j = 0; j < contourFinder2.size(); j++) {
//        cv::RotatedRect ellipse = contourFinder2.getFitEllipse(j);
//        ofxCv::toOf(ellipse).draw();
//    }
    
    // blob tracking
//    ofxCv::RectTracker& tracker = contourFinder2.getTracker();
//    for (int k = 0; k < contourFinder2.size(); k++) {
//        int label = contourFinder2.getLabel(k);
//        if(tracker.existsPrevious(label)) {
//            const cv::Rect& previous = tracker.getPrevious(label);
//            const cv::Rect& current = tracker.getCurrent(label);
//            ofVec2f previousPosition(previous.x + previous.width / 2, previous.y + previous.height / 2);
//            ofVec2f currentPosition(current.x + current.width / 2, current.y + current.height / 2);
//            ofSeedRandom(label << 24);
//            ofSetColor(ofColor::fromHsb(ofRandom(255), 255, 255));
//            ofDrawLine(previousPosition, currentPosition);
//        }
//    }
    
    // contours with persistent colors
//    ofxCv::RectTracker& tracker = contourFinder2.getTracker();
//    for (int l = 0; l < contourFinder2.size(); l++) {
//        int label = contourFinder2.getLabel(l);
//        vector<cv::Point> contour = contourFinder2.getContour(l);
//        
//        ofPolyline polyline = contourFinder2.getPolyline(l);
//        ofPolyline smoothedPolyline = polyline.getSmoothed(25, 0);
//        smoothedPolyline.close();
//        smoothedPolyline.simplify();
//        
////        ofSeedRandom(label << 24);
////        ofSetColor(ofColor::fromHsb(ofRandom(255), 255, 255));
////        cv::Point2f center = contourFinder2.getCenter(l);
////        ofSetColor(grabber.getPixels().getColor(center.x, center.y));
//        
//        ofRectangle boundingRect = ofxCv::toOf(contourFinder2.getBoundingRect(l));
//        float r = 0.0;
//        float g = 0.0;
//        float b = 0.0;
//        int numPixels = 0;
//        std::map<int, int> colorFrequencies;
//        ofColor median;
//        int maxFrequency = 0;
//        for (int m = boundingRect.getLeft(); m < boundingRect.getRight(); m++) {
//            for (int n = boundingRect.getTop(); n < boundingRect.getBottom(); n++) {
////                if (!smoothedPolyline.inside(m, n)) {
////                    continue;
////                }
//                ofColor c = grabber.getPixels().getColor(m, n);
//                int hex = c.getHex();
//                colorFrequencies[hex] = colorFrequencies[hex] ? colorFrequencies[hex] + 1 : 1;
////                r += c.r;
////                g += c.g;
////                b += c.b;
////                numPixels++;
//                if (colorFrequencies[hex] > maxFrequency) {
//                    maxFrequency = colorFrequencies[hex];
//                    median = c;
//                }
//            }
//        }
////        ofColor average(r / numPixels, g / numPixels, b / numPixels);
//        ofSetColor(median);
//        
//        ofBeginShape();
//        for (ofPoint point : smoothedPolyline.getVertices()) {
//            ofVertex(point.x, point.y);
//        }
//        ofEndShape();
//    }
}

//--------------------------------------------------------------
void ofApp::exit(){

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
