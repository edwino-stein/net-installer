#pragma once


#if !defined _VIEW_DISKPART_BUTTON
	#define _VIEW_DISKPART_BUTTON

	#include "../abstract/Button.h"
	#include "../Controller.h"

	class DiskpartButton : public Button {

		public:

			static const int BTN_ID = 103;

			DiskpartButton() : Button() {
				index = BTN_ID;
				x = 24;
				y = 262;
				width = 194;
				height = 30;
				text = "Diskpart";
				enabled = true;
			}

			void onClick() {
				Controller::getInstance()->onDiskpartBtnClicked();
			}
	};

#endif