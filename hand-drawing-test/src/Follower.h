#pragma once

#include "ofMain.h"
#include "ofxCv.h"

class BlobFollower : public ofxCv::RectFollower {
    
    protected:
        ofColor color;
        ofPoint cur, smooth;
        ofPolyline all;
    
    public:
    
        void setup(const cv::Rect& track);
        void update(const cv::Rect& track);
        void kill();
        void draw();
};
