#pragma once

#if !defined _VIEW_INSTALL_DRIVER_BOX

	#define _VIEW_INSTALL_DRIVER_BOX
	#include "../abstract/GroupBox.h"

	class InstallDriverBox : public GroupBox {

		public:
			InstallDriverBox() : GroupBox() {
				index = 11;
				x = 12;
				y = 205;
				width = 220;
				height = 60;
				text = "Carregar drivers";
			}
	};

#endif