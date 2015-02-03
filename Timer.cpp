#include "Timer.h"
namespace seefeel
{
ofEvent<ofxTimeOut> ofxTimeOut::events;

Timer::Timer(){
	count = -1;
	_bTimeOut = true;
}
Timer::~Timer(){
	stop();
}

void Timer::start(const int & c){
	if (c > 0){
		count = c;
		_bTimeOut = false;

		startThread(true, false);   // blocking, verbose
	}else{
		ofLogNotice("Timer") << "counter must be greater than zero." ;
	}
	
}
void Timer::reset(const int & c){
	if (c > 0){
		if (lock()){
			count = c;
			_bTimeOut = false;
			unlock();
		}
	}else{
		ofLogNotice("Timer") << "counter must be greater than zero." ;
	}
}

void Timer::stop(){
    stopThread();
}

void Timer::threadedFunction(){

	while( isThreadRunning() != 0 ){
		ofSleepMillis(1 * 1000);

		if( lock() ){
			if (!_bTimeOut){
				count--;
					
				if (count == 0){
					_bTimeOut = true;
				}
			}
			
			unlock();
		}
	}
}

bool Timer::IsTimeOut(){
	bool bTimeOut = false;
	if (lock()){
		bTimeOut = _bTimeOut;
		unlock();
	}
			
	return bTimeOut;
}

}