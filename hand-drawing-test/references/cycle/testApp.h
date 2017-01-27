#ifndef _TEST_APP
#define _TEST_APP

#define OF_ADDON_USING_OFXOPENCV

#include "ofMain.h"
#include "ofAddons.h"
#include "ofxOsc.h"
#include "thing.h"
#include "lo/lo.h"

#define TB_WAVE 1
#define TB_TUNING 2
#define TB_CUTOFF 3
#define TB_RESONANCE 4
#define TB_ENVMOD 5
#define TB_DECAY 6
#define TB_ACCENT 7
#define TB_VOLUME 8

#define _USE_LIVE_VIDEO		// uncomment this to use a live camera
								// otherwise, we'll use a movie file


#define LATENCY 0.06

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>

#include "quadWarper.h"

typedef std::pair<int, int> linko;

typedef std::pair<float, int> noteoff;
typedef std::pair<float, ofxCvBlob> bloboff;

class testApp : public ofSimpleApp {

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased();
        void triggerKick(void);
        int pairs(int n);
        void makeTree(void);
        ofPoint centrepoint(void);
        int centreblob(void);
        void sequenceThings(void);
        void travelThings(vector<int> *notVisited, int blob_n, float distance, int depth);
        float getOrientation(vector <ofPoint> & contour);
        float thingsdist(int a, int b);
        void playThings(void);
        void triggerOn(int note, int accent, float duration);
        void schedule_noteOff(float when, int note);
        void triggerOff(int note);
        void sendMidi(uint8_t midi_data[4]);
        void triggerControl(int control, float value);
        void doNoteOffs(void);
        void doBlobOffs(void);
        int nextLoop(void);
        float maxTime;
        float lastTime;
        vector<noteoff> noteoffs;
        vector<bloboff> blobbing;
        lo_address tb303;

        #define LOOPTIME 2.0f

        #ifdef _USE_LIVE_VIDEO
		  ofVideoGrabber 		vidGrabber;
		#else
		  ofVideoPlayer 		vidPlayer;
		#endif


        // opencv image processing
        ofxCvColorImage		    colorImg;                   // color image to process computer vision

        ofxCvGrayscaleImage 	grayImage;                  // grayscale conversion of incoming camera or video
		ofxCvGrayscaleImage 	grayBg;                     // grayscale background capture for bg subtraction
		ofxCvGrayscaleImage 	grayDiff;                   // grayscale image to hold difference of current and background
        ofxCvGrayscaleImage     grayWarped;

        ofxCvContourFinder 	contourFinder;                  // contour finder object for analyzing the image

		int 				threshold;                      // threshold for differencing
        float               scale;
		// states for controlling app
		bool                bShowVideo;
		bool				bLearnBackground;
		bool                bDiagnosticMode;
		bool                bShowFrameRate;
        bool                bDrawLines;
        bool                bKick;
        int                 kicks;
        int                 loopN;
        float               now;
        ofxOscSender sender;
        vector<linko> tree;
        vector<thing> things;

        quadWarper warper;
};

#endif
