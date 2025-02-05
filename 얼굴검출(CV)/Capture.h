//-----------------------------------------------------
// Template matching-based face detector
// Programmed by Heung-Soo Kim
// Version 1.1 (2005.12.15)
//-----------------------------------------------------

#if !defined (CAPTURE_INCLUDED_)
#define CAPTURE_INCLUDED_

#define ENABLE_VIDEOFRAME_CALLBACKS 1
#define FNWCALLBACK CALLBACK

extern DWORD gdwFrameNum;
extern LPBYTE glpData;

LRESULT FNWCALLBACK FrameCallbackProc(HWND, LPVIDEOHDR);
LRESULT FNWCALLBACK VideoCallbackProc(HWND, LPVIDEOHDR);

#endif