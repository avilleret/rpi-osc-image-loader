#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  ofSetLogLevel(OF_LOG_VERBOSE);
  ofHideCursor();
  dir.allowExt("png");
  dir.allowExt("jpg");
  dir.allowExt("gif");
#ifdef TARGET_OPENGLES
  dir.listDir("/home/pi/media/");
#else
  dir.listDir("/media/antoine/longuevue/media/");
#endif
  dir.sort(); // in linux the file system doesn't return file lists ordered in alphabetical order

  if (dir.size()) image.load(dir.getPath(0));

  /*
  //allocate the vector to have as many ofImages as files
  if( dir.size() ){
    images.assign(dir.size(), ofImage());
  }
  */

  // you can now iterate through the files and load them into the ofImage vector
  for(int i = 0; i < (int)dir.size(); i++){
    ofLogNotice("setup") << "Loading image " << i << " " << dir.getName(i);
    // bool res = images[i].load(dir.getPath(i));
    map[dir.getName(i)] = i;
    // else ofLogError("setup") << "can't load image " << dir.getName(i);
  }
  // ofLogNotice("setup") << images.size() << " images loaded";

  receiver.setup(9000);
}

//--------------------------------------------------------------
void ofApp::update(){
    while(receiver.hasWaitingMessages()){
        ofxOscMessage m;
        receiver.getNextMessage(m);
        if(m.getAddress() == "/img"){
            if (m.getNumArgs() > 0){
                switch (m.getArgType(0)){
                 case OFXOSC_TYPE_INT32:
                 case OFXOSC_TYPE_INT64:
                 case OFXOSC_TYPE_FLOAT:
                 case OFXOSC_TYPE_DOUBLE:
                    currentImage = m.getArgAsInt(0);
                    currentImage %= dir.size();
                    break;
                case OFXOSC_TYPE_STRING:
                case OFXOSC_TYPE_SYMBOL:
                    try {
                      currentImage = map.at(m.getArgAsString(0));
                      ofLogVerbose("update") << "currentImage " << currentImage << " " << m.getArgAsString(0);
                    } catch (std::exception e){
                      ofLogError(__func__) << "Can't find " << m.getArgAsString(0) << "in current image list.";
                      ofLogError(__func__) << e.what();
                    }
                    break;
                default:
                    ofLogError(__func__) << "Wrong OSC argument type (need int or string)";
            }

            } else {
                ofLogError(__func__) << "you should send at least one argument (int or string)";
            }

        } else if ( m.getAddress() == "/next") currentImage = (currentImage+1) % dir.size();
        else if ( m.getAddress() == "/prev") currentImage = (currentImage-1) % dir.size();
        if (lastImage != currentImage){
          image.load(dir.getPath(currentImage));
          lastImage = currentImage;
        }
        ofLogVerbose("update") << "currentImage " << currentImage << " " << dir.getPath(currentImage);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofClear(ofColor::black);
    ofSetColor(ofColor::white);
    if (image.isAllocated()) image.draw(0,0,ofGetWidth(),ofGetHeight());
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

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
