#include "ofxTextureButtons.h"

namespace cn_seefeel{
	ofxTextureButtons::ofxTextureButtons(void)
	{
	}


	ofxTextureButtons::~ofxTextureButtons(void)
	{
	}

	void ofxTextureButtons::setup(const string & name){

		ofDirectory dir;
		int number = dir.listDir(name);

		for (int i = 0; i < number; ++i){
			SetButton(i, dir.getPath(i));
		}
		//ofLogNotice() << "ofxButton::Setup of " + name; 

		gui.addPage(name).setXMLName(name + ".xml");
		gui.addTitle("Buttons");

		map<int, ofxTexturesAdv>::iterator it = _buttons.begin();
		map<int, ofxTexturesAdv>::iterator itend = _buttons.end();

		for ( ; it != itend; ++it){
			gui.addSlider(ofToString(it->first) + " X ", it->second.m_Position.x, 0, ofGetWidth());
			gui.addSlider(ofToString(it->first) + " Y ", it->second.m_Position.y, 0, ofGetHeight());
		}

		gui.loadFromXML();
		gui.setDefaultKeys(true);
	}

	void ofxTextureButtons::SetButton(const int btnId, string dirname){
		_buttons[btnId].setup(dirname);
	}
	void ofxTextureButtons::update(){
		map<int, ofxTexturesAdv>::iterator it = _buttons.begin();
		map<int, ofxTexturesAdv>::iterator itend = _buttons.end();
		for ( ; it != itend; ++it){
			it->second.update();
		}
	}
	int  ofxTextureButtons::touch(ofPoint loc){
		int btnId = -1;
		map<int, ofxTexturesAdv>::iterator it = _buttons.begin();
		map<int, ofxTexturesAdv>::iterator itend = _buttons.end();
		for ( ; it != itend; ++it){
			if (isInRange(loc, getButtonArea(it->first))){
				btnId = it->first;
				break;
			}
		}
		return btnId;
	}

	void ofxTextureButtons::draw(){
		map<int, ofxTexturesAdv>::iterator it = _buttons.begin();
		map<int, ofxTexturesAdv>::iterator itend = _buttons.end();
		for ( ; it != itend; ++it){
			it->second.draw();
		}
	}
	ofRectangle ofxTextureButtons::getButtonArea(int btnId){
		return ofRectangle(_buttons[btnId].GetPosition().x - _buttons[btnId].getWidth()/2, 
			_buttons[btnId].GetPosition().y - _buttons[btnId].getHeight()/2, 
			_buttons[btnId].getWidth(), 
			_buttons[btnId].getHeight());
	}
}