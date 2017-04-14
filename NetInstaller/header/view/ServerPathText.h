#pragma once

#if !defined _VIEW_SERVER_PATH_TEXT
	#define _VIEW_SERVER_PATH_TEXT

	#include "../abstract/Text.h"

	class ServerPathText : public Text {

		public:

			ServerPathText() : Text() {
				index = 12;
				style |= ES_AUTOHSCROLL;
				x = 24;
				y = 81;
				width = 194;
				height = 29;
				text = "";
			}
	};

#endif