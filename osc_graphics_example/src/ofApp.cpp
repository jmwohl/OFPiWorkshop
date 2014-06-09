#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    oscReceiver.setup(PORT);
    
    // broadcast
    oscSender.setup(BROADCAST_IP, PORT);
}

//--------------------------------------------------------------
void ofApp::update(){
    
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
                
                // Push the remote mouse location onto the map of mice to draw
                remoteMicePositions[m.getRemoteIp()] = ofVec2f(m.getArgAsFloat(0), m.getArgAsFloat(1));
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
void ofApp::draw() {
    // loop through the vector of remoteMicePositions, draw 'em.
    typedef map<string, ofVec2f>::iterator it_type;
    for(it_type iterator = remoteMicePositions.begin(); iterator != remoteMicePositions.end(); iterator++) {
        ofVec2f mousePos = iterator->second;
        drawRemoteMouse(mousePos.x, mousePos.y);
    }
}

// we separate out the actual drawing into it's own method.
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
