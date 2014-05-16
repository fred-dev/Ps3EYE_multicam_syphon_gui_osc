#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    XML.loadFile("mySettings.xml");
    camWidth		= XML.getValue("CAMWIDTH", 640);
	camHeight	= XML.getValue("CAMHEIGHT", 480);
	frameRate	= XML.getValue("FRAMERATE", 25);
    recievePort	= XML.getValue("RECIEVEPORT", 1234);
    
    
    receiver.setup(recievePort);

	//ofSetVerticalSync(false);
	//changes for fun
	ofSetLogLevel(OF_LOG_VERBOSE);	
	
	vector<ofxMacamPs3EyeDeviceInfo*> deviceList = ofxMacamPs3Eye::getDeviceInfoList();
	for (int i = 0; i < deviceList.size(); i++) {
        ofxSyphonServer * server = new ofxSyphonServer();
		ofxMacamPs3Eye * camera = new ofxMacamPs3Eye();
        ofTexture * texture = new ofTexture();
		camera->setDeviceID(deviceList[i]->id);
		camera->setDesiredFrameRate(frameRate);
		camera->initGrabber(camWidth, camHeight);
		cameras.push_back(camera);
        cameras[i]->setAutoGainAndShutter(false); // otherwise we can'   t set gain or shutter
        cameras[i]->setGain(0.9);
        cameras[i]->setShutter(1.0);
        cameras[i]->setGamma(0.5);
        cameras[i]->setBrightness(0.6);
        cameras[i]->setContrast(1.0);
        cameras[i]->setHue(0.5);
        cameras[i]->setFlicker(1);
        cameras[i]->setWhiteBalance(1);
		
        
        server->setName("Camera " +ofToString(i+1)+" Output");
        
        servers.push_back(server);
        
        textures.push_back(texture);
        gui.addPage();
        gui.addTitle("Camera"+ ofToString(i+1));
        gui.addToggle("Draw Camera", drawcams[i]);
     //   gui.addToggle("Use Auto", camsAuto[i]);
        gui.addSlider("Gain", camsGain[i], 0.0, 1.0);
        gui.addSlider("Shutter", camsShutter[i], 0.0, 1.0);
        gui.addSlider("Gamma", camsGamma[i], 0.0, 1.0);
        gui.addSlider("Brightness", camsBrightness[i], 0.0, 1.0);
        gui.addSlider("Contrast", camsContrast[i], 0.0, 1.0);
        gui.addSlider("Hue", camsHue[i], 0.0, 1.0);
        gui.addSlider("Flicker Mode", camsFlicker[i], 1, 3);
        gui.addSlider("White Balance Mode", camsWbMode[i], 1, 4);
        
    }
    
    camCounter=deviceList.size();
    
    
    gui.loadFromXML();
    
    gui.show();


	if(cameras.size() > 0){
		ofSetWindowShape(camWidth * cameras.size(), 900);
	}
}


void testApp::update(){
    if (camCounter>0) {
        for (int i = 0; i < cameras.size(); i++) {
            cameras[i]->setAutoGainAndShutter(false); // otherwise we can'   t set gain or shutter
            
            cameras[i]->setGain(camsGain[i]);
            cameras[i]->setShutter(camsShutter[i]);
            cameras[i]->setGamma(camsGamma[i]);
            cameras[i]->setBrightness(camsBrightness[i]);
            cameras[i]->setContrast(camsContrast[i]);
            cameras[i]->setHue(camsHue[i]);
            cameras[i]->setFlicker(camsFlicker[i]);
            cameras[i]->setWhiteBalance(camsWbMode[i]);
            cameras[i]->update();
            textures[i]=&cameras[i]->getTextureReference();
            servers[i]->publishTexture(textures[i]);
        }
    }
    if (camCounter>0) {
        for (int i = 0; i < cameras.size(); i++) {
            while(receiver.hasWaitingMessages()){
                // get the next message
                ofxOscMessage m;
                receiver.getNextMessage(&m);
                if ( m.getAddress() == "/"+ofToString(i+1)+"/gain" ){
                    camsGain[i] = m.getArgAsFloat( 0 );
                    cameras[i]->setGain(camsGain[i]);
                }
                if ( m.getAddress() == "/"+ofToString(i+1)+"/shutter" ){
                    camsShutter[i] = m.getArgAsFloat( 0 );
                    cameras[i]->setShutter(camsShutter[i]);
                }
                if ( m.getAddress() == "/"+ofToString(i)+"/brightness" ){
                    camsBrightness[i] = m.getArgAsFloat( 0 );
                    cameras[i]->setBrightness(camsBrightness[i]);

                }
                if ( m.getAddress() == "/"+ofToString(i+1)+"/contrast" ){
                    camsContrast[i] = m.getArgAsFloat( 0 );
                    cameras[i]->setContrast(camsContrast[i]);
                }
                if ( m.getAddress() == "/"+ofToString(i+1)+"/hue" ){
                    camsHue[i] = m.getArgAsFloat( 0 );
                    cameras[i]->setHue(camsHue[i]);
                }
                if ( m.getAddress() == "/"+ofToString(i+1)+"/flicker" ){
                    camsFlicker[i] = m.getArgAsInt32( 0 );
                    cameras[i]->setFlicker(camsFlicker[i]);
                }
                if ( m.getAddress() == "/"+ofToString(i+1)+"/white_blalnce" ){
                    camsWbMode[i] = m.getArgAsInt32( 0 );
                    cameras[i]->setWhiteBalance(camsWbMode[i]);
                }
            }
        }
    }
    
}

//--------------------------------------------------------------
void testApp::draw(){
    
    
	
	
	if(cameras.size() == 0){
		ofDrawBitmapString("No PS3Eye found. :(", 20, 20);
	}
    
    if (camCounter>0) {
        for (int i = 0; i < cameras.size(); i++) {
            if (drawcams[i]==true) {
                cameras[i]->draw(i * cameras[i]->getWidth(),0);
                ofDrawBitmapString(ofToString(cameras[i]->getRealFrameRate()), i * cameras[i]->getWidth() + 20, 20);
            }
        }
    }
    

    if( bHide ){
		gui.draw();
	}
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if( key == 'g' ){
		bHide = !bHide;
	}
	if(key == 'n') {
		gui.nextPage();
	}
    if (key == 'p') {
        gui.prevPage();
    }

    
    
    

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}