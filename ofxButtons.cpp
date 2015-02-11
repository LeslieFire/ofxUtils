#include "ofxButtons.h"
namespace cn_seefeel{
//--------------------------------class ofxButtons -----------------------
ofxButtons::ofxButtons(void)
{
	//void addListener();

	_bCentered = false;
}


ofxButtons::~ofxButtons(void)
{
	//void removeListener();
}

void ofxButtons::setup(const string & name){
	ofLogNotice() << "ofxButton::Setup of " + name; 

	gui.addPage(name).setXMLName(name + ".xml");
	gui.addTitle("Buttons");

	map<int, button>::iterator it = _buttons.begin();
	map<int, button>::iterator itend = _buttons.end();

	for ( ; it != itend; ++it){
		gui.addSlider(ofToString(it->first) + " X ", it->second._pos.x, 0, ofGetWidth());
		gui.addSlider(ofToString(it->first) + " Y ", it->second._pos.y, 0, ofGetHeight());
	}

	gui.loadFromXML();
	gui.setDefaultKeys(true);
}

void ofxButtons::setPosition(const int& btnName, const ofPoint &pos){

	map<int, button>::iterator it = _buttons.find(btnName);
	if (it != _buttons.end()){
		if (ofDist(it->second._pos.x, it->second._pos.y, pos.x, pos.y)>20){
			it->second._pos = pos;
		}
	}else{
		ofLogVerbose() << "Not found button : " + btnName;
	}
}

void ofxButtons::SetButton(const int &name, ofImage *b, int id){
	ofLogNotice() << "ofxButton::Set Button : " + ofToString(name);
	_buttons[name]._img[id] = b;
}

void ofxButtons::draw(){
	ofEnableAlphaBlending();
	map<int, button>::iterator it = _buttons.begin();
	map<int, button>::iterator itend = _buttons.end();

	for (; it != itend; ++it){
		// draw every enabled buttons
		if(it->second._enabled){
			it->second._img[it->second._id]->draw(it->second._pos.x, it->second._pos.y);
		}
	}
	ofDisableAlphaBlending();
}

void ofxButtons::draw(int btnId){
	ofEnableAlphaBlending();
	map<int, button>::iterator it = _buttons.find(btnId);
	
	if (it != _buttons.end()){
		it->second._img[it->second._id]->draw(it->second._pos.x, it->second._pos.y);
	}

	ofDisableAlphaBlending();
}
ofPoint ofxButtons::getButtonPos(int btnId){
	map<int, button>::iterator it = _buttons.find(btnId);
	return it->second._pos;
}
ofRectangle ofxButtons::getButtonArea(int btnId){
	return ofRectangle(_buttons[btnId]._pos.x, 
					   _buttons[btnId]._pos.y,
					   _buttons[btnId]._img[_buttons[btnId]._id]->getWidth(),
					   _buttons[btnId]._img[_buttons[btnId]._id]->getHeight());
}

void ofxButtons::changeButtonState(int btnId){
	_buttons[btnId]._id  = (_buttons[btnId]._id + 1) % 2;
}


void ofxButtons::mousePressed(ofMouseEventArgs &e)
{
}
void ofxButtons::mouseReleased(ofMouseEventArgs &e){
	
}

void ofxButtons::addListener()
{
	ofAddListener(ofEvents().mousePressed, this, &ofxButtons::mousePressed);
	ofAddListener(ofEvents().mouseReleased, this, &ofxButtons::mouseReleased);
}
void ofxButtons::removeListener()
{
	ofRemoveListener(ofEvents().mousePressed, this, &ofxButtons::mousePressed);
	ofRemoveListener(ofEvents().mouseReleased, this, &ofxButtons::mouseReleased);
}


int ofxButtons::update(ofPixelsRef pixels){
	float ratioX = (float)pixels.getWidth() / ofGetWidth();
	float ratioY = (float)pixels.getHeight() / ofGetHeight();

	map<int, button>::iterator it = _buttons.begin();
	map<int, button>::iterator itend = _buttons.end();
	for (; it != itend; ++it){
		ofRectangle rect = getButtonArea(it->first);

		rect.x = rect.x*ratioX;
		rect.y = rect.y*ratioY;
		rect.scaleWidth(ratioX);
		rect.scaleHeight(ratioY);
		int counts = countNoneZeroPixelIn(rect, pixels);
		if (counts > 50){
			return (int)it->first;
		}
	}

	return -1;
}

int ofxButtons::countNoneZeroPixelIn(ofRectangle &rect, ofPixelsRef pixels)
{
	int count = 0;
	for (int x = rect.x; x < rect.x + rect.width; ++x){
		for (int y = rect.y; y < rect.y + rect.height; ++y){
			if (x < pixels.getWidth() && y < pixels.getHeight())
			if (pixels.getColor(x, y).r > 200){
				count++;
			}
		}
	}
	return count;
}

int ofxButtons::update(ofPoint loc){
	map<int, button>::iterator it = _buttons.begin();
	map<int, button>::iterator itend = _buttons.end();
	for (; it != itend; ++it){
		if(isInRange(loc, getButtonArea(it->first))){
			return (int)it->first;
		}

	}

	return -1;
}

bool ofxButtons::isInRange(int x, int y, ofRectangle & t){
	if ( ofInRange(x, t.getMinX(), t.getMaxX())
		&& ofInRange(y, t.getMinY(), t.getMaxY())){
			return true;
	}
	return false;
}

bool ofxButtons::isInRange(ofPoint loc, ofRectangle & t){
	if ( ofInRange(loc.x, t.getMinX(), t.getMaxX())
		&& ofInRange(loc.y, t.getMinY(), t.getMaxY())){
			return true;
	}
	return false;
}
// namespace }
}

