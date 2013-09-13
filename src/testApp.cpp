#include "testApp.h"
/*
 Slapped together this app with two OF examples. All original code by other talented individuals.
 
    I did NOT make Syphon or ofxEDSDK, I just saw an opportunity to offer a useful tool to the community.
 
 Credits I can find:
    ofxEdsdk  - Kyle McDonald ( www.kylemcdonald.net )
    ofxSyphon - http://code.google.com/p/syphon-implementations/source/browse/#svn%2Ftrunk%2FSyphon%20Implementations%2FOpenFrameworks
    Syphon by Anton Marini ( http://vade.info/ ) and Tom Butterworth ( http://kriss.cx/tom )
    
 
    Please donate for continued Syphon development - http://syphon.v002.info/
 
    EDSDK from Canon Inc. 
*/

void testApp::setup() {
    
    ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofSetLogLevel(OF_LOG_VERBOSE);
    tex.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);  
    
	camera.setup();
    
    serverName = "CanonOutput";
    textureName = "Canon_Texture";
    
    if( xml.loadFile("xml/ServerName.xml") ){
		cout<< "ServerName.xml loaded!" <<endl;
        serverName = xml.getValue("NAMES:SERVER", "CanonOutput");
        textureName = xml.getValue("NAMES:TEXTURE", "Canon_Texture");
        cout << "ServerName: " << serverName <<endl;
        cout << "TextureName: " << textureName <<endl;

	}else{
		cout << "unable to load mySettings.xml check data/ folder" <<endl;
	}
    
        
    
    mainOutputSyphonServer.setName(serverName);
    individualTextureSyphonServer.setName(textureName);
    
    bRenderOnScreen=true;
    
}

void testApp::update() {
	camera.update();
	if(camera.isFrameNew()) {
	}
	if(camera.isPhotoNew()) {
		camera.savePhoto(ofToString(ofGetFrameNum()) + ".jpg");
	}
}

void testApp::draw() {
    ofSetColor(255, 255, 255);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
	//camera.draw(0, 0);
	// camera.drawPhoto(0, 0, 432, 288);

    if(bRenderOnScreen){
    
        if(camera.isLiveReady()) {
            camera.draw(0, 0,ofGetWidth(),.6667*ofGetWidth());
        }
        else{
            ofSetColor(0, 0, 0);
            ofRect(0, 0, ofGetWidth(), ofGetHeight());
            ofSetColor(255, 255, 255);
            for(int i=0; i<ofGetWidth(); i=i+150){
                for(int j=0; j<ofGetHeight(); j=j+50)
                ofDrawBitmapString("No Camera Found!", i,j);
            }
        }
        mainOutputSyphonServer.publishScreen(); ///Syphon grab starts NOW. Everything after will not be displayed
    }
    else{ //or publish as a texture and don't draw to screen
        if(camera.isLiveReady()){
            //tex.readToPixels(camera.getLivePixels());
            tex.loadData(camera.getLivePixels());
            individualTextureSyphonServer.publishTexture(&tex);
        }
        else{
            ofSetColor(0, 0, 0);
            ofRect(0, 0, ofGetWidth(), ofGetHeight());
            ofSetColor(255, 255, 255);
            for(int i=0; i<ofGetWidth(); i=i+150){
                for(int j=0; j<ofGetHeight(); j=j+50)
                    ofDrawBitmapString("No Camera Found!", i,j);
            }
        }

    }
    
    if(camera.isLiveReady()) {
		stringstream status;
        status << ofGetWidth() << "x" << ofGetHeight() << " @ " <<
        (int) ofGetFrameRate() << " app-fps " << " / " <<
        (int) camera.getFrameRate() << " cam-fps";
		ofDrawBitmapString(status.str(), 10, 20);
        ofDrawBitmapString("Outputting Syphon: \"" + serverName + "\"", 10,50);
        ofDrawBitmapString("Outputting Texture: \"" + textureName + "\"", 10,65);
        ofDrawBitmapString("Press 'r' to render to screen or offscreen as texture", 10,80);
	}
}

void testApp::mouseReleased(int x, int y, int button){

}

void testApp::keyPressed(int key) {
	if(key == ' ') {
		camera.takePhoto();
	}
    if(key == 'r') {
		bRenderOnScreen = !bRenderOnScreen;
	}
}