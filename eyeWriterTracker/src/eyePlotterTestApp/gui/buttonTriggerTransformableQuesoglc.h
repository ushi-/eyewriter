//
//  buttonTriggerTransformableQuesoglc.h
//  RemoteEyeTracker
//
//  Created by Yosuke Ushigome on 8/25/11.
//  Copyright (c) 2011 Yosuke Ushigome. All rights reserved.
//

#ifndef RemoteEyeTracker_buttonTriggerTransformableQuesoglc_h
#define RemoteEyeTracker_buttonTriggerTransformableQuesoglc_h

#include "buttonTransformable.h"
#include "glc.h"

class buttonTriggerTransformableQuesoglc : public buttonTransformable {
	
public:
	
	buttonTriggerTransformableQuesoglc() : buttonTransformable() {
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
//		textHeight = stringMetric[7] - stringMetric[1];
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
	}
	
	void draw(float opacity = 255){
		ofFill();
		
		float pctActive = ofMap(pct, 0.0, maxCount, 0.0, 110.0, true);		
		
		//pctActive = ofClamp(pctActive, 0, 110.0);	
		if( bFlash || editing){
			ofSetColor(0, 100, 240, opacity);
		}else{
			ofSetColor(120 - pctActive, 120+pctActive*2, 120 - pctActive, opacity);
		}
		
		ofRect(x, y, width, height); 
		
		ofNoFill();
		ofSetColor(30, 30, 30, opacity);
		ofRect(x, y, width, height); 
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

	}
	
	void mouseReleased(int x, int y, int button) {
		if (!dragging && !scaling && pressing) {
			// start changing text
			setDisplayText("");
			editing = true;
		}else {
			editing = false;
		}
		pressing = false;
		scaling = false;
		dragging = false;
	}
	
	float textWidth;
	float textHeight;
	
};


#endif
