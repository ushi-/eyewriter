//
//  answeringScene.cpp
//  RemoteEyeTracker
//
//  Created by Yosuke Ushigome on 8/24/11.
//  Copyright (c) 2011 Yosuke Ushigome. All rights reserved.
//

#include "answeringScene.h"
#include "glc.h"

//switch to gui
extern  int buttonCount; 

GLint ctx = 0;
GLint font = 0;

//--------------------------------------------------------------
void answeringScene::setup(){
	
	helvetica.loadFont("fonts/HelveticaNeueMed.ttf", 32);
//	jaFont.loadFont("fonts/AxisCondStd-Bold.otf", 32, true);
	
	ctx = glcGenContext();
	glcContext(ctx);
	
	glcAppendCatalog(ofToDataPath("fonts").c_str());
	
//	glcAppendCatalog("/System/Library/Fonts");
	
	font = glcGenFontID();
	glcNewFontFromFamily(font, "AXIS Condensed Std");
	glcFontFace(font, "Bold");
	glcFont(font);
	
	glcRenderStyle(GLC_TEXTURE);
    glcEnable(GLC_GL_OBJECTS);
    glcEnable(GLC_MIPMAP);
	glcEnable(GLC_HINTING_QSO);
	glcStringType(GLC_UTF8_QSO);	
	//buttonCount=390;
	ofBackground(255, 255, 255);

	addButton.setup("images/add.png", ofGetWidth() - 110, 10, 100, 100);
	
	buttonTriggerTransformableQuesoglc yesButton;
	yesButton.setup("はい", ofGetWidth()/2.0 - 310 - 150, ofGetHeight()/2.0 - 100, 300, 200);
	yesButton.setMaxCounter(buttonCount);
	yesButton.setRetrigger(false);
	buttons.push_back(yesButton);
	
	buttonTriggerTransformableQuesoglc noButton;
	noButton.setup("いいえ", ofGetWidth()/2.0 + 310 - 150, ofGetHeight()/2.0 - 100, 300, 200);
	noButton.setMaxCounter(buttonCount);
	noButton.setRetrigger(false);
	buttons.push_back(noButton);
	
	mx = 0.0;
	my = 0.0; 
	editingText = false;
	bRecording = false;

	bufferLeft = new float[256];
	bufferRight = new float[256];

}
//--------------------------------------------------------------
void answeringScene::update(float mouseX, float mouseY){
	mx = mouseX;
	my = mouseY;
	
	vector<buttonTriggerTransformableQuesoglc>::iterator it = buttons.begin();
	while (it != buttons.end()) {
		if (it->update(mx, my)) {
			answer.loadSound("sounds/"+ it->displayText + ".wav");
			if (!answer.bLoadedOk) {
				answer.loadSound("sounds/Ping.wav");
			}
			answer.play();
		}
		++it;
	}
	
	//ofSetFrameRate(100);
	
}	

//--------------------------------------------------------------
void answeringScene::draw(){
	ofPushStyle();	

	addButton.draw();
	
	vector<buttonTriggerTransformableQuesoglc>::iterator it = buttons.begin();
	while (it != buttons.end()) {
		it->draw();
		++it;
	}
	
	ofPopStyle();
}

void answeringScene::mousePressed(int x, int y, int button) {
	if (addButton.inRect(x, y)) {
		buttonTriggerTransformableQuesoglc newButton;
		newButton.setup("新しいボタン", ofGetWidth()/2.0 - 150, ofGetHeight()/2.0 - 100, 300, 200);
		newButton.setMaxCounter(buttonCount);
		newButton.setRetrigger(false);
		buttons.push_back(newButton);
	}
	
	editingText = false;
	vector<buttonTriggerTransformableQuesoglc>::reverse_iterator rit = buttons.rbegin();
	while (rit != buttons.rend()) {
		rit->mousePressed(x, y, button);
		if (rit->state == buttonStateRecordStopped) {
			// save wav
			bRecording = false;
			rit->state = buttonStateNone;
		}
		++rit;
	}
}

void answeringScene::mouseDragged(int x, int y, int button) {
	vector<buttonTriggerTransformableQuesoglc>::iterator it = buttons.begin();
	while (it != buttons.end()) {
		it->mouseDragged(x, y, button);
		++it;
	}
}

void answeringScene::mouseReleased(int x, int y, int button) {
	vector<buttonTriggerTransformableQuesoglc>::iterator it = buttons.begin();
	while (it != buttons.end()) {
		if (it->inRect(x, y)) {
			it->mouseReleased(x, y, button);
			if (it->state == buttonStateRemoving) {
				it = buttons.erase(it);
				continue;
			}
			if (it->state == buttonStateEditing) {
				it->setDisplayText("");
				editingText = true;
			}
			if (it->state == buttonStateRecordStarted) {
				sndfileHandle = SndfileHandle((ofToDataPath("sounds/")+it->displayText+".wav").c_str(), 
											  SFM_WRITE, 
											  SF_FORMAT_WAV | SF_FORMAT_PCM_16, 
											  2, 
											  44100);
				bRecording = true;				
			}
			if (it->state == buttonStateRecordStopped) {
				// save wav
				bRecording = false;
				sndfileHandle = SndfileHandle();
				it->state = buttonStateNone;
			}
		}
		++it;
	}

}

void answeringScene::keyPressed(int key) {
	if (key == OF_KEY_RETURN) {
		vector<buttonTriggerTransformableQuesoglc>::iterator it = buttons.begin();
		while (it != buttons.end()) {
			it->state = buttonStateNone;
			++it;
		}
		editingText = false;
		return;
	}
	vector<buttonTriggerTransformableQuesoglc>::iterator it = buttons.begin();
	while (it != buttons.end()) {
		if (it->state == buttonStateEditing) {
			if (key == OF_KEY_DEL) {
				it->setDisplayText((it->displayText).substr(0, (it->displayText).size()-1));
			}else {
				it->setDisplayText((it->displayText)+(char)key);
			}
		}
		++it;
	}
}

void answeringScene::sdlTextChanged(char *text) {
	if ((string)text == "") {
		return;
	}
	vector<buttonTriggerTransformableQuesoglc>::iterator it = buttons.begin();
	while (it != buttons.end()) {
		if (it->state == buttonStateEditing) {
			it->setDisplayText(text);
		}
		++it;
	}
}
