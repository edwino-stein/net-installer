#include "stdafx.h"
#include "header\WinMain.h"

//Espelho para WinMain::tMain
int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {
	return WinMain::getInstance()->tMain(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
}

//Espelho para WinMain::WndProc
LRESULT CALLBACK _WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	return WinMain::getInstance()->WndProc(hWnd, message, wParam, lParam);
}
