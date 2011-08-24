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
	
	buttonTransformable yesButton;
	yesButton.setup("Yes.", 100, 100, 300, 200);
	yesButton.setMaxCounter(buttonCount);
	yesButton.setRetrigger(false);
	buttons.push_back(yesButton);
	
	mx = 0.0;
	my = 0.0; 
}
//--------------------------------------------------------------
void answeringScene::update(float mouseX, float mouseY){
	mx = mouseX;
	my = mouseY;
	
	vector<buttonTransformable>::iterator it = buttons.begin();
	while (it != buttons.end()) {
		if (it->update(mx, my)) {
			
		}
		++it;
	}

	
	//ofSetFrameRate(100);
	
}	

//--------------------------------------------------------------
void answeringScene::draw(){
	glEnable(GL_TEXTURE_2D);
	ofPushStyle();	
	
	glPushMatrix();

	glTranslatef(ofGetWidth()/2, ofGetHeight()/2, 0);
	
	glRotatef(60, 1, 0, 0);
	
	static float rot = 0;
	glRotatef(rot, 0, 0, 1);
	rot += 0.1;
	
	glTranslatef(0, 32, 0);
	
	glPushMatrix();
	glTranslatef(0, 0, 0);
	glScalef(32, -32, 1);
	glcRenderString("あのイーハトーヴォのすきとおった風、");
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0, 50, 0);
	glScalef(32, -32, 1);
	glcRenderString("夏でも底に冷たさをもつ青いそら、");
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0, 100, 0);
	glScalef(32, -32, 1);
	glcRenderString("うつくしい森で飾られたモリーオ市、");
	glPopMatrix();	
	
	glPushMatrix();
	glTranslatef(0, 150, 0);
	glScalef(32, -32, 1);
	glcRenderString("郊外のぎらぎらひかる草の波。");
	glPopMatrix();	

	glPopMatrix();

	
//	ofRectangle rect = jaFont.getStringBoundingBox("牛desu", 0, 0);
//	ofSetColor(0, 0, 0);
//	jaFont.drawString("牛desu", ofGetWidth()/2-rect.width/2, ofGetHeight()/2+rect.height/2);
//	ofSetColor(255, 255, 255);
	
	vector<buttonTransformable>::iterator it = buttons.begin();
	while (it != buttons.end()) {
		it->draw();
		++it;
	}
	
	ofPopStyle();
}

void answeringScene::mousePressed(int x, int y, int button) {
	vector<buttonTransformable>::iterator it = buttons.begin();
	while (it != buttons.end()) {
		if (it->inRect(x, y)) {
			it->mousePressed(x, y, button);
		}
		++it;
	}
}

void answeringScene::mouseDragged(int x, int y, int button) {
	vector<buttonTransformable>::iterator it = buttons.begin();
	while (it != buttons.end()) {
		if(it->pressing) {
			it->mouseDragged(x, y, button);
		}
		++it;
	}
}

void answeringScene::mouseReleased(int x, int y, int button) {
	vector<buttonTransformable>::iterator it = buttons.begin();
	while (it != buttons.end()) {
		if (it->inRect(x, y)) {
			it->mouseReleased(x, y, button);
		}
		++it;
	}

}
