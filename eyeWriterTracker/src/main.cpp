#include "ofMain.h"
#include "testApp.h"
#include "ofAppGlutWindow.h"
#include "ofxSDL.h"

//========================================================================
int main( ){

    ofxSDLAppWindow window;
	ofSetupOpenGL(&window, 1440,860, OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new testApp());
}
