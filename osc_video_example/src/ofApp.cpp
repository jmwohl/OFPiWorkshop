#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    oscReceiver.setup(PORT);
    
    // broadcast
    oscSender.setup(BROADCAST_IP, PORT);
    
    // let's make the camera display full screen.
    camWidth = 640;
    camHeight = 480;
    
    vector<ofVideoDevice> devices = vidGrabber.listDevices();
    
    for(int i = 0; i < devices.size(); i++){
        cout << devices[i].id << ": " << devices[i].deviceName;
        if( devices[i].bAvailable ){
            cout << endl;
        }else{
            cout << " - unavailable " << endl;
        }
    }
    
    vidGrabber.setDeviceID(0);
	vidGrabber.setDesiredFrameRate(30);
	vidGrabber.initGrabber(camWidth,camHeight);
    
    // the number of bytes is width * height * 3 for RGB.
    videoBytesAltered = new unsigned char[camWidth*camHeight*3];
	videoTexture.allocate(camWidth,camHeight, GL_RGB);
	ofSetVerticalSync(true);
}

//--------------------------------------------------------------
void ofApp::update(){
    
    // check for waiting message
	while(oscReceiver.hasWaitingMessages()){
		// get the next message
		ofxOscMessage m;
		oscReceiver.getNextMessage(&m);
        
        // This is to ensure we're not reacting to our own messages
        if(m.getRemoteIp() != MY_IP_ADDRESS) {
            
            // example of handling a /mouse/moved message
            if(m.getAddress() == "/mouse/moved"){
                cout << m.getRemoteIp() << " mouse moved to " << m.getArgAsInt32(0) << ", " << m.getArgAsInt32(1) << endl;

                mouseEffect = ofMap(m.getArgAsFloat(1), 0, ofGetScreenHeight(), 0, 255);
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
    
    // Update the video
    vidGrabber.update();
	
    // If we have a new frame from the camera, loop through each pixel
    // and alter it.
	if (vidGrabber.isFrameNew()){
		int totalPixels = camWidth*camHeight*3;
		unsigned char * pixels = vidGrabber.getPixels();
		for (int i = 0; i < totalPixels; i++){
			videoBytesAltered[i] = pixels[i] + mouseEffect;
		}
		videoTexture.loadData(videoBytesAltered, camWidth,camHeight, GL_RGB);
	}
    
}


//--------------------------------------------------------------
void ofApp::draw(){
    videoTexture.draw(0,0,camWidth,camHeight);
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
