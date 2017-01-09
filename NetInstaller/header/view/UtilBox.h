#pragma once

#if !defined _VIEW_UTIL_BOX

	#define _VIEW_UTIL_BOX
	#include "../abstract/GroupBox.h"

	class UtilBox : public GroupBox {

		public:
			UtilBox() : GroupBox() {
				index = 11;
				x = 12;
				y = 205;
				width = 220;
				height = 138;
				text = "Utilitarios";
			}
	};

#endif