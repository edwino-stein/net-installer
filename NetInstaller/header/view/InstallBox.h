#pragma once
#if !defined _VIEW_INSTALL_BOX
	#define _VIEW_INSTALL_BOX
	#include "../abstract/GroupBox.h"

	class InstallBox : public GroupBox {

		public:

			InstallBox() : GroupBox() {
				x = 12;
				y = 3;
				width = 220;
				height = 110;
				text = "Setup";
			}
	};

#endif