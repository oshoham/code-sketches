#pragma once

#include "ofMain.h"
#include "ofxSyphon.h"
#include "VideoRingBuffer.h"
#include "SoundRingBuffer.h"

#define NUM_BUFFERS 11

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
        void audioIn(ofSoundBuffer &inBuffer);
        void audioOut(ofSoundBuffer &outBuffer);
    
        int frameRate;
        float minDelay;
        float maxDelay;
		
        ofVideoGrabber grabber;
        ofImage currentFrame;
        float bufferDurations[NUM_BUFFERS];
        int bufferFrameLengths[NUM_BUFFERS];
        vector<VideoRingBuffer> buffers;
    
        SoundRingBuffer soundDelayBuffer;
    
        ofxSyphonServer mainOutputSyphonServer;
    
        ofSoundBuffer soundBuffer;
        float audioBufferDuration;
};
