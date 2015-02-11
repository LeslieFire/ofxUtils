#include "ofxTimer.h"
namespace cn_seefeel
{
	ofEvent<ofxTimeOut> ofxTimeOut::events;

	ofxTimer::ofxTimer(){
		count = -1;
		_bTimeOut = true;
	}
	ofxTimer::~ofxTimer(){
		stop();
	}

	void ofxTimer::start(const float & c){
		if (c >= 0){
			count = c;
			_bTimeOut = false;

			startThread(true, false);   // blocking, verbose
		}else{
			ofLogNotice("ofxTimer") << "counter must be greater or equal than zero." ;
		}
	
	}
	void ofxTimer::reset(const float & c){
		if (c > 0){
			if (lock()){
				count = c;
				_bTimeOut = false;
				unlock();
			}
		}else{
			ofLogNotice("ofxTimer") << "counter must be greater than zero." ;
		}
	}

	void ofxTimer::stop(){
		stopThread();
	}

	void ofxTimer::threadedFunction(){

		while( isThreadRunning() != 0 ){
			ofSleepMillis(1 * 60);

			if( lock() ){
				if (!_bTimeOut){
					count = count - 0.06;
					
					if (count <= 0){
						_bTimeOut = true;
					}
				}
			
				unlock();
			}
		}
	}

	bool ofxTimer::IsTimeOut(){
		bool bTimeOut = false;
		if (lock()){
			bTimeOut = _bTimeOut;
			unlock();
		}
			
		return bTimeOut;
	}
	float  ofxTimer::getCount(){
		float c = 0;
		if (lock()){
			c = count;
			unlock();
		}
		return c;
	}
}