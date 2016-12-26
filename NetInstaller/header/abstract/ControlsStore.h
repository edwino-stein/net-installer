#pragma once

#if !defined _CONTROLSTORE
	#define _CONTROLSTORE

	#include "../../stdafx.h"
	#include "Control.h"

	class ControlsStore {

		protected:
			std::vector<Control *> objects;

		public:
		
			void initObjects(HWND parent, HINSTANCE hInst);

			void fireEvent(int index, int wmEvent, WPARAM wParam, LPARAM lParam);

			void storeObjects(Control *objs[], unsigned int length);

			Control *getElementById(int index);

			Control *getElementByName(const char *name);

			Control *getElementByName(std::string name);

			std::vector<Control *> getElementsByType(int type);
	};

#endif