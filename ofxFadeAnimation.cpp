#include "ofxFadeAnimation.h"
namespace cn_seefeel
{
	ofEvent<ofxFadeAnimationOver> ofxFadeAnimationOver::events;

	ofxFadeAnimation::ofxFadeAnimation(){
		count = -1;
		_bTimeOut = true;
		_bStarted = false;
		_image = NULL;
	}
	ofxFadeAnimation::~ofxFadeAnimation(){
		stop();
	}

	void ofxFadeAnimation::start(ofImage *image, const float time, bool fadein, const int alphaMin, const int alphaMax){
		if (time >= 0 && image != NULL){
			count = time;
			_image = image;

			_alphaMax = alphaMax;
			_alphaMin = alphaMin;

			_fadeIn = fadein;
			_alpha = _fadeIn ? alphaMin : alphaMax;

			_alphaStride = (alphaMax - alphaMin) / count;

			_bTimeOut = false;
			_bStarted = true;
			/*cout << "Count  = " << count
				<< "alpha = " << _alpha
				<< "alpha stride = " << _alphaStride
				<<endl;*/
			startThread(true, false);   // blocking, verbose
		}else{
			ofLogNotice("ofxTimer") << "counter must be greater or equal than zero." ;

		}
	
	}
	void ofxFadeAnimation::reset(ofImage *image, const float time, bool fadein, const int alphaMin, const int alphaMax){
		if (time > 0 && image != NULL){
			if (lock()){
				count = time;
				_image = image;

				_alphaMax = alphaMax;
				_alphaMin = alphaMin;

				_fadeIn = fadein;
				_alpha = _fadeIn ? alphaMin : alphaMax;

				_alphaStride = (alphaMax - alphaMin) / count;

				_bTimeOut = false;
				unlock();
			}
		}else{
			ofLogNotice("ofxTimer") << "counter must be greater than zero." ;
		}
	}
	void ofxFadeAnimation::reset(const float time, bool fadein, const int alphaMin, const int alphaMax){
		reset(_image, time, fadein, alphaMin, alphaMax);
	}

	void ofxFadeAnimation::stop(){
		_bStarted = false;
		stopThread();
	}

	void ofxFadeAnimation::threadedFunction(){

		while( isThreadRunning() != 0 ){
			ofSleepMillis(1 * 60);

			if( lock() ){
				if (!_bTimeOut){
					count = count - 0.06;
					_alpha = (_fadeIn ? (_alpha + 0.06 * _alphaStride) : (_alpha - 0.06 * _alphaStride));
					//cout << "threaded function alpha = " << _alpha <<endl;
					if (count <= 0){
						_bTimeOut = true;
					}
				}
			
				unlock();
			}else{
				cout << "lock failed" <<endl;
			}
		}
	}

	bool ofxFadeAnimation::IsTimeOut(){
		bool bTimeOut = false;
		if (lock()){
			bTimeOut = _bTimeOut;
			unlock();
		}
			
		return bTimeOut;
	}
	bool ofxFadeAnimation::IsStart(){
		bool bStart = false;
		if (lock()){
			bStart = _bStarted;
			unlock();
		}
			
		return bStart;
	}

	int  ofxFadeAnimation::getCount(){
		int c = 0;
		if (lock()){
			c = count;
			unlock();
		}
		return c;
	}

	ofImage	* ofxFadeAnimation::getImage(){
		return _image;
	}
	void ofxFadeAnimation::draw(int x, int y, int width, int height){
		int alpha = 0;

		if (lock()){
			alpha = _alpha;
			unlock();
		}
		ofEnableAlphaBlending();
		ofSetColor(255, 255, 255, alpha);
		_image->draw(x, y, width, height);
		ofSetColor(255, 255, 255, 255);
		ofDisableAlphaBlending();
	}
	void ofxFadeAnimation::draw(){
		draw(0, 0, ofGetWidth(), ofGetHeight());
	}
}