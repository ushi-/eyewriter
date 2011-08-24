//
//  buttonQuesoglc.h
//  RemoteEyeTracker
//
//  Created by Yosuke Ushigome on 8/25/11.
//  Copyright (c) 2011 Yosuke Ushigome. All rights reserved.
//

#ifndef RemoteEyeTracker_buttonQuesoglc_h
#define RemoteEyeTracker_buttonQuesoglc_h

#include "buttonTransformable.h"
#include "glc.h"

class buttonQuesoglc : public buttonTransformable {
	
public:
	
	buttonQuesoglc() : buttonTransformable() {
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
		numTriggers = 0;
		flashLength = 0.2;
	}
	
	void draw(float opacity = 255){
		ofFill();
		
		float pctActive = ofMap(pct, 0.0, maxCount, 0.0, 110.0, true);		
		
		//pctActive = ofClamp(pctActive, 0, 110.0);	
		if( bFlash){
			ofSetColor(0, 100, 240, opacity);
		}else{
			ofSetColor(120 - pctActive, 120+pctActive*2, 120 - pctActive, opacity);
		}
		
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

//		if (!bHasFont){
//			float textWidth = 8.0f * displayText.length();
//			float remainX = (width - textWidth)/2;
//			
//			float textHeight = 14.0f;
//			float remainY = (height - textHeight)/2.0f + (textHeight/2.0f);
//			
//			ofSetColor(100, 100, 160);
//			ofDrawBitmapString(displayText, x + remainX, y + remainY);
//		} else {
//			ofRectangle bounds = font->getStringBoundingBox(displayText, 0,0);
//			
//			float textWidth = bounds.width;
//			float remainX = (width - textWidth)/2;
//			
//			float textHeight = bounds.height;
//			float remainY = (height - textHeight)/2.0f + (textHeight/2.0f);
//			ofSetColor(60, 60, 60);
//			font->drawString(displayText, x + remainX, y + remainY);
//		}
		
		//ofDrawBitmapString("pctActive is" +ofToString(pct), 200, y);
	}
	
	float textWidth;
	float textHeight;
	
};


#endif
