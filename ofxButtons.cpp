/*
 *  ofxButtons.cpp
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

	map<int, button>::iterator it = _buttons.begin();
	map<int, button>::iterator itend = _buttons.end();

	for (; it != itend; ++it){
		// draw every enabled buttons
		if(it->second._enabled){
			it->second._img[it->second._id]->draw(it->second._pos.x, it->second._pos.y);
		}
	}
}

void ofxButtons::draw(int btnId){
	//ofEnableAlphaBlending();
	map<int, button>::iterator it = _buttons.find(btnId);
	ofSetRectMode(OF_RECTMODE_CENTER);
	if (it != _buttons.end()){
		it->second._img[it->second._id]->draw(it->second._pos.x, it->second._pos.y);
	}
	ofSetRectMode(OF_RECTMODE_CORNER);
	//ofDisableAlphaBlending();
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

// namespace }
}

