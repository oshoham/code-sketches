#ifndef _QUAD_WARPER
#define _QUAD_WARPER





#include "ofMain.h"

#define OF_ADDON_USING_OFXXMLSETTINGS
#include "ofxXmlSettings.h"




class quadWarper {

	public:

		quadWarper();
		quadWarper(int w, int h);


		int width, height;

		ofPoint srcPoints[4];
		ofPoint dstPoints[4];

		//--------------------------------------------------------
		void setup(float x, float y, float w, float h);
		void reset(float minX, float minY, float maxX, float maxY);

		float 		xCalib, yCalib, wCalib, hCalib;
		int 		pointBeingCalibrated;
		void 		mousePressed(float x, float y);
		bool 		mouseDragged(float x, float y);
		void 		mouseReleased();
		//--------------------------------------------------------

		void loadSettings(string filename_);
		void saveSettings(string filename_);


		void draw();



};

#endif
