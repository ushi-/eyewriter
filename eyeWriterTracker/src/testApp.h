#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"

#include "trackingManager.h"	
#include "calibrationManager.h"
#include "buttonTrigger.h"
#include "typingScene.h"
#include "pongScene.h"
#include "answeringScene.h"
#include "ofxSDL.h"

enum{
	
//	MODE_TRACKING,	MODE_CALIBRATING,	MODE_TEST, MODE_DRAW,  MODE_TYPING, MODE_PONG, MODE_ANSWER
	MODE_TRACKING,	MODE_CALIBRATING,	MODE_TEST, MODE_ANSWER, MODE_DRAW,  MODE_TYPING, MODE_PONG

};

#include "eyePlotterTestApp.h"

class testApp : public ofxSDLApp {

	public:

		testApp();
		void setup();
		void update();
		void draw();
		void exit();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void resized(int w, int h);
	void sdlTextChanged(char* text);
	void audioReceived 	(float * input, int bufferSize, int nChannels); 

		//----- scenes

		trackingManager			TM;
		calibrationManager		CM;
	
		buttonTrigger			BT;
		eyePlotterTestApp	eyeApp;
		typingScene				typeScene;
		pongScene				ponger;
		answeringScene		answerScene;

	
	
		ofPoint eyeSmoothed;
		ofPoint screenPoint;
		float waitFpsTime;
		float timeSince;
	
		int mode; 
	
		bool bMouseSimulation;
		bool bMouseEyeInputSimulation;
	
		//------ drawing
		void drawHelp();
	
		static const float rotSmooth = .9;

};

#endif
