#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    oscReceiver.setup(PORT);
    
    // broadcast
    oscSender.setup(BROADCAST_IP, PORT);
}

//--------------------------------------------------------------
void ofApp::update(){
    
    // clear the previous frame's mice positions
    remoteMicePositions.clear();
    
    // check for waiting messages
	while(oscReceiver.hasWaitingMessages()){
		// get the next message
		ofxOscMessage m;
		oscReceiver.getNextMessage(&m);
        
        // This is to ensure we're not reacting to our own messages
        if(m.getRemoteIp() != MY_IP_ADDRESS) {
            
            // example of handling a /mouse/moved message
            if(m.getAddress() == "/mouse/moved"){
                cout << m.getRemoteIp() << " mouse moved to " << m.getArgAsInt32(0) << ", " << m.getArgAsInt32(1) << endl;
                
                // Push the remote mouse location onto the vector of mice to draw
                remoteMicePositions.push_back(ofVec2f(m.getArgAsFloat(0), m.getArgAsFloat(1)));
            }
            
            // example of handling a /mouse/pressed message
            if(m.getAddress() == "/mouse/pressed"){
                cout << m.getRemoteIp() << " mouse pressed at " << m.getArgAsInt32(0) << ", " << m.getArgAsInt32(1) << endl;
                
                // REACT to the /mouse/pressed message!
            }
            
            // example of handling a /key/pressed message
            if(m.getAddress() == "/key/pressed"){
                cout << m.getRemoteIp() << " key pressed " << m.getArgAsInt32(0) << endl;
                
                // REACT to the /key/pressed message!
            }
        }
	}
}


//--------------------------------------------------------------
void ofApp::draw(){
    for (int i = 0; i < remoteMicePositions.size(); i++) {
        ofVec2f mousePos = remoteMicePositions.at(i);
        drawRemoteMouse(mousePos.x, mousePos.y);
    }
}

void ofApp::drawRemoteMouse(int x, int y) {
    ofSetColor(0,0,255);
    ofFill();
    ofCircle(x, y, 10);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    ofxOscMessage m;
    m.setAddress("/key/pressed");
    m.addIntArg(key);
    oscSender.sendMessage(m);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    ofxOscMessage m;
    m.setAddress("/mouse/moved");
    m.addIntArg(x);
    m.addIntArg(y);
    oscSender.sendMessage(m);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    ofxOscMessage m;
    m.setAddress("/mouse/pressed");
    m.addIntArg(x);
    m.addIntArg(y);
    oscSender.sendMessage(m);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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
