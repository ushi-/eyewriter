
#include "testApp.h"
#include "stdio.h"

//--------------------------------------------------------------
testApp::testApp(){

}                                                  

//--------------------------------------------------------------
void testApp::setup(){

	
	//---- setup standard application settings
	
//	ofSetVerticalSync(true);  
	
	mode = MODE_TRACKING;
	TM.setup();
	CM.setup();
	typeScene.setup();
	answerScene.setup();
	eyeSmoothed.set(0,0,0);
	
	eyeApp.setup();
	
	ponger.setup();

	
	
	BT.setup("catch me!", 50,50,180,180);
	BT.setRetrigger(true);
	
	timeSince = 0;
	bMouseSimulation = false;
	bMouseEyeInputSimulation = false;

	ofSoundStreamSetup(0,2,this, 44100, 256, 4);	
}


//--------------------------------------------------------------
void testApp::update(){

//	ofBackground(70,70,70);
	ofBackground(30,30,30);
	
	// update the tracking manager (and internally, its input manager)
	TM.update();
	
	// update the calibration manager
	CM.update();
	
	// record some points if we are in auto mode
	if (CM.bAutomatic == true && CM.bAmInAutodrive == true && CM.bInAutoRecording){
		
		if (TM.bGotAnEyeThisFrame()){	
			ofPoint trackedEye = TM.getEyePoint();
			CM.fitter.registerCalibrationInput(trackedEye.x,trackedEye.y);
			CM.inputEnergy = 1;
		}
	}
	
	if (!bMouseSimulation){
	// smooth eye data in...
		if (CM.fitter.bBeenFit){
			
			ofPoint trackedEye;
			
			if (bMouseEyeInputSimulation) {
				trackedEye.x = mouseX;
				trackedEye.y = mouseY;
			} else {
				trackedEye = TM.getEyePoint();
			}

			screenPoint = CM.fitter.getCalibratedPoint(trackedEye.x, trackedEye.y);
			eyeSmoothed.x = CM.smoothing * eyeSmoothed.x + (1-CM.smoothing) * screenPoint.x;
			eyeSmoothed.y = CM.smoothing * eyeSmoothed.y + (1-CM.smoothing) * screenPoint.y;
		}
		
	} else {
		
		eyeSmoothed.x = mouseX;
		eyeSmoothed.y = mouseY;
	}

	
	if (mode == MODE_TEST){
		ofPoint pt = eyeSmoothed;
		if (BT.update(pt.x, pt.y)){
			BT.x = ofRandom(100,ofGetWidth()-100);
			BT.y = ofRandom(100,ofGetHeight()-100);
		}
	}
	
	if( mode == MODE_DRAW ){
		ofPoint pt = eyeSmoothed;
		//if( ofGetElapsedTimef() - timeSince >= 1.0/8.0 ){
			
			//To test with mouse comment this line and uncomment the line below
			eyeApp.update( pt.x, pt.y);
			//eyeApp.update( mouseX, mouseY );
			
		//	timeSince = ofGetElapsedTimef();
		//}
	}
	
	if (mode == MODE_TYPING){
		ofPoint pt = eyeSmoothed;
		typeScene.update(pt.x, pt.y);
	}
	
	if (mode == MODE_PONG){
		ofPoint pt = eyeSmoothed;
		ponger.update(pt.x, pt.y);
	}
	
	if (mode == MODE_ANSWER) {
		ofPoint pt = eyeSmoothed;
		answerScene.update(pt.x, pt.y);
	}
	
}

//--------------------------------------------------------------
void testApp::draw(){

	
	ofSetColor(255, 255, 255);
	
	if (mode == MODE_TRACKING)			TM.draw();
	if (mode == MODE_CALIBRATING)		CM.draw();
	if (mode == MODE_TEST)				BT.draw();
	if (mode == MODE_DRAW )				eyeApp.draw();
	if (mode == MODE_TYPING)			typeScene.draw();
	if (mode == MODE_PONG)				ponger.draw();
	if (mode == MODE_ANSWER)			answerScene.draw();
		
	// draw a green dot to see how good the tracking is:
	if (CM.fitter.bBeenFit || bMouseSimulation){
		if( mode != MODE_DRAW ){	
			ofSetColor(0,255,0,120);
			ofFill();
			ofCircle(eyeSmoothed.x, eyeSmoothed.y, 20);
		}
	}
	
	if (TM.IM.bRecord) {
		ofSetColor(255, 0, 0);
		ofFill();
		ofRect(0, ofGetHeight()-10, 10, 10);
	}
	
	if (mode != MODE_TRACKING) {
		ofEnableAlphaBlending();
		ofSetColor(255, 255, 255, 120);
		TM.drawInput(0, 0, TM.IM.width/4, TM.IM.height/4, TM.IM.width/4, 0, TM.IM.width/4, TM.IM.height/4);	
		ofDisableAlphaBlending();
	}
	
	ofSetColor(255, 255, 255);
	ofDrawBitmapString("FrameRate: " + ofToString(ofGetFrameRate(), 5), 1, ofGetHeight() - 20);

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	
	if (mode == MODE_ANSWER && answerScene.editingText) {
		answerScene.keyPressed(key);
		return;
	}
	
	switch (key){
			
		case	OF_KEY_RETURN:
			mode ++;
			mode %= 4; // number of modes;
			break;
			
		case	'm':
		case	'M':
			bMouseSimulation = !bMouseSimulation;
			break;
			
		case	'r':
		case	'R':
			if (TM.IM.bRecord) TM.IM.stopRecord();
			else TM.IM.startRecord();
			break;
			
		case	'n':
		case	'N':
			bMouseEyeInputSimulation = !bMouseEyeInputSimulation;
			break;
			

		case	'f':
		case	'F':
			ofToggleFullscreen();
			break;
			
		case	'c':
		case	'C':
			TM.setOriginalPosition();
			break;
			
		case 'x':
		case 'X':
			TM.bOriginalPositon = false;
			break;
			
			
	}
	
	if (mode == MODE_CALIBRATING){
		CM.keyPressed(key);
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	if (mode == MODE_TRACKING)			TM.mouseDragged(x, y, button);
	if (mode == MODE_CALIBRATING)		CM.mouseDragged(x, y, button);
	if (mode == MODE_ANSWER)			answerScene.mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	if (mode == MODE_TRACKING)			TM.mousePressed(x, y, button);
	if (mode == MODE_CALIBRATING)		CM.mousePressed(x, y, button);
	if (mode == MODE_ANSWER)			answerScene.mousePressed(x, y, button);

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	if (mode == MODE_TRACKING)			TM.mouseReleased();
	if (mode == MODE_CALIBRATING)		CM.mouseReleased(x,y,button);
	if (mode == MODE_ANSWER)			answerScene.mouseReleased(x, y, button);
}

//--------------------------------------------------------------
void testApp::resized(int w, int h){

}

void testApp::sdlTextChanged(char* text){
	if (mode == MODE_ANSWER) answerScene.sdlTextChanged(text);
}

//--------------------------------------------------------------
void testApp::audioReceived 	(float * input, int bufferSize, int nChannels){	
	// samples are "interleaved"
	if (mode == MODE_ANSWER && answerScene.bRecording){
		for (int i = 0; i < bufferSize; i++){
			answerScene.bufferLeft[i] = input[i*2];
			answerScene.bufferRight[i] = input[i*2+1];
		}
		answerScene.sndfileHandle.writef(input, bufferSize);
	}
}


void testApp::exit(){
	if (mode == MODE_ANSWER) answerScene.exit();
}













