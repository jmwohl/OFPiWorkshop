#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    oscReceiver.setup(PORT);
    
    // broadcast
    oscSender.setup(BROADCAST_IP, PORT);
    
    gui = new ofxUICanvas();
    gui->addTextInput("CHAT", chat)->setAutoClear(false);
    ofAddListener(gui->newGUIEvent, this, &ofApp::guiEvent);
    y = 20;
}

//--------------------------------------------------------------
void ofApp::update(){
    
    // check for waiting messages
	while(oscReceiver.hasWaitingMessages()){
		// get the next message
		ofxOscMessage m;
		oscReceiver.getNextMessage(&m);
        
        if(m.getRemoteIp() != MY_IP_ADDRESS){
            
            // example of handling a /mouse/moved message
            if(m.getAddress() == "/mouse/moved"){
                cout << m.getRemoteIp() << " mouse moved to " << m.getArgAsInt32(0) << ", " << m.getArgAsInt32(1) << endl;
                
                // REACT to the /mouse/moved message!
            }
            
            // example of handling a /mouse/pressed message
            if(m.getAddress() == "/mouse/pressed"){
                cout << m.getRemoteIp() << " mouse pressed at " << m.getArgAsInt32(0) << ", " << m.getArgAsInt32(1) << endl;
                
                // REACT to the /mouse/pressed message!
            }
            
            // example of handling a /key/pressed message
            if(m.getAddress() == "/key/pressed"){
                cout << m.getRemoteIp() << " key pressed " << m.getArgAsInt32(0) << endl;
                
                // REACT to the /mouse/moved message!
            }
        }
        
        // handle chat message
        // this is outside the IP check because we do want to display our own messages as well
        if(m.getAddress() == "/chat"){
			handleChat(&m);
		}
	}
}


// Called when we receive a chat message
// Gets the message and pushes it onto the vector (like an "array") of messages.
void ofApp::handleChat(ofxOscMessage *m) {
    string ip = m->getRemoteIp();
    string message = m->getArgAsString(0);
    messages.push_back(ip + ": " + message);
}

//--------------------------------------------------------------
void ofApp::draw(){
    // draw the last 20 messages received.
    y = 0;
    if(messages.size()){
        for(int i =0; i<MIN(messages.size(),20); i++){
            string msg = messages[messages.size()-1-i];
            ofDrawBitmapStringHighlight(msg, 220, y+=20);
        }
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
    // cout << "mouse moved locally" << endl;
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
    //cout << "mouse pressed locally" << endl;
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

void ofApp::exit()
{
  delete gui;
}

void ofApp::guiEvent(ofxUIEventArgs &e)
{
    string ev = e.widget->getName();
    cout << ev << endl;
    if (ev == "CHAT"){
        ofxUITextInput *text = (ofxUITextInput *) e.widget;

        if(text->getInputTriggerType() == OFX_UI_TEXTINPUT_ON_ENTER)
        {
            string message = text->getTextString();
            ofxOscMessage m;
            m.setAddress("/chat");
            m.addStringArg(message);
            oscSender.sendMessage(m);
        }
    }

}
