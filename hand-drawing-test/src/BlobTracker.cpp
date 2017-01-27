#include "BlobTracker.h"
#include "ofMain.h"

//------------------------------------------------------------
BlobTracker::BlobTracker() {
    blobCounter = 0;
}

//------------------------------------------------------------
void BlobTracker::track(vector<ofxCvBlob> blobs) {
    if (trackedBlobs.empty() && blobs.size() > 0) { // no blobs! every blob is a new blob!
        for (auto blob : blobs) {
            BlobWithId b;
            b.id = blobCounter;
            b.blob = blob;
            b.matched = false;
            trackedBlobs.push_back(b);
            blobCounter++;
        }
    } else if (trackedBlobs.size() <= blobs.size()) {
        vector<BlobWithId> currentBlobs;
        for (auto blob : blobs) {
            BlobWithId b;
            b.blob = blob;
            b.matched = false;
            currentBlobs.push_back(b);
        }
        
        // for each of the blobs we're tracking over time
        for (auto & tb : trackedBlobs) {
            float recordDistance = FLT_MAX;
            BlobWithId* closestBlob = NULL;
            
            // find the closest blob among the blobs that we've found in this frame
            for (auto & cb : currentBlobs) {
                // consider using distance() instead of squareDistance if this proves inaccurate
                float distance = tb.blob.centroid.squareDistance(cb.blob.centroid);
                if (distance < recordDistance && !cb.matched) {
                    recordDistance = distance;
                    closestBlob = &cb;
                }
            }
            // mark the closest blob as matched so that we don't accidentally match it again
            // on another iteration of this loop
            closestBlob->matched = true;
            // update the tracked blob to track the matching blob that we found in this frame
            tb.blob = closestBlob->blob;
        }
        
        // create new tracked blobs for any unmatched blobs that were found in this frame
        for (auto cb : currentBlobs) {
            if (!cb.matched) {
                BlobWithId b;
                b.id = blobCounter;
                b.blob = cb.blob;
                b.matched = false;
                trackedBlobs.push_back(b);
                blobCounter++;
            }
        }
    } else if (trackedBlobs.size() > blobs.size()) {
        vector<BlobWithId> currentBlobs;
        for (auto blob : blobs) {
            BlobWithId cb;
            cb.blob = blob;
            cb.matched = false;
            currentBlobs.push_back(cb);
        }
        
        for (auto & tb : trackedBlobs) {
            tb.matched = false;
        }
        
        // for each of the blobs found in this frame
        for (auto & cb : currentBlobs) {
            float recordDistance = FLT_MAX;
            BlobWithId* closestBlob = NULL;
            
            // find the closest blob that we've been tracking over time
            for (auto & tb : trackedBlobs) {
                // consider using distance() instead of squareDistance if this proves inaccurate
                float distance = cb.blob.centroid.squareDistance(tb.blob.centroid);
                if (distance < recordDistance && !tb.matched) {
                    recordDistance = distance;
                    closestBlob = &tb;
                }
            }
            
            if (closestBlob != NULL) {
                // mark the tracked blob as matched so that we don't try to match it again in this loop
                closestBlob->matched = true;
                // update the tracked blob to track the matching blob that we found in this frame
                closestBlob->blob = cb.blob;
                // reset the tracked blob's lifespan because we know it's still around
                closestBlob->resetLifespan();
            }
        }
        
        // decrement the lifespan of any tracked blobs that weren't matched
        // to a blob found in this frame
        for (auto & tb : trackedBlobs) {
            if (!tb.matched) {
                tb.updateLifespan();
            }
        }
        
        // remove any tracked blobs that weren't matched to a blob found in this frame
        // and that have been absent long enough for their lifespan to reach 0
        trackedBlobs.erase(std::remove_if(trackedBlobs.begin(), trackedBlobs.end(), [](BlobWithId b) { return !b.matched && b.checkLifespan(); }), trackedBlobs.end());
    }
}
