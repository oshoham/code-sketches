#pragma once

#include "ofMain.h"

class Hankin {
    
    public:
        Hankin() {}
        Hankin(ofVec2f a, ofVec2f v) : a(a), v(v), b(a + v), prevD(FLT_MAX), foundEnd(false) {}
    
        void findEnd(Hankin h);
        void draw();
    
        ofVec2f a;
        ofVec2f v;
    
        float prevD;
        ofVec2f end;
        ofVec2f b;
        bool foundEnd;
};
