#pragma once

#include "ofMain.h"

// this is not a very exciting example yet
// but ofThread provides the basis for ofNetwork and other
// operations that require threading.
//
// please be careful - threading problems are notoriously hard
// to debug and working with threads can be quite difficult


namespace seefeel
{

//static ofEvent <ofxTimeOut> events;
class ofxTimeOut: public ofEventArgs
{
public:
	
	bool isTimeOut(){return _timeOut;}
	void timeOut(bool t){_timeOut = t;}
	
	ofxTimeOut():_timeOut(false){}

	static ofEvent <ofxTimeOut> events;
private:
	bool _timeOut;
};

class Timer : public ofThread{

	public:

		Timer();
		~Timer();

		void start(const int & c);
		void reset(const int & c);
        void stop();
		bool IsTimeOut();

protected:
		//--------------------------
		void threadedFunction();
		bool _bTimeOut;
		int count;  // threaded fucntions that share data need to use lock (mutex)
	                // and unlock in order to write to that data
	                // otherwise it's possible to get crashes.
	                //
	                // also no opengl specific stuff will work in a thread...
	                // threads can't create textures, or draw stuff on the screen
	                // since opengl is single thread safe

};

}

namespace cfeel = seefeel;