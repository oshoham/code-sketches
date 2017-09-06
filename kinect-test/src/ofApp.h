#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxCv.h"

class ofApp : public ofBaseApp{
    
    class Blob : public ofxCv::RectFollower {
        protected:
            ofColor color;
        public:
            void setup(const cv::Rect& track);
            void update(const cv::Rect& track);
            void kill();
        };

	public:
		void setup();
		void update();
		void draw();
        void exit();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
        ofxCvColorImage colorImg;
    
        ofxCvGrayscaleImage grayImage; // grayscale depth image
        ofxCvGrayscaleImage grayThreshNear; // the near thresholded image
        ofxCvGrayscaleImage grayThreshFar; // the far thresholded image
    
        ofxCvContourFinder contourFinder;
    
        bool bThreshWithOpenCV;
        bool bDrawPointCloud;
    
        int nearThreshold;
        int farThreshold;
    
        int angle;
    
        ofVideoGrabber grabber;
        ofxCvGrayscaleImage grayBg, grayDiff;
        ofxCv::ContourFinder contourFinder2;
        int threshold;
        bool bLearnBackground;
};
