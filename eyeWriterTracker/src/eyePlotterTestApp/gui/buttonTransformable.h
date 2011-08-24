//
//  buttonTransformable.h
//  RemoteEyeTracker
//
//  Created by Yosuke Ushigome on 8/24/11.
//  Copyright (c) 2011 Yosuke Ushigome. All rights reserved.
//

#ifndef BUTTONTRANSFORMABLE_H
#define BUTTONTRANSFORMABLE_H

//#pragma once

#include "ofMain.h"
#include "buttonTrigger.h"

static const int SCALING_EDGE = 30;

class buttonTransformable : public buttonTrigger {
	
public:
	
	buttonTransformable() : buttonTrigger() {
		dragOrigin = ofPoint(0, 0);
		dragging = false;
		pressing = false;
		scaling = false;
	}

	void mousePressed(int xIn, int yIn, int button) {
		pressing = true;
		dragOrigin.x = xIn;
		dragOrigin.y = yIn;
		if (x + width - SCALING_EDGE < xIn &&
			y + height - SCALING_EDGE < yIn) {
			scaling = true;
		}
	}
	
	void mouseDragged(int xIn, int yIn, int button) {
		if (scaling) {
			width += (xIn - dragOrigin.x);
			height += (yIn - dragOrigin.y);
		}else {
			dragging = true;
			x += (xIn - dragOrigin.x);
			y += (yIn - dragOrigin.y);
		}
		dragOrigin.x = xIn;
		dragOrigin.y = yIn;
	}
	
	void mouseReleased(int x, int y, int button) {
		if (!dragging && !scaling && pressing) {
			// start changing text
		}
		pressing = false;
		scaling = false;
		dragging = false;
	}
	
	ofPoint dragOrigin;
	bool dragging;
	bool pressing;
	bool scaling;
};

#endif