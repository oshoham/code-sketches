#include "quadWarper.h"


//---------------------------------------------------------
quadWarper::quadWarper()
{
	width 	    = 320;
	height 	    = 240;

	reset( 0,0,320,240);
}//---------------------------------------------------------
quadWarper::quadWarper(int w, int h)
{
	width 	    = w;
	height 	    = h;

	reset( 0,0,w,h);
}
//--------------------------------------------------------
void quadWarper::reset(float minX, float minY, float maxX, float maxY){

	dstPoints[0].x = minX;
	dstPoints[0].y = maxY;

	dstPoints[1].x = maxX;
	dstPoints[1].y = maxY;

	dstPoints[2].x = maxX;
	dstPoints[2].y = minY;

	dstPoints[3].x = minX;
	dstPoints[3].y = minY;

	for( int i = 0; i < 4; i++)
	{
        srcPoints[i].set(dstPoints[i].x,dstPoints[i].y);
	}

}
//--------------------------------------------------------
void quadWarper::setup(float x, float y, float w, float h){
	xCalib = x;
	yCalib = y;
	wCalib = w;
	hCalib = h;
	pointBeingCalibrated = -1;

	width 	    = w;
	height 	    = h;

	reset(0,0,w,h);

}

//--------------------------------------------------------
void quadWarper::mousePressed(float x, float y){

	float scalew = wCalib / (float)width;
	float scaleh = hCalib / (float)height;
	for (int i = 0; i < 4; i++){
		float xdiff = xCalib + dstPoints[i].x*scalew - x;
		float ydiff = yCalib + dstPoints[i].y*scaleh - y;
		float dist = sqrt(xdiff * xdiff + ydiff * ydiff);
		if (dist < 5){
			pointBeingCalibrated = i;
		}
	}
}
//--------------------------------------------------------
bool quadWarper::mouseDragged(float x, float y){

	float scalew = wCalib / (float)width;
	float scaleh = hCalib / (float)height;

	if (pointBeingCalibrated >= 0 && pointBeingCalibrated <= 3){
		float newx = (x - xCalib) / scalew;
		float newy = (y - yCalib) / scaleh;
		dstPoints[pointBeingCalibrated].x = newx;
		dstPoints[pointBeingCalibrated].y = newy;
		return true;
	}else
		return false;
}
//--------------------------------------------------------
void quadWarper::mouseReleased(){
	pointBeingCalibrated = -1;
}



//---------------------------------------------------------
void quadWarper::draw(){

	float scalew = wCalib / (float)width;
	float scaleh = hCalib / (float)height;


	glBegin(GL_LINE_LOOP);
		for (int i = 0; i < 4; i++){
			glVertex2f(xCalib + dstPoints[i].x*scalew, yCalib + dstPoints[i].y*scaleh);
		}
	glEnd();

	for (int i = 0; i < 4; i++){
		if (pointBeingCalibrated == i) ofFill();
		else ofNoFill();
		ofCircle(xCalib + dstPoints[i].x*scalew, yCalib + dstPoints[i].y*scaleh, 5);
	}
}



//---------------------------------------------------------
void quadWarper::loadSettings(string filename_){

	ofxXmlSettings  xml;

    if( xml.loadFile(filename_) ){
		printf("Loaded mask settings.\n");
	}else{
		printf("Unable to load tracking settings, check data/ folder\n");
		return;
	}

	char quadStr[255];

	for (int i = 0; i < 4; i++){
			sprintf(quadStr, "cv:warp:point_%i:x", i);
			dstPoints[i].x = xml.getValue(quadStr, 0.0f);
			sprintf(quadStr, "cv:warp:point_%i:y", i);
			dstPoints[i].y = xml.getValue(quadStr, 0.0f);
	}

}
//---------------------------------------------------------
void quadWarper::saveSettings(string filename_){

	ofxXmlSettings  xml;
    xml.loadFile(filename_);

	char quadStr [255];

	for (int i = 0; i < 4; i++){
		sprintf(quadStr, "cv:warp:point_%i:x", i);
		xml.setValue(quadStr, (dstPoints[i].x));
		sprintf(quadStr, "cv:warp:point_%i:y", i);
		xml.setValue(quadStr, (dstPoints[i].y));
	}
	xml.saveFile(filename_);


}
