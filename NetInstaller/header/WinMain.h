/*
Controller da janaela principal

TODO: Separar interface da implementação
*/

#if !defined _WIN_MAIN
#define _WIN_MAIN

	#include "../stdafx.h"
	#include "../main.h"
	#include "ViewControls.h"

	#define MAX_LOADSTRING 100
	#define INIT_WIDTH 258
	#define INIT_HEIGHT 468

	class WinMain {
		private:

			//Definições Singleton
			WinMain(WinMain const&);
			void operator=(WinMain const&);

			//Contrutor
			WinMain();
			
			ControlsStore *controls;

			HINSTANCE hInst;								// current instance
			HWND hWnd;										// Handle da janela
			TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
			TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

			//ControlsStore *controls;						//Controls

			int width;
			int height;

			/*
			Callback para quando a janela é criada
			*/
			LRESULT onCreate(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

			/*
			Callback de eventos dos itens da janela
			*/
			LRESULT onCommand(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

			/*
			Callback para redesenhar a janela
			*/
			LRESULT onPaint(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

		public:

			/**
			* Metodo estatico para recupar a instancia singleton da classe
			*/
			static WinMain* getInstance() {
				static WinMain *instance = new WinMain;
				return instance;
			}
				

			ControlsStore *getControlsStore();

			std::string loadString(int resourceId);

			/**
			* Metodo EntryPoint da aplicação
			*/
			int tMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow);

			/**
			*  FUNCTION: registerClass()
			*
			*  PURPOSE: Registers the window class.
			*
			*  COMMENTS:
			*
			*    This function and its usage are only necessary if you want this code
			*    to be compatible with Win32 systems prior to the 'RegisterClassEx'
			*    function that was added to Windows 95. It is important to call this function
			*    so that the application will get 'well formed' small icons associated
			*    with it.
			*/
			ATOM registerClass(HINSTANCE hInstance);


			/**
			*   FUNCTION: initWin32Instance(HINSTANCE, int)
			*
			*   PURPOSE: Saves instance handle and creates main window
			*
			*   COMMENTS:
			*
			*        In this function, we save the instance handle in a global variable and
			*        create and display the main program window.
			*/
			BOOL initWin32Instance(HINSTANCE hInstance, int nCmdShow);

			/**
			*  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
			*
			*  PURPOSE:  Processes messages for the main window.
			*
			*  WM_COMMAND	- process the application menu
			*  WM_PAINT	- Paint the main window
			*  WM_DESTROY	- post a quit message and return
			*
			*/
			LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

			/**
			* Getter para hInstance da janela principal
			*/
			HINSTANCE getHandleInstance();


			/**
			* Getter para hWnd da janela principal
			*/
			HWND getWindowHandle();
	};

#endif