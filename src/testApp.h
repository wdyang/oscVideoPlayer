#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

// listen on port 12345
#define PORT 8000
#define NUM_MSG_STRINGS 20

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

class testApp : public ofBaseApp {
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
    
        int displayOffsetX=0;
        int displayOffsetY=0;
        bool bMirror=false;
        bool bUseYToZoom = false;
    
        float currentZoom = 2.0;
        float targetZoom = 2.0;
    
        float z=0.2;

		ofTrueTypeFont font;
		ofxOscReceiver receiver;

		int current_msg_string;
		string msg_strings[NUM_MSG_STRINGS];
		float timers[NUM_MSG_STRINGS];

		int mouseX, mouseY;
		string mouseButtonState;
    
        ofVideoPlayer vidPlayer;
        float targetPct = 0.5;
        float currentPosition = 0.5;
        int quietCnt = 0;
    
    float toFixNum(float x);
};
