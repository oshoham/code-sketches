#include "SoundRingBuffer.h"

//--------------------------------------------------------------
SoundRingBuffer::SoundRingBuffer() {
    currentFrame = 0;
    currentChannel = 0;
}

//--------------------------------------------------------------
void SoundRingBuffer::setup(int numFrames, int numChannels) {
    samples.allocate(numFrames, numChannels);
    currentFrame = 0;
    currentChannel = 0;
}

//--------------------------------------------------------------
void SoundRingBuffer::addSamples(ofSoundBuffer & inBuffer) {
    int numFrames = samples.getNumFrames();
    int numChannels = samples.getNumChannels();
    for (int i = 0; i < inBuffer.size(); i++) {
        if (currentChannel >= numChannels) {
            currentFrame = ofWrap(currentFrame + 1, 0, numFrames);
            currentChannel = 0;
        } else {
            currentChannel++;
        }
        samples[currentFrame * numChannels + currentChannel] = inBuffer[i];
    }
}

//--------------------------------------------------------------
float & SoundRingBuffer::getDelayedSample(size_t delay, int channel) {
    if (delay < samples.getNumFrames()) {
        return samples.getSample(ofWrap(currentFrame - delay, 0, samples.getNumFrames()), channel);
    }
    return samples.getSample(0, channel);
}
