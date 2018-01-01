#pragma once

#include "ofMain.h"

class SoundRingBuffer {
    public:
        SoundRingBuffer();
        void setup(int numFrames, int numChannels);
        void addSamples(ofSoundBuffer & inBuffer);
        float & getDelayedSample(size_t delay, int channel);
        
    protected:
        int currentFrame;
        int currentChannel;
        ofSoundBuffer samples;
};
