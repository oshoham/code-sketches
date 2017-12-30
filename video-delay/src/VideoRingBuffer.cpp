#include "VideoRingBuffer.h"

// Based on code by Roy Macdonald
// reference: https://forum.openframeworks.cc/t/real-time-video-delay-port-from-processing/25822/11

//--------------------------------------------------------------
VideoRingBuffer::VideoRingBuffer() {
    currentIndex = 0;
}

//--------------------------------------------------------------
void VideoRingBuffer::setup(int numFrames) {
    frames.resize(numFrames);
    currentIndex = numFrames - 1;
}

//--------------------------------------------------------------
void VideoRingBuffer::addFrame(ofPixels & pixels) {
    currentIndex--;
    if (currentIndex < 0) {
        currentIndex = frames.size() - 1;
    }
    frames[currentIndex] = pixels;
}

//--------------------------------------------------------------
ofPixels & VideoRingBuffer::getDelayedPixels(size_t delay) {
    if (delay < frames.size()) {
        return frames[ofWrap(delay + currentIndex, 0, frames.size())];
    }
    return frames[0];
}
