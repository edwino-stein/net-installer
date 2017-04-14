#pragma once

#if !defined _VIEW_SERVER_URL_TEXT
	#define _VIEW_SERVER_URL_TEXT

	#include "../abstract/Text.h"

	class ServerUrlText : public Text {

		public:

			ServerUrlText() : Text() {
				index = 11;
				style |= ES_AUTOHSCROLL;
				x = 79;
				y = 40;
				width = 139;
				height = 29;
				text = "";
			}
	};

#endif