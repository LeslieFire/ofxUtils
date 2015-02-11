#pragma once

#include "ofMain.h"

// this is not a very exciting example yet
// but ofThread provides the basis for ofNetwork and other
// operations that require threading.
//
// please be careful - threading problems are notoriously hard
// to debug and working with threads can be quite difficult


namespace cn_seefeel
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

	class ofxTimer : public ofThread{

		public:

			ofxTimer();
			~ofxTimer();

			void start(const float & c);
			void reset(const float & c);
			void stop();
			bool IsTimeOut();
			float  getCount();

	protected:
			//--------------------------
			void threadedFunction();
			bool _bTimeOut;
			float count;  // threaded fucntions that share data need to use lock (mutex)
						// and unlock in order to write to that data
						// otherwise it's possible to get crashes.
						//
						// also no opengl specific stuff will work in a thread...
						// threads can't create textures, or draw stuff on the screen
						// since opengl is single thread safe

	};

}
namespace cfeel = cn_seefeel;