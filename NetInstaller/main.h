#pragma once

#if !defined _MAIN
	#define _MAIN
	
	#include "stdafx.h"
	#include "resource.h"
	#include "version.h"

	int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow);
	LRESULT CALLBACK _WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

#endif