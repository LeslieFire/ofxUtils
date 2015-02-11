#ifndef _WIN_UTILS
#define _WIN_UTILS

#include "ofMain.h"
static string	windowTitle;
static int		storedWindowX;
static int		storedWindowY;
static int		storedWindowW;
static int		storedWindowH;
static bool		bCustomFullscreen = false;
//--------------------------------------
static void ofHideWindow()
{
    #ifdef TARGET_WIN32
        HWND  m_hWnd = WindowFromDC(wglGetCurrentDC());
        ShowWindow(m_hWnd,HIDE_WINDOW);
	#endif
}
//--------------------------------------
static void ofShowWindow()
{
    #ifdef TARGET_WIN32
        HWND  m_hWnd = WindowFromDC(wglGetCurrentDC());
        ShowWindow(m_hWnd,1);
	#endif
}
//--------------------------------------
static void ofBeginCustomFullscreen(int x, int y, int width, int height){

	if (ofGetWindowMode() == OF_GAME_MODE) return;
    #ifdef TARGET_WIN32
        HWND  m_hWnd = WindowFromDC(wglGetCurrentDC());
        long windowStyle = GetWindowLong(m_hWnd, GWL_STYLE);
        windowStyle &= ~WS_OVERLAPPEDWINDOW;
        windowStyle |= WS_POPUP;
        SetWindowLong(m_hWnd, GWL_STYLE, windowStyle);
        SetWindowPos(m_hWnd, HWND_TOP, x, y, width, height, SWP_FRAMECHANGED);
        bCustomFullscreen = true;
	#endif
}

//--------------------------------------
static void  ofEndCustomFullscreen(){

	if (ofGetWindowMode() == OF_GAME_MODE) return;
	#ifdef TARGET_WIN32
		if(bCustomFullscreen){
		    HWND  m_hWnd = WindowFromDC(wglGetCurrentDC());
		    long windowStyle = GetWindowLong(m_hWnd, GWL_STYLE);
			windowStyle  |= WS_OVERLAPPEDWINDOW;
		    windowStyle  &= ~WS_POPUP;
			SetWindowLong(m_hWnd, GWL_STYLE, windowStyle);
			SetWindowPos(m_hWnd, HWND_TOP,storedWindowX, storedWindowY, storedWindowW, storedWindowH, SWP_FRAMECHANGED);
			bCustomFullscreen = false;
		}
	#endif
}

#endif

