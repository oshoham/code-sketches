#ifndef sine_h
#define sine_h

#include "ofMain.h"

class sine {
    public:
        sine(ofPoint position, int w, float theta, float amplitude, float period, ofColor color);
    
        void update();
        void draw();
    
        float xspacing;    // Distance between each horizontal location
        int w;                // Width of entire wave
        float theta;      // Start angle at 0
        float amplitude; // Height of wave
        float period;   // How many pixels before the wave repeats
        float dx;               // Value for incrementing x
        vector<float> yvalues;  // Using an array to store height values for the wave
        
        ofPolyline line;
        ofColor color;
        ofPoint position;
};

#endif /* sine_h */
