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
	BUTTON15,
	BUTTON16,
	BUTTON17,
	BUTTON18,
	BUTTON19,
	BUTTON20,
	BUTTON21
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
	virtual void setup(const string & name);

	// used for button pressed check
	/*
	-1 : no button pressed
	 0 : button1  pressed
	 1 : button2  pressed
	 ... ... 
	*/
	int update(ofPixelsRef pixels);
	int update(ofPoint loc);

	// used for openNI hand
	void setPosition(const int& btnName, const ofPoint &pos);

	void draw();
	void draw(int btnId);

	ofRectangle getButtonArea(int btnId);
	ofPoint		getButtonPos(int btnId);
	void		changeButtonState(int btnId);

	virtual void SetButton(const int &name, ofImage *b, int id = 0);
	map<int,button> &buttons(){return _buttons;}

protected:
	int countNoneZeroPixelIn(ofRectangle &rect, ofPixelsRef pixels);
	bool isInRange(int x, int y, ofRectangle & t);
	bool isInRange(ofPoint loc, ofRectangle & t);
private:
	map<int, button> _buttons;

	bool _bCentered;
};

}
namespace cfeel = cn_seefeel;
