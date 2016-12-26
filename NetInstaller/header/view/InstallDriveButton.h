#pragma once

#if !defined _VIEW_INSTALL_DRIVE_BUTTON
	#define _VIEW_INSTALL_DRIVE_BUTTON

	#include "../abstract/Button.h"

	class InstallDriveButton : public Button {

		public:

			static const int BTN_ID = 100;

			InstallDriveButton() : Button() {
				index = BTN_ID;
				x = 24;
				y = 156;
				width = 194;
				height = 30;
				text = "Instalar Driver";
				enabled = true;
			}

			void onClick() {
				OutputDebugStringA("InstallDriveButton\n");
			}
	};

#endif