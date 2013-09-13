#pragma once

#include "ofMain.h"

#include "ofxEdsdk.h"
#include "ofxSyphon.h"
#include "ofxXmlSettings.h"

class testApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);
    void mouseReleased(int x, int y, int button);
	
	ofxEdsdk::Camera camera;
    
    ofxSyphonServer mainOutputSyphonServer;
    
        bool bRenderOnScreen;
    ofTexture tex;
    ofxSyphonServer individualTextureSyphonServer;
    ofxXmlSettings xml;
    string serverName;
    string textureName;
};
