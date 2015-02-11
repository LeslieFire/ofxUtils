#pragma once

#include "ofMain.h"

namespace cn_seefeel
{

	//static ofEvent <ofxTimeOut> events;
	class ofxFadeAnimationOver: public ofEventArgs
	{
	public:
	
		bool isTimeOut(){return _timeOut;}
		void timeOut(bool t){_timeOut = t;}
	
		ofxFadeAnimationOver():_timeOut(false){}

		static ofEvent <ofxFadeAnimationOver> events;
	private:
		bool _timeOut;
	};

	class ofxFadeAnimation : public ofThread{

		public:

			ofxFadeAnimation();
			~ofxFadeAnimation();

			void start(ofImage *image, const float time, bool fadein, const int alphaMin = 0, const int alphaMax = 255);
			void reset(const float time, bool fadein, const int alphaMin = 0, const int alphaMax = 255);
			void reset(ofImage *image, const float time, bool fadein, const int alphaMin = 0, const int alphaMax = 255);
			void stop();
			bool IsTimeOut();
			bool IsStart();
			int  getCount();
			ofImage	* getImage();
			void draw();
			void draw(int x, int y, int width, int height);

	protected:
			//--------------------------
			ofImage	*_image;
			void threadedFunction();
			bool _bTimeOut;
			bool _bStarted;

			float count; 
			int	  _alphaMax;
			int	  _alphaMin;
			float	  _alpha;
			bool  _fadeIn;
			float   _alphaStride;
	};

}
namespace cfeel = cn_seefeel;