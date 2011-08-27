//
//  answeringScene.h
//  RemoteEyeTracker
//
//  Created by Yosuke Ushigome on 8/24/11.
//  Copyright (c) 2011 Yosuke Ushigome. All rights reserved.
//

#pragma once

#include "ofMain.h"
#include "buttonStateManager.h"
#include "buttonState.h"

#include "buttonRect.h"
#include "buttonToggle.h"
#include "buttonTrigger.h"
#include "buttonTransformable.h"
#include "buttonTriggerTransformableQuesoglc.h"
#include "buttonQuesoglc.h"

#include "ofxXmlSettings.h"
#include "baseScene.h"


extern "C" {
#include "speak.h"
};


class answeringScene : public baseScene{
	
public:
	
	void setup();
	void update(float mouseX, float mouseY);
	void draw();
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void printMessageHistory();
	void keyPressed  (int key);
	void sdlTextChanged(char* text);
	
	
	vector <buttonTriggerTransformableQuesoglc> buttons;
	buttonQuesoglc addButton;
	buttonQuesoglc removeButotn;
	buttonTriggerTransformableQuesoglc currentButton;
	
	ofTrueTypeFont  helvetica;	
	
	bool editingText;
};
