#pragma once

#include "ofxOpenCv.h"

const int BLOB_LIFESPAN = 25;

typedef struct BlobWithId {
    ofxCvBlob blob;
    int id;
    bool matched;
    int lifespan;
    
    BlobWithId(): blob(ofxCvBlob()), id(0), matched(false), lifespan(BLOB_LIFESPAN){}
    
    void updateLifespan() {
        lifespan--;
    }
    
    void resetLifespan() {
        lifespan = BLOB_LIFESPAN;
    }
    
    bool checkLifespan() {
        return lifespan < 0;
    }
} BlobWithId;

class BlobTracker {
    
    private:
        int blobCounter;
    
    public:
        BlobTracker();
        virtual ~BlobTracker(){};
    
        void track(vector<ofxCvBlob>);
    
        vector<BlobWithId> trackedBlobs;
    
};
