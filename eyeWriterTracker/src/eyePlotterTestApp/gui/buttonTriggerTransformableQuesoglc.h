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
	buttonStateRecordStarted,
	buttonStateRecordStopped
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
		textHeight = -0.8;
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
		imgRecord.loadImage("images/record.png");
		imgRecordStop.loadImage("images/recordStop.png");
	}
	
	void draw(float opacity = 255){
		ofFill();
		
		float pctActive = ofMap(pct, 0.0, maxCount, 0.0, 110.0, true);		
		
		//pctActive = ofClamp(pctActive, 0, 110.0);	
		if( bFlash ){
			ofSetColor(0, 100, 240, opacity);
		}else if (state == buttonStateEditing) {
			ofSetColor(20, 220, 20, opacity);
		}else if (state == buttonStateRecordStarted) {
			ofSetColor(20, 220, 20
					   
					   );
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
		if (state == buttonStateRecordStarted) {
			imgRecordStop.draw(x+width/2.0-imgRecordStop.getWidth()/2.0, y+height/2.0+8);
		}else {
			imgRecord.draw(x+width/2.0-imgRecord.getWidth()/2.0, y+height/2.0+8);
		}
		ofDisableAlphaBlending();
	}
	
	void mousePressed(int xIn, int yIn, int button) {
		if (inRect(xIn, yIn)) {
			if (state == buttonStateRecordStarted) {
				return;
			}
			state = buttonStateOnMouse;
			dragOrigin.x = xIn;
			dragOrigin.y = yIn;
			if (x + width - SCALING_EDGE < xIn &&
				y + height - SCALING_EDGE < yIn) {
				state = buttonStateScaling;
			}
		}else {
			if (state == buttonStateRecordStarted) {
				state = buttonStateRecordStopped;
			}else {
				state = buttonStateNone;
			}
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
		float recordOriginX = x+width/2.0-imgRecord.getWidth()/2.0;
		float recordOriginY = y + height/2.0 + 8;
		switch(state) {
			case buttonStateDragging:
			case buttonStateScaling:
				state = buttonStateNone;
				break;
			case buttonStateOnMouse:
			{
				if (x <= xIn && xIn <= x+32 &&
					y <= yIn && yIn <= y+32){
					state = buttonStateRemoving;
				}else if (recordOriginX < xIn && xIn < recordOriginX + imgRecord.getWidth() &&
						  recordOriginY < yIn && yIn < recordOriginY + imgRecord.getHeight()) {
					state = buttonStateRecordStarted;
				}else {
					state = buttonStateEditing;
				}
				break;
			}
			case buttonStateRecordStarted:
				if (recordOriginX < xIn && xIn < recordOriginX + imgRecord.getWidth() &&
					recordOriginY < yIn && yIn < recordOriginY + imgRecord.getHeight()) {
					state = buttonStateRecordStopped;
				}
				break;
		}
	}
	
	ofPoint dragOrigin;
	int state;
	float textWidth;
	float textHeight;
	ofImage imgRemove;
	ofImage imgRecord;
	ofImage imgRecordStop;
	buttonRect rectRecord;
};


#endif
