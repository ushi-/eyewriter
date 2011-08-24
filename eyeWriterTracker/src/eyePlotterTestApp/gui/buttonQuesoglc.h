//
//  buttonQuesoglc.h
//  RemoteEyeTracker
//
//  Created by Yosuke Ushigome on 8/25/11.
//  Copyright (c) 2011 Yosuke Ushigome. All rights reserved.
//

#ifndef RemoteEyeTracker_buttonQuesoglc_h
#define RemoteEyeTracker_buttonQuesoglc_h

#include "ofMain.h"
#include "buttonRect.h"
#include "glc.h"

class buttonQuesoglc : public buttonRect {
public:
	
	buttonQuesoglc():buttonRect() {
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
		textHeight = stringMetric[7] - stringMetric[1];
	}

	virtual void setup( string onName, float xIn, float yIn, float w, float h ){
		setDisplayText(onName);
		
		x		= xIn;
		y		= yIn;
		width	= w;
		height	= h;
	}
	
	void draw(float opacity = 255){
		ofFill();
		ofSetColor(120, 120, 120, opacity);		
		ofRect(x, y, width, height); 
		
		ofNoFill();
		ofSetColor(30, 30, 30, opacity);
		ofRect(x, y, width, height); 
		
		
		glEnable(GL_TEXTURE_2D);
		glPushMatrix();
		glTranslatef(x+width/2.0, y+height/2.0, 0);
		glScalef(32, -32, 1);
		glTranslatef(-textWidth/2.0, -textHeight/2.0, 0);
		glcRenderString(displayText.c_str());
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
	}

	float textWidth;
	float textHeight;
	string displayText;
};

#endif
