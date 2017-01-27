#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"

const int BLOB_LIFESPAN = 25;

typedef struct blobWithId {
    ofxCvBlob blob;
    int id;
    bool matched;
    int lifespan;
    
    blobWithId(): blob(ofxCvBlob()), id(0), matched(false), lifespan(BLOB_LIFESPAN){}
    
    void updateLifespan() {
        lifespan--;
    }
    
    void resetLifespan() {
        lifespan = BLOB_LIFESPAN;
    }
    
    bool checkLifespan() {
        return lifespan < 0;
    }
} blobWithId;

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
		
        bool bLearnBackground;
        ofVideoGrabber vidGrabber;
        ofxCvColorImage colorImg;
        ofxCvGrayscaleImage grayImage, grayBg, grayDiff;
        ofxCvContourFinder contourFinder;
        vector<blobWithId> trackedBlobs;
        int blobCounter;
};
