#pragma once


#if !defined _VIEW_CMD_BUTTON
	#define _VIEW_CMD_BUTTON

	#include "../abstract/Button.h"
	#include "../Controller.h"

	class CmdButton : public Button {

		public:

			static const int BTN_ID = 104;

			CmdButton() : Button() {
				index = BTN_ID;
				x = 24;
				y = 340;
				width = 194;
				height = 30;
				text = "Prompt de Comando";
				enabled = true;
			}

			void onClick() {
				Controller::getInstance()->onCmdBtnClicked();
			}
	};

#endif