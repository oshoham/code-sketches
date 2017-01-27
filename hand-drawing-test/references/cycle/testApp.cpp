/*  cycle - acid sketching
    Copyright (C) 2009 alex@slab.org

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "testApp.h"
#include <boost/lambda/lambda.hpp>

//--------------------------------------------------------------
void testApp::setup(){
    ofSetFullscreen(true);
    sender.setup("localhost", 7770);
    tb303 = lo_address_new("localhost", "11869");
    // allocate memory for cv images
    colorImg.allocate(320,240);
    grayImage.allocate(320,240);
    grayBg.allocate(320,240);
    grayDiff.allocate(320,240);
    grayWarped.allocate(320,240);

    warper.setup(0,0,320,240);
    //img.allocate(320,240);

    bDrawLines          = false;
    bShowVideo          = true;
    bLearnBackground    = true;
    bShowFrameRate      = true;
    bDiagnosticMode     = true;
    threshold           = 80;
    bKick               = false;
    kicks               = 0;
    loopN               = 0;
#ifdef _USE_LIVE_VIDEO
  vidGrabber.setVerbose(true);
  vidGrabber.initGrabber(320,240);
#else
  vidPlayer.loadMovie("fingers.mov");
  vidPlayer.setLoopState(OF_LOOP_NORMAL);
  vidPlayer.play();
#endif

//  ofSetFrameRate(1);
  ofSetVerticalSync(true);

  lastTime = 0;

}

//--------------------------------------------------------------
void testApp::update(){
  lastTime = now;
  now = ofGetElapsedTimef();
  ofBackground(0,0,0);

  bool bNewFrame = false;

  //------------------------------ video capture
#ifdef _USE_LIVE_VIDEO
  vidGrabber.grabFrame();
  bNewFrame = vidGrabber.isFrameNew();
#else
  vidPlayer.idleMovie();
  bNewFrame = vidPlayer.isFrameNew();
#endif

  //------------------------------ image processing
  if (bNewFrame) {
#ifdef _USE_LIVE_VIDEO
    colorImg.setFromPixels(vidGrabber.getPixels(), 320,240);
#else
    colorImg.setFromPixels(vidPlayer.getPixels(), 320,240);
#endif

    if (nextLoop()) {
        // copy color to grayscale
        grayImage = colorImg;

        grayWarped.warpIntoMe( grayImage,  warper.dstPoints, warper.srcPoints);

        // capture background if set
        if (bLearnBackground == true){
        grayBg = grayWarped;		// the = sign copys the pixels from grayImage into grayBg (operator overloading)
        bLearnBackground = false;
        }

        // bacground subtraction to get difference between background and current image
        grayWarped.absDiff(grayBg, grayWarped);
        //grayDiff = grayImage - grayBg;

        // apply threshold
        grayWarped.threshold(threshold);

        // find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
        // also, find holes is set to true so we will get interior contours as well....
        contourFinder.findContours(grayWarped, 20, (340*240)/3, 10, false);	// find holes
        makeTree();
        things.resize(contourFinder.nBlobs);
        for (int i = 0; i < contourFinder.nBlobs; i++) {
            ofxCvBlob blob = contourFinder.blobs[i];
            things[i].centroid = blob.centroid;
            things[i].area = blob.area;
            things[i].angle = getOrientation(blob.pts);
            //newThing->regularity = blob.length / blob.area;
            things[i].regularity = (blob.length * 0.282) / sqrt(blob.area);
            things[i].time = 0;
        }
        sequenceThings();
        //cout << "sequenced " + ofToString((int) things.size()) + "\n";
    }
  }
  playThings();
}

int testApp::nextLoop(void) {
    int result = false;
    int loop = (int) (now / LOOPTIME);
    if (loopN < loop) {
        loopN = loop;
        result = true;
    }
    return(result);
}

void testApp::playThings(void) {
    for(int i = 0; i < things.size(); i++) {
        float thingTime = things[i].time + LATENCY;
        if (thingTime > lastTime && thingTime <= now) {
            float duration = 0.2;
            int note = 80 - sqrt(things[i].area);
            if (note < 30) {
                note = 30;
            }
            //cout << ofToString(note) + "\n";
            float envmod = (things[i].regularity - 1.0f) / 5.0f;
            if (envmod > 1) {
                envmod = 1;
            }

            float resonance = things[i].angle / PI;

            triggerControl(TB_ENVMOD, envmod);
            triggerControl(TB_RESONANCE, resonance);
            triggerOn(note, 0, duration);
            blobbing.push_back(bloboff(now + duration, contourFinder.blobs[i]));
        }
    }
    doNoteOffs();
    doBlobOffs();

    if (bKick) {
        int kickNo = ((now - LATENCY) / (LOOPTIME / 4));
        if (kicks < kickNo) {
            triggerKick();
            kicks = kickNo;
        }
    }
}

//--------------------------------------------------------------

void testApp::travelThings(vector<int> *notVisited, int blob_n, float distance, int depth) {
    int exhausted = 0;
    if (depth > 20) {
        cout << "bugger\n";
        //return;
    }
    //cout << "blob_n: " + ofToString(blob_n) + "depth: " + ofToString(depth) + " not visited: " + ofToString((int) notVisited->size()) + "\n";
    if (blob_n < 0) {
        return;
    }
    things[blob_n].time = distance;

    for (int k = 0; k < notVisited->size(); ++k) {
        if ((*notVisited)[k] == blob_n) {
            (*notVisited)[k] = notVisited->back();
            notVisited->pop_back();
            break;
        }
    }

    int retry = 1;
    while (retry) {
        retry = 0;
        for (int i = 0; i < tree.size(); ++i) {
            int a = tree[i].first;
            int b = tree[i].second;
            int other;

            if ((a == blob_n) || (b == blob_n)) {
                other = ((a == blob_n) ? b : a);
                int ok = 0;
                for (int j = 0; j < notVisited->size(); ++j) {
                    if ((*notVisited)[j] == other) {
                        ok = 1;
                        break;
                    }
                }
                if (ok) {
                    travelThings(notVisited, other, distance + thingsdist(other, blob_n), depth+1);
                    retry = 1;
                    break;
                }
            }
        }
    }
}

float testApp::thingsdist(int a, int b) {
    float diffX = things[a].centroid.x - things[b].centroid.x;
    float diffY = things[a].centroid.y - things[b].centroid.y;
    return(sqrt(abs(diffX * diffX) + abs(diffY * diffY)));
}


void testApp::sequenceThings() {
    vector<int> notVisited;
    if (things.size() > 1) {
        //cout << "aha\n";
    }
    for(int i = 0; i < things.size(); ++i) {
        notVisited.push_back(i);
    }
    travelThings(&notVisited, centreblob(), 0, 0);
    maxTime = 0;
    for(int i = 0; i < things.size(); ++i) {
        maxTime = max(maxTime, things[i].time);
    }
    maxTime *= ((float) (things.size()) / (float) (things.size() - 1));

    float loopStart = now - fmodf(now, LOOPTIME);
    for(int i = 0; i < things.size(); ++i) {
        float timepc = maxTime == 0 ? 0 : (things[i].time / maxTime);
        things[i].time = (timepc * LOOPTIME) + loopStart;
    }

    if (notVisited.size() > 0) {
        cout << "daft " + ofToString((int) notVisited.size()) + "\n";
    }
}

void testApp::draw(){
    scale = 1; //(float)ofGetWidth() / 320.0f;
    ofSetColor(255,255,255);
    if (bShowVideo) {
//        grayWarped.draw(0,0, 320.0f * scale, 240.0f * scale);
        colorImg.draw(0,0);
        //warper.draw();

    }
    if (bDrawLines) {
        for (int i = 0; i < things.size(); ++i) {
            ofNoFill();
            ofSetColor(255,0,0);
            string s = ofToString(things[i].regularity, 2) + " / " + ofToString(things[i].time, 2);
            ofDrawBitmapString(s, things[i].centroid.x, things[i].centroid.y);
        }
    }

    for (int i = 0; i < tree.size(); ++i) {
        ofxCvBlob a = contourFinder.blobs[tree[i].first];
        ofxCvBlob b = contourFinder.blobs[tree[i].second];

        if (bDrawLines) {
            ofSetColor(255, 0, 0);
            ofLine(a.centroid.x * scale, a.centroid.y * scale, b.centroid.x * scale, b.centroid.y * scale);
        }

        thing thing1, thing2;
        if (things[tree[i].first].time > things[tree[i].second].time) {
          thing1 = things[tree[i].first];
          thing2 = things[tree[i].second];
        }
        else {
          thing1 = things[tree[i].second];
          thing2 = things[tree[i].first];
        }

        float start = thing2.time;
        float stop = thing1.time;
        if ((now > start) && (now < stop)) {
            float diff = stop - start;
            float p = now - start;
            float pc = 1 - (p / diff);
            float x = thing1.centroid.x + ((thing2.centroid.x - thing1.centroid.x) * pc);
            float y = thing1.centroid.y + ((thing2.centroid.y - thing1.centroid.y) * pc);
            ofSetColor(200, 32, 32);
            ofFill();
            ofCircle(x * scale, y * scale, 7);
        }
    }

    for (int i = 0; i < blobbing.size(); ++i) {
        ofxCvBlob blob = blobbing[i].second;

        ofFill();
        ofSetColor(255,0,0);
        ofBeginShape();
        for (int i = 0; i < blob.nPts; i++){
            ofVertex(blob.pts[i].x * scale, blob.pts[i].y * scale);
        }
        ofEndShape(true);
    }

    if (bDrawLines) {
        int i = centreblob();
        if (i >= 0) {
            ofSetColor(0,0,255);
            ofNoFill();
            ofCircle(contourFinder.blobs[i].centroid.x * scale, contourFinder.blobs[i].centroid.y * scale, 10);
        }
    }
}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){

  switch (key){
  case ' ':
    bLearnBackground = true;
    break;
  case '+':
    threshold ++;
    if (threshold > 255) threshold = 255;
    break;
  case '-':
    threshold --;
    if (threshold < 0) threshold = 0;
    break;
  case OF_KEY_RETURN: bDiagnosticMode = !bDiagnosticMode; break;
  case 'X':
  case 'x': ofToggleFullscreen(); break;
  case 'f':
  case 'F':
    bShowFrameRate = !bShowFrameRate; break;
  case 'D':
  case 'd':
    bDrawLines = !bDrawLines; break;
    case 'k':
    case 'K':
    bKick = !bKick; break;
  case 'v': case 'V':
    bShowVideo = !bShowVideo;
  case 's': warper.saveSettings("warper.xml"); break;
  case 'l': warper.loadSettings("warper.xml"); break;
  }
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    warper.mouseDragged(x,y);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    triggerOn(60, 1, 0.2);
    warper.mousePressed(x,y);
}

//--------------------------------------------------------------
void testApp::mouseReleased(){
    warper.mouseReleased();
}

ofPoint testApp::centrepoint(void) {
    if (contourFinder.nBlobs == 0) {
        return(NULL);
    }
    float x = contourFinder.blobs[0].centroid.x;
    float y = contourFinder.blobs[0].centroid.y;

    if (contourFinder.nBlobs == 1) {
        return(ofPoint(x, y));
    }
    for (int i = 1; i < contourFinder.nBlobs; i++) {
        x += contourFinder.blobs[i].centroid.x;
        y += contourFinder.blobs[i].centroid.y;
    }
    x /= contourFinder.nBlobs;
    y /= contourFinder.nBlobs;


    return(ofPoint(x,y));
}

int testApp::centreblob(void) {
    if (contourFinder.nBlobs == 0) {
        return(-1);
    }

    ofPoint cp = centrepoint();

    if (contourFinder.nBlobs == 1) {
        return(0);
    }

    float diffX = contourFinder.blobs[0].centroid.x - cp.x;
    float diffY = contourFinder.blobs[0].centroid.y - cp.y;
    float distance = sqrt(abs(diffX * diffX) + abs(diffY * diffY));
    int result = 0;

    for(int i = 1; i < contourFinder.nBlobs; i++) {
        diffX = contourFinder.blobs[i].centroid.x - cp.x;
        diffY = contourFinder.blobs[i].centroid.y - cp.y;
        float newDistance = sqrt(abs(diffX * diffX) + abs(diffY * diffY));
        if (newDistance < distance) {
            distance = newDistance;
            result = i;
        }
    }

    return(result);
}

void testApp::makeTree(void) {
    using namespace boost;
    typedef adjacency_list < vecS, vecS, undirectedS,
        no_property, property < edge_weight_t, int > > Graph;
    typedef graph_traits < Graph >::edge_descriptor Edge;
    typedef graph_traits < Graph >::vertex_descriptor Vertex;

    int num_nodes = contourFinder.nBlobs;

    if (num_nodes < 2) {
        tree.resize(0);
        return;
    }

    int edges_n = pairs(num_nodes);
    linko edge_array[edges_n];
    int weights[edges_n];
    int j = 0;

    for (int from = 0; from < (num_nodes - 1); ++from) {
        for (int to = from + 1; to < num_nodes; ++to) {
            edge_array[j] = linko(from, to);
            ofxCvBlob fromBlob = contourFinder.blobs[from];
            ofxCvBlob toBlob = contourFinder.blobs[to];
            float diffX = fromBlob.centroid.x - toBlob.centroid.x;
            float diffY = fromBlob.centroid.y - toBlob.centroid.y;
            if (j >= edges_n) {
                cout << "oh dear\n";
            }
            weights[j] = (int) (10000 * sqrt(abs(diffX * diffX) + abs(diffY * diffY)));
            j++;
        }
    }

//#if defined(BOOST_MSVC) && BOOST_MSVC <= 1300
//  Graph g(num_nodes);
//  property_map<Graph, edge_weight_t>::type weightmap = get(edge_weight, g);
//  for (std::size_t j = 0; j < num_edges; ++j) {
//    Edge e; bool inserted;
//    tie(e, inserted) = add_edge(edge_array[j].first, edge_array[j].second, g);
//    weightmap[e] = weights[j];
//  }
//#else
  Graph g(edge_array, edge_array + edges_n, weights, num_nodes);
//#endif
  property_map < Graph, edge_weight_t >::type weight = get(edge_weight, g);
  std::vector < Edge > spanning_tree;

  kruskal_minimum_spanning_tree(g, std::back_inserter(spanning_tree));

  tree.resize(0);
  for (std::vector < Edge >::iterator ei = spanning_tree.begin();
       ei != spanning_tree.end(); ++ei) {
    int from = source(*ei, g);
    int to =  target(*ei, g);
    linko *foo = new linko();
    foo->first = from;
    foo->second = to;
    tree.push_back(*foo);
  }
}

void testApp::triggerKick(void) {
  ofxOscMessage m;
  m.setAddress( "/trigger" );

  m.addStringArg("909/BT0A0A7.WAV"); // sample
  //m.addStringArg("jvbass/000_01.wav");
  m.addFloatArg(1); // speed
  m.addFloatArg(0); // shape
  m.addFloatArg(0); // pan
  m.addFloatArg(0); // pan_to
  m.addFloatArg(1); // volume
  m.addStringArg("none"); // envelope_name
  m.addFloatArg(0); // anafeel_strength
  m.addFloatArg(0); // anafeel_frequency
  m.addFloatArg(0); // accellerate
  m.addStringArg(""); // vowel
  m.addStringArg("equal"); // scale
  m.addFloatArg(1); // loops
  m.addFloatArg(0); // duration
  m.addFloatArg(0); // delay
  m.addFloatArg(0); // delay2
  m.addFloatArg(0); // cutoff
  m.addFloatArg(0); // resonance
  sender.sendMessage( m );
}

void testApp::triggerOn(int note, int accent, float duration) {
    uint8_t midi_data[4] = {0, 144, (uint8_t) note, accent ? 127 : 60};
    sendMidi(midi_data);
    schedule_noteOff(now + duration, note);
}

void testApp::schedule_noteOff(float when, int note) {
    for (int i = 0; i < noteoffs.size(); ++i) {
        if (noteoffs[i].second == note) {
            noteoffs[i] = noteoffs.back();
            noteoffs.pop_back();
            break;
        }
    }
    noteoffs.push_back(noteoff(when, note));
}

void testApp::doNoteOffs(void) {
    for (int i = 0; i < noteoffs.size(); ++i) {
        if (noteoffs[i].first < now) {
            triggerOff(noteoffs[i].second);
            noteoffs[i] = noteoffs.back();
            noteoffs.pop_back();
            i--;
        }
    }
}

void testApp::doBlobOffs(void) {
    for (int i = 0; i < blobbing.size(); ++i) {
        if (blobbing[i].first < now) {
            blobbing[i] = blobbing.back();
            blobbing.pop_back();
            i--;
        }
    }
}

void testApp::triggerOff(int note) {
    uint8_t midi_data[4] = {0, 128, (uint8_t) note, 0};
    sendMidi(midi_data);
}

void testApp::sendMidi(uint8_t midi_data[4]) {
    lo_send(tb303, "/dssi/nekobee/nekobee/chan00/midi", "m", midi_data);
}

void testApp::triggerControl(int control, float value) {
    lo_send(tb303, "/dssi/nekobee/nekobee/chan00/control", "if", control, value);
}

int testApp::pairs( int n )
{
    int p = 0;

    while ( n > 1) {
        p += n - 1;
        n--;
    }
    return p;
}

float testApp::getOrientation( vector <ofPoint> & contour )
{
    CvMoments* myMoments = (CvMoments*)malloc( sizeof(CvMoments) );

    // Allocate storage
    CvMemStorage*   storage = cvCreateMemStorage(0);
    CvSeq* seq = cvCreateSeq( CV_SEQ_POLYGON, sizeof(CvContour),sizeof(CvPoint), storage );


    for( int i = 0; i < contour.size(); i++)
    {
        CvPoint pt = cvPoint(contour[i].x,contour[i].y);
        cvSeqPush( seq, &pt );
    }

    cvMoments( seq, myMoments );

    double cm20 = cvGetCentralMoment(myMoments, 2, 0);
    double cm02 = cvGetCentralMoment(myMoments, 0, 2);
    double cm11 = cvGetCentralMoment(myMoments, 1, 1);

    if (cm11 == 0.0f) cm11 = 0.00001f;
    float d = (cm20 - cm02);
    float b = d/cm11;
    float quadratic = ((-1.0f*b) + sqrtf(b*b + 4.0f))/2.0f;
    float theta = atanf(quadratic);

    if (((d < 0) && (quadratic < 1.0f)) ||
        ((d > 0) && (quadratic > 1.0f))) { theta += HALF_PI;}

    // Free the storage memory.
	// Warning: do this inside this function otherwise you get a strange memory leak
	if (storage != NULL) 	{ cvReleaseMemStorage(&storage);}

    free( myMoments);

    return theta;
}
