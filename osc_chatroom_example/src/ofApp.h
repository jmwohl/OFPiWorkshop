#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxUI.h"
#include "ofxXmlSettings.h"

#define PORT 8000

#define MY_IP_ADDRESS "10.88.0.134"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    ofxOscReceiver oscReceiver;
    ofxOscSender oscSender;
    
    // gui for chat input
    ofxUICanvas *gui;
    void exit();
    void guiEvent(ofxUIEventArgs &e);
    string chat;
    void handleChat(ofxOscMessage *m);
    vector<string> messages;
    int y;
};
