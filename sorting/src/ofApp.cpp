#include "ofApp.h"

bool bSort( ofColor a, ofColor b){
    return a.getBrightness() > b.getBrightness();
}

//--------------------------------------------------------------
void ofApp::setup(){
    image.load("coney.jpg");
    image.resize(640, 640);
    
    remix.allocate(image.getWidth(), image.getHeight(), OF_IMAGE_COLOR);
    remix.clone(image);
    
    for (int i = 0; i < image.getWidth(); i++) {
        unsortedColumns.push_back(i);
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    if (unsortedColumns.empty()) {
        return;
    }
    
    int w = image.getWidth();
    int h = image.getHeight();
    
    int columnIndex = floor(ofRandom(unsortedColumns.size()));
    int column = unsortedColumns[columnIndex];
    unsortedColumns.erase(unsortedColumns.begin() + columnIndex);
    
    vector <ofColor> lineOfPixels;
    
    for (int i = 0; i < h; i++) {
        ofColor orig = image.getColor(column, i);
        lineOfPixels.push_back(orig);
    }
    
    ofSort(lineOfPixels, bSort);
    
    for (int i = 0; i < h; i++){
        remix.setColor(column, i, lineOfPixels[i]);
    }
    
    remix.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    remix.draw(0, 0);
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
