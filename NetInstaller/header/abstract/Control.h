#pragma once

#if !defined _USERCONTROL
	#define _USERCONTROL

	#include "../../stdafx.h"
	#include "../util/Conversions.h"

	#define FONT_WEIGHT_LIGHTER 300
	#define FONT_WEIGHT_LIGHT 300
	#define FONT_WEIGHT_NORMAL 400
	#define FONT_WEIGHT_SEMIBOLD 600
	#define FONT_WEIGHT_BOLD 700
	#define FONT_WEIGHT_BOLDER 800

	#define FONT_SIZE_SMALLER 8
	#define FONT_SIZE_SMALL 10
	#define FONT_SIZE_NORMAL 13
	#define FONT_SIZE_BIG 16
	#define FONT_SIZE_BIGER 20

	class Control {

		protected:

			typedef struct _fontCfg {
				unsigned int size;
				unsigned int weight;
				bool italic;
				bool underlie;
				std::string family;
				static _fontCfg create();
			} fontCfg;

			bool enabled;

			HWND parent;
			HWND handle;
			DWORD style;
			int index;

			std::string name;
			std::string text;
			int type;
			unsigned int x;
			unsigned int y;
			unsigned int width;
			unsigned int height;

			fontCfg font;

			std::string getWin32Type();

			HFONT getWin32Font();

		public:

			static const DWORD BASIC_STYLE = WS_CHILD | WS_VISIBLE;
			static const int TYPE_BUTTON = 0;
			static const int TYPE_LABEL = 1;
			static const int TYPE_TEXT = 2;
			static const int TYPE_DROPDOWN = 3;
			static const int TYPE_GROUPBOX = 4;

			Control();

			//Metodos para sobescrever
			virtual LRESULT onCreate(HWND parent, HINSTANCE hInst) = 0;
			virtual LRESULT onCommand(int index, int wmEvent, WPARAM wParam, LPARAM lParam) = 0;
			virtual void toggleEnabled() = 0;

			/** GETTERS **/
			bool inited();
			int getIndex();
			HWND getHandle();
			std::string getName();
			std::string getText();
			int getType();
			unsigned int getX();
			unsigned int getY();
			unsigned int getWidth();
			unsigned int getHeight();

			/** SETTERS **/
			void setIndex(int index);
			void setText(std::string text);
			void setText(char* text);
			void setX(unsigned int x);
			void setY(unsigned int y);
			void setWidth(unsigned int width);
			void setHeight(unsigned int height);
			bool isEnabled();
	};

#endif