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

	addButton.setup("クリックしてボタンを追加", ofGetWidth() - 370, 10, 360, 100);
	removeButotn.setup("削除したいボタンをドロップ", ofGetWidth() - 370, ofGetHeight() - 110, 360, 100);
	
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
	removeButotn.draw();
	
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
	vector<buttonTriggerTransformableQuesoglc>::iterator it = buttons.begin();
	while (it != buttons.end()) {
		it->editing = false;
		++it;
	}
	editingText = false;
	
	vector<buttonTriggerTransformableQuesoglc>::reverse_iterator rit = buttons.rbegin();
	while (rit != buttons.rend()) {
		if (rit->inRect(x, y)) {
			rit->mousePressed(x, y, button);
			break;
		}
		++rit;
	}
}

void answeringScene::mouseDragged(int x, int y, int button) {
	vector<buttonTriggerTransformableQuesoglc>::iterator it = buttons.begin();
	while (it != buttons.end()) {
		if(it->pressing) {
			it->mouseDragged(x, y, button);
		}
		++it;
	}
}

void answeringScene::mouseReleased(int x, int y, int button) {
	vector<buttonTriggerTransformableQuesoglc>::iterator it = buttons.begin();
	while (it != buttons.end()) {
		if (it->inRect(x, y)) {
			if (it->dragging && removeButotn.inRect(x, y)){
				it = buttons.erase(it);
				break;
			}
			it->mouseReleased(x, y, button);
			if (it->editing) {
				editingText = true;
			}
		}
		++it;
	}

}

void answeringScene::keyPressed(int key) {
	if (key == OF_KEY_RETURN) {
		vector<buttonTriggerTransformableQuesoglc>::iterator it = buttons.begin();
		while (it != buttons.end()) {
			it->editing = false;
			++it;
		}
		editingText = false;
		return;
	}
	vector<buttonTriggerTransformableQuesoglc>::iterator it = buttons.begin();
	while (it != buttons.end()) {
		if (it->editing) {
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
		if (it->editing) {
			it->setDisplayText(text);
		}
		++it;
	}
}
