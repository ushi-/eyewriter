//
//  buttonImage.h
//  RemoteEyeTracker
//
//  Created by Yosuke Ushigome on 8/29/11.
//  Copyright (c) 2011 Yosuke Ushigome. All rights reserved.
//

#ifndef RemoteEyeTracker_buttonImage_h
#define RemoteEyeTracker_buttonImage_h

#include "ofMain.h"
#include "buttonRect.h"

class buttonImage : public buttonRect {
public:
	
	buttonImage():buttonRect() {
	}
	
	virtual void setup( string imgName, float xIn, float yIn, float w, float h ){
		x		= xIn;
		y		= yIn;
		width	= w;
		height	= h;
		img.loadImage(imgName);
	}
	
	void draw(float opacity = 255){
		ofEnableAlphaBlending();
		float w = img.getWidth();
		float h = img.getHeight();
		img.draw(x + width/2.0 - w/2.0, y + height/2.0 - h/2.0);
		ofDisableAlphaBlending();
	}
	
	ofImage img;
};

#endif
