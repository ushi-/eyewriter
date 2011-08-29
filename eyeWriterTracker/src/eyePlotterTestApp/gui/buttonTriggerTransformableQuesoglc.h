//
//  buttonTriggerTransformableQuesoglc.h
//  RemoteEyeTracker
//
//  Created by Yosuke Ushigome on 8/25/11.
//  Copyright (c) 2011 Yosuke Ushigome. All rights reserved.
//

#ifndef RemoteEyeTracker_buttonTriggerTransformableQuesoglc_h
#define RemoteEyeTracker_buttonTriggerTransformableQuesoglc_h

#include "buttonTrigger.h"
#include "glc.h"

static const int SCALING_EDGE = 24;

enum {
	buttonStateNone = 0,
	buttonStateOnMouse,
	buttonStateDragging,
	buttonStateScaling,
	buttonStateEditing,
	buttonStateRemoving,
	buttonStateRecording
};


class buttonTriggerTransformableQuesoglc : public buttonTrigger {
	
public:
	
	buttonTriggerTransformableQuesoglc() : buttonTrigger() {
		dragOrigin = ofPoint(0, 0);
		state = buttonStateNone;
		textWidth = 0;
		textHeight = 0;
	}

	void setDisplayText (string onName) {
		displayText = onName;
		
		float stringMetric[8];
		if (glcMeasureString(false, displayText.c_str())) {
			glcGetStringMetric(GLC_BOUNDS, stringMetric);
		}
		textWidth = stringMetric[4] - stringMetric[6];
		textHeight = 1;
	}
	
	virtual void setup( string onName, float xIn, float yIn, float w, float h ){
		setDisplayText(onName);
		
		x		= xIn;
		y		= yIn;
		width	= w;
		height	= h;
		numTriggers = 0;
		flashLength = 0.2;
		imgRemove.loadImage("images/remove.png");
	}
	
	void draw(float opacity = 255){
		ofFill();
		
		float pctActive = ofMap(pct, 0.0, maxCount, 0.0, 110.0, true);		
		
		//pctActive = ofClamp(pctActive, 0, 110.0);	
		if( bFlash || state == buttonStateEditing){
			ofSetColor(0, 100, 240, opacity);
		}else{
			ofSetColor(120 - pctActive, 120+pctActive*2, 120 - pctActive, opacity);
		}
		
		ofRect(x, y, width, height); 

		
		ofNoFill();
		ofSetColor(30, 30, 30, opacity);
		ofRect(x, y, width, height); 
		ofSetLineWidth(2.0);
		ofLine(x+width-SCALING_EDGE, y+height-4, x+width - 4, y+height-SCALING_EDGE);
		ofLine(x+width-SCALING_EDGE+8, y+height-4, x+width - 4, y+height-SCALING_EDGE+8);
		ofLine(x+width-SCALING_EDGE+16, y+height-4, x+width - 4, y+height-SCALING_EDGE+16);

		glEnable(GL_TEXTURE_2D);
		glPushMatrix();
		glTranslatef(x+width/2.0, y+height/2.0, 0);
		glScalef(32, -32, 1);
		glTranslatef(-textWidth/2.0, -textHeight/2.0, 0);
		glcRenderString(displayText.c_str());
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);

		ofEnableAlphaBlending();
		imgRemove.draw(x, y);
		ofDisableAlphaBlending();
	}
	
	void mousePressed(int xIn, int yIn, int button) {
		if (inRect(xIn, yIn)) {
			state = buttonStateOnMouse;
			dragOrigin.x = xIn;
			dragOrigin.y = yIn;
			if (x + width - SCALING_EDGE < xIn &&
				y + height - SCALING_EDGE < yIn) {
				state = buttonStateScaling;
			}
		}else {
			state = buttonStateNone;
		}
	}
	
	void mouseDragged(int xIn, int yIn, int button) {
		if (state == buttonStateScaling) {
			width += (xIn - dragOrigin.x);
			height += (yIn - dragOrigin.y);
			dragOrigin.x = xIn;
			dragOrigin.y = yIn;
		}else if (state == buttonStateOnMouse || state == buttonStateDragging) {
			state = buttonStateDragging;
			x += (xIn - dragOrigin.x);
			y += (yIn - dragOrigin.y);
			dragOrigin.x = xIn;
			dragOrigin.y = yIn;
		}
	}
	
	void mouseReleased(int xIn, int yIn, int button) {
		switch(state) {
			case buttonStateDragging:
			case buttonStateScaling:
				state = buttonStateNone;
				break;
			case buttonStateOnMouse:
				if (x <= xIn && xIn <= x+32 &&
					y <= yIn && yIn <= y+32){
					state = buttonStateRemoving;
				}else {
					state = buttonStateEditing;
				}
				break;
		}
	}
	
	ofPoint dragOrigin;
	int state;
	float textWidth;
	float textHeight;
	ofImage imgRemove;
};


#endif
