//-----------------------------------------------------
// Template matching-based face detector
// Programmed by Heung-Soo Kim
// Version 1.1 (2005.12.15)
//-----------------------------------------------------

#include <stdafx.h>
#include <vfw.h>
#include <memory.h>

#include "capture.h"

DWORD gdwFrameNum;
LPBYTE glpData;

LRESULT FNWCALLBACK FrameCallbackProc(HWND hWnd, LPVIDEOHDR lpVHdr)
{
	gdwFrameNum++;
	glpData = lpVHdr->lpData; // ĸ�ĵ� �������� ������ �Ѱ��ֱ�

	return (LRESULT) TRUE;
}

LRESULT FNWCALLBACK VideoCallbackProc(HWND hWnd, LPVIDEOHDR lpVHdr)
{
	return (LRESULT) TRUE;
}
