#pragma once

#if !defined _VIEW_NWREFRESH_BUTTON
	#define _VIEW_NWREFRESH_BUTTON

	#include "../abstract/Button.h"
	#include "../Controller.h"

	class NwRefreshBtn : public Button {

		public:

			static const int BTN_ID = 101;

			NwRefreshBtn() : Button() {
				index = BTN_ID;
				x = 24;
				y = 196;
				width = 194;
				height = 30;
				text = "Atualizar Status";
				enabled = true;
			}

			void onClick() {
				Controller::getInstance()->onRefreshBtnClicked();
			}
	};

#endif