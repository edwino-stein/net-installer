#pragma once
#if !defined _USERCONTROL_BUTTON
	#define _USERCONTROL_BUTTON

	#include "Control.h"

	class Button : public Control {

		protected:
			bool dfaut;

		public:

			Button();
			virtual void onClick() = 0;
			LRESULT onCreate(HWND parent, HINSTANCE hInst);
			LRESULT onCommand(int index, int wmEvent, WPARAM wParam, LPARAM lParam);
			void toggleEnabled();

			void setText(std::string text);
			void setText(char* text);
			void setDefault(bool dfault);
	};

#endif