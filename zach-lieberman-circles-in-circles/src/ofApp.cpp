#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

}

//--------------------------------------------------------------
void ofApp::update(){

}

ofPolyline drawCircle(float x, float y, float r, int num, float startAngle){
    
    ofPolyline temp;
    for (int i = 0; i < num; i++){
        float angle = ofMap(i, 0, num, 0, TWO_PI) + startAngle;
        ofPoint pt(x + cos(angle)*r, y + sin(angle)*r);
        temp.addVertex(pt);
        
    }
    return temp;
}

//--------------------------------------------------------------
void ofApp::draw(){
    vector < ofxPolylines > linesToTry;
    
    
    float time = ofGetElapsedTimef();
    
    
    
    ofSeedRandom(mouseX);
    
    for (int i = 0; i < 100; i++){
        
        float pct = 0.5 + 0.5 * sin(time/2.0);
        
        float pctMap = ofMap(i,0, 100-1, 0, 1);
        float angle = ofRandom(0, TWO_PI);
        pctMap = powf(pctMap, 0.2);
        ofPoint targetA = ofPoint(320,320) - ofPoint(cos(angle),sin(angle)) * 50;
        ofPoint targetB = ofPoint(320,320) + ofPoint(cos(angle),sin(angle)) * 50;
        ofPoint pos = targetA + pct * (targetB - targetA);
        pos.x += ofSignedNoise(time/3.0, i * 100, 0) * 100 * pct;
        pos.y += ofSignedNoise(time/3.0, i * 100, 10000) * 100 * pct;
        
        ofxPolylines t;
        
        t.push_back(drawCircle(pos.x, pos.y, 300- i*2, 100,  ofRandom(0, TWO_PI)));
        
        linesToTry.push_back(t);
    }
    
    
    
    
    ofxPolylines solution;
    solution.clear();
    
    for (int i = 0; i < linesToTry[0].size(); i++){
        solution.push_back(linesToTry[0][i]);
    }
    
    
    for (int i = 1; i < linesToTry.size(); i++){
        
        
        
        clipper.clear();
        for (int j = 0; j < solution.size(); j++){
            clipper.addPolyline(solution[j], OFX_CLIPPER_SUBJECT);
        }
        
        for (int j = 0; j < linesToTry[i].size(); j++){
            clipper.addPolyline(linesToTry[i][j], OFX_CLIPPER_CLIP);
        }
        
        solution.clear();
        
        clipper.clip(OFX_CLIPPER_INTERSECTION ,
                     solution,
                     OF_POLY_WINDING_ODD,
                     OF_POLY_WINDING_ODD);
        
        for (int j = 0; j < solution.size(); j++){
            solution[j].draw();
        }
        //
        //            vector < ofPolyline > holes;
        //
        //
        //            mesh.triangulate(solution[j], holes, 28, -1);
        //
        //            ofMesh temp;
        //
        //            temp.setMode(OF_PRIMITIVE_TRIANGLES);
        //
        //            temp.addVertices(mesh.outputPts);
        //
        //
        //            for (int i = 0;  i < mesh.triangles.size(); i++){
        //                temp.addIndex(mesh.triangles[i].index[0]);
        //                temp.addIndex(mesh.triangles[i].index[1]);
        //                temp.addIndex(mesh.triangles[i].index[2]);
        //            }
        //
        //            ofSetColor(255,0,i * 50, 255);
        //            temp.draw();
        //
        //            ofSetColor(255);
        //            solution[j].draw();
    }
    
    
    for (int i = 0; i < linesToTry[0].size(); i++){
        linesToTry[0][i].setClosed(true);
        linesToTry[0][i].draw();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
