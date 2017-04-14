#pragma once
#if !defined _VIEW_NW_STATUS_BOX
	#define _VIEW_NW_STATUS_BOX
	#include "../abstract/GroupBox.h"

	class NwStatusBox : public GroupBox {

		public:
			NwStatusBox() : GroupBox() {
				index = 11;
				x = 12;
				y = 160;
				width = 220;
				height = 80;
				text = "Status da Rede";
			}
	};

#endif