#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxCv.h"
#include "ofxKinect.h"
#include "ofxSecondWindow.h"
#include "ofxKinectProjectorToolkit.h"
#include "ofxGui.h"

// this must match the display resolution of your projector
#define PROJECTOR_RESOLUTION_X 1280
#define PROJECTOR_RESOLUTION_Y 800

using namespace ofxCv;
using namespace cv;

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

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
		
        ofxSecondWindow             projector;
        
        ofxPanel                    gui;
        ofColor                     blobColors[12];
        
        ofxCv::ContourFinder        contourFinder;
        ofxKinectProjectorToolkit   kpt;
        ofxKinect                   kinect;
        
        ofxCvGrayscaleImage         bgImage;
        ofxCvGrayscaleImage         grayImage;
        ofxCvGrayscaleImage         grayThreshNear;
        ofxCvGrayscaleImage         grayThreshFar;
        
        ofParameter<float>          nearThreshold;
        ofParameter<float>          farThreshold;
        ofParameter<float>          minArea;
        ofParameter<float>          maxArea;
        ofParameter<float>          threshold;
        ofParameter<float>          persistence;
        ofParameter<float>          maxDistance;
};
