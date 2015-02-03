#pragma once
#include "ofxButtons.h"
#include "ofxTexturesAdv.h"
#include "ofxSimpleGuiToo.h"

namespace cn_seefeel{

	class ofxTextureButtons :public ofxButtons
	{
	public:
		ofxTextureButtons(void);
		~ofxTextureButtons(void);
		/*
		* set position configure page
		*/
		void setup(const string & name);
		void update();
		int  touch(ofPoint loc);
		void draw();

		ofRectangle getButtonArea(int btnId);

		void SetButton(const int btnId, string filename);
	private:
		map<int, ofxTexturesAdv>	_buttons;
	};

}