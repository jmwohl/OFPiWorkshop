#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    oscReceiver.setup(PORT);
    
    // broadcast
    oscSender.setup(BROADCAST_IP, PORT);
    
    // load a sound file from the bin/data directory
    player.loadSound("Weird Bell 1.aif");
    
    // allow the sound to play more than once
    player.setMultiPlay(true);
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
                
                // when someone moves their mouse, change the speed of the audio playback
                float xPos = m.getArgAsFloat(0);
                
                float xPercent = ofMap(xPos, 0, ofGetScreenWidth(), 0, 2);
                
                player.setSpeed(xPercent);
            }
            
            // example of handling a /mouse/pressed message
            if(m.getAddress() == "/mouse/pressed"){
                cout << m.getRemoteIp() << " mouse pressed at " << m.getArgAsInt32(0) << ", " << m.getArgAsInt32(1) << endl;
                
                // When someone clicks the mouse, play the sound
                player.play();

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
