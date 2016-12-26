#pragma once

#if !defined _USERCONTROL_LABEL
	#define _USERCONTROL_LABEL

	#include "Control.h"

	class Label : public Control {

		public:

			Label();
			LRESULT onCreate(HWND parent, HINSTANCE hInst);

			/*
			TODO: Verificar como capturar os eventos
			*/
			LRESULT onCommand(int index, int wmEvent, WPARAM wParam, LPARAM lParam);

			/*
			TODO: Implementar o toggleEnabled
			*/
			void toggleEnabled();
			
			/*
			TODO: Implementar o getText
			*/
			void setText(std::string text);
			void setText(char* text);
	};

#endif