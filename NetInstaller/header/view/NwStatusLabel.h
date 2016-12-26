#pragma once
#if !defined _VIEW_NW_STATUS
#define _VIEW_NW_STATUS

	#include "../abstract/Label.h"

	class NwStatusLabel : public Label {
		public:
			NwStatusLabel() : Label() {
				index = 10;
				x = 24;
				y = 137;
				width = 194;
				height = 17;
				text = "Rede: desconectado";
			}
	};

#endif