#include "Follower.h"

using namespace ofxCv;
using namespace cv;

void BlobFollower::setup(const cv::Rect& track) {
    color.setHsb(ofRandom(0, 255), 255, 255);
    cur = toOf(track).getCenter();
    smooth = cur;
}

void BlobFollower::update(const cv::Rect& track) {
    cur = toOf(track).getCenter();
    smooth.interpolate(cur, .5);
    all.addVertex(smooth);
}

void BlobFollower::kill() {
}

void BlobFollower::draw() {
    ofPushStyle();
    float size = 16;
    ofSetColor(255);
    ofNoFill();
    ofDrawCircle(cur, size);
    ofSetColor(color);
    all.draw();
    ofSetColor(255);
    ofDrawBitmapString(ofToString(label), cur);
    ofPopStyle();
}
