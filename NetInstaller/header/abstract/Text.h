#pragma once
#if !defined _USERCONTROL_TEXT
	#define _USERCONTROL_TEXT

	#include "Control.h"

	class Text : public Control {

		protected:
			unsigned int lines;
			bool readOnly;
			bool full;

		public:

			static const int EVENT_FOCUS = 256;
			static const int EVENT_BLUR = 512;
			static const int EVENT_CHANGE = 768;
			static const int EVENT_FREE = 1024;
			static const int EVENT_LIMIT = 1281;
				
			Text();

			LRESULT onCreate(HWND parent, HINSTANCE hInst);
			LRESULT onCommand(int index, int wmEvent, WPARAM wParam, LPARAM lParam);

			std::string getText();
			int getLength();
			void setText(std::string text);
			void setText(char* text);
			void setReadOnly(bool readOnly);
			void setLines(unsigned int lines);
			unsigned int getLines();
			void toggleEnabled();
			bool isFull();
			bool isEmpty();
			bool isReadOnly();

			void onChange();
			void onBlur();
			void onFocus();
			void onFree();
			void onLimit();
	};

#endif