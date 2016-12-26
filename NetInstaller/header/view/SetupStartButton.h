#pragma once

#if !defined _VIEW_SETUP_START_BUTTON
	#define _VIEW_SETUP_START_BUTTON

	#include "../abstract/Button.h"
	#include "../Controller.h"

	class SetupStartButton : public Button {

		public:

			SetupStartButton() : Button() {
				index = 200;
				x = 24;
				y = 69;
				width = 194;
				height = 30;
				font.weight = FONT_WEIGHT_BOLD;
				font.size = FONT_SIZE_BIG;
				text = "Iniciar";
				enabled = true;
				dfaut = true;
			}

			void onClick() {
				Controller::getInstance()->onSetupBtnClicked();
			}
	};

#endif