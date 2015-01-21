/*
 *  G:\leslie\01github\ofxUtils\ofxButtons.h
 *
 *  Created by Leslie Yang on 2015-01-21
 *
 *
 *  Copyright 2015 https://github.com/LeslieFire All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the author nor the names of its contributors
 *       may be used to endorse or promote products derived from this software
 *       without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 *  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 *  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 *  OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 *  OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 *  OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 *  OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *  ************************************************************************************ */ 
#pragma once

#include "ofxSimpleGuiToo.h"
#include "ofMain.h"

namespace cn_seefeel{

enum myButtons{
	BUTTON1 = 0,
	BUTTON2,
	BUTTON3,
	BUTTON4,
	BUTTON5,
	BUTTON6,
	BUTTON7,
	BUTTON8,
	BUTTON9,
	BUTTON10,
	BUTTON11,
	BUTTON12,
	BUTTON13,
	BUTTON14,
	BUTTON15
};

class button{

public:

	button():_pos(ofPoint(0, 0, 0)), 
		_enabled(true), _id(0){
			_img[0] = NULL;
			_img[1] = NULL; 

	}

	ofImage		*_img[2];	// two state
	
	ofPoint		_pos;
	bool		_enabled;

	int			_id;
	string		_title;
};

class ofxButtons
{
public:
	
	ofxButtons(void);
	virtual ~ofxButtons(void);

	void mousePressed(ofMouseEventArgs &e);
	void mouseReleased(ofMouseEventArgs &e);

	void addListener();
	void removeListener();

	/*
	* set position configure page
	*/
	void setup(const string & name);

	// used for button pressed check
	/*
	-1 : no button pressed
	 0 : button1  pressed
	 1 : button2  pressed
	 ... ... 
	*/
	int update(ofPixelsRef pixels);

	// used for openNI hand
	void setPosition(const int& btnName, const ofPoint &pos);

	void draw();
	void draw(int btnId);

	ofRectangle getButtonArea(int btnId);
	void changeButtonState(int btnId);

	void SetButton(const int &name, ofImage *b, int id = 0);
	map<int,button> &buttons(){return _buttons;}

protected:
	int countNoneZeroPixelIn(ofRectangle &rect, ofPixelsRef pixels);
private:
	map<int, button> _buttons;

	bool _bCentered;
};

}

namespace cfeel = cn_seefeel;