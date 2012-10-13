#pragma once

#include "ofMain.h"
#include "ofxMacamPs3Eye.h"
#include "ofxSyphon.h"
#include "ofxSimpleGuiToo.h"
#include "ofxOsc.h"


class testApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
//    void onAutoGainAndShutterChange(bool & value);
//	void onGainChange(float & value);
//	void onShutterChange(float & value);
//	void onGammaChange(float & value);
//	void onBrightnessChange(float & value);
//	void onContrastChange(float & value);
//	void onHueChange(float & value);
//	void onLedChange(bool & value);
//	void onFlickerChange(int & value);
//	void onWhiteBalanceChange(int & value);
    
    bool bHide;
    
    int camWidth;
    int camHeight;
    int frameRate;
    int camCounter;
    ofxXmlSettings XML;
    
    vector<ofxMacamPs3Eye*> cameras;
    vector<ofxSyphonServer*> servers;
    vector<ofTexture*> textures;

    bool drawcams[16];
   /// bool camsAuto[16];
    float camsShutter[16];
    float camsGain[16];
    float camsGamma[16];
    float camsBrightness[16];
    float camsContrast[16];
    float camsHue[16];
    int camsFlicker[16];
    int camsWbMode[16];
    int recievePort;
    
    ofxOscReceiver receiver;
    

};
