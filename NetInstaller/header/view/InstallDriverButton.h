#pragma once

#if !defined _VIEW_INSTALL_DRIVER_BUTTON
	#define _VIEW_INSTALL_DRIVER_BUTTON

	#include "../abstract/Button.h"
	#include "../Controller.h"

	class InstallDriverButton : public Button {

		public:

			static const int BTN_ID = 100;

			InstallDriverButton() : Button() {
				index = BTN_ID;
				x = 24;
				y = 224;
				width = 194;
				height = 30;
				text = "Carregar drivers";
				enabled = true;
			}

			void onClick() {
				Controller::getInstance()->onInstallDriverBtnClicked();
			}
	};

#endif