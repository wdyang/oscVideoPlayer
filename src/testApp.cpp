#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	// listen on the given port
	cout << "listening for osc messages on port " << PORT << "\n";
	receiver.setup(PORT);

	current_msg_string = 0;
	mouseX = 0;
	mouseY = 0;
	mouseButtonState = "";

    //get files from data path, use the first file
    string path = "";
    ofDirectory dir(path);
    dir.listDir();
    
    //go through and print out all the paths
    for(int i = 0; i < dir.numFiles(); i++){
        cout<<dir.getPath(i)<<endl;
    }

	ofBackground(0, 0, 0);
    vidPlayer.loadMovie(dir.getPath(0));
//    vidPlayer.loadMovie("StereoscopicSkullFux.m4v");
//    vidPlayer.
//    vidPlayer.play();
    

}

//--------------------------------------------------------------
void testApp::update(){
    
    quietCnt ++;
    
	// hide old messages
	for(int i = 0; i < NUM_MSG_STRINGS; i++){
		if(timers[i] < ofGetElapsedTimef()){
			msg_strings[i] = "";
		}
	}

	// check for waiting messages
	while(receiver.hasWaitingMessages()){
		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage(&m);

        // check for mouse moved message
		if(m.getAddress() == "/location"){
			// both the arguments are int32's
			int x = m.getArgAsInt32(0);
			int y = m.getArgAsInt32(1);
//            cout<<"/location "<<x<<" "<<y<<endl;
            targetPct = x/300.0;
//            cout<<targetPct<<endl;
            if(bMirror) {
                targetPct = 1.0-targetPct;
            }
            
            //map y from 0 to 240 to zoom 1 to 4
            targetZoom = y/240.0 * 3.0 + 1;
            
            quietCnt  = 0;
		}
	}
    
    if(quietCnt>30){
        targetPct = 0.5; //should there is no action for 0.5 sec, go back to middle
        targetZoom = 2.0;
    }
//    float z = 0.2;
    currentPosition = (1-z) * currentPosition + z* targetPct;
    currentZoom = (1-z)*currentZoom + z*targetZoom;
    
    vidPlayer.setPosition(currentPosition);
    vidPlayer.update();
//    cout<<"target: "<<targetPct<<" current: "<<currentPosition<<endl;
    string titleStr;
    titleStr = "target: "+ofToString(toFixNum(targetPct))+" current: "+ofToString(toFixNum(currentPosition))+ " z: "+ofToString(toFixNum(z)) + " currentZoom " + ofToString(toFixNum(currentZoom)) + " targetZoom " + ofToString(toFixNum(targetZoom))+" 'z' to toggle use Y to zoom";
    ofSetWindowTitle(titleStr);


}

float testApp::toFixNum(float x){
    return round(x * 100);
}

//--------------------------------------------------------------
void testApp::draw(){

//    vidPlayer.draw(displayOffsetX, displayOffsetY, ofGetWindowWidth(), ofGetWindowWidth());
    if(bUseYToZoom){
        int newWidth = WINDOW_WIDTH * currentZoom;
        int newHeight = WINDOW_HEIGHT* currentZoom;
        int x0 = WINDOW_WIDTH/2 - newWidth / 2;
        int y0 = WINDOW_HEIGHT/2 - newHeight/2 + (currentZoom-1) * 350;
        vidPlayer.draw(x0,y0, newWidth, newHeight);
    }else{
        vidPlayer.draw(0,0, WINDOW_WIDTH, WINDOW_HEIGHT);
    }
//    vidPlayer.draw(0,0, 800, 600);
//	string buf;
//	buf = "listening for osc messages on port" + ofToString(PORT);
//	ofDrawBitmapString(buf, 10, 20);
//
//	// draw mouse state
//	buf = "mouse: " + ofToString(mouseX, 4) +  " " + ofToString(mouseY, 4);
//	ofDrawBitmapString(buf, 430, 20);
//	ofDrawBitmapString(mouseButtonState, 580, 20);
//
//	for(int i = 0; i < NUM_MSG_STRINGS; i++){
//		ofDrawBitmapString(msg_strings[i], 10, 40 + 15 * i);
//	}



}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    cout<<"key pressed "<<key<<endl;
    switch (key) {
        case 'f':
            ofToggleFullscreen();
            break;
        case '=':
            if(z<0.95){
                z+=0.05;
            }
            break;
        case '-':
            if(z>0.05){
                z-=0.05;
            }
            break;
        case 'm':
            bMirror=!bMirror;
            break;
        case 'z':
            bUseYToZoom = !bUseYToZoom;
            break;
        case 357:
            displayOffsetY+=10;
            break;
        case 359:
            displayOffsetY-=10;
            break;
        default:
            break;
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
