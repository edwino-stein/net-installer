#pragma once

#if !defined _VIEW_SERVER_URL_LABEL
	#define _VIEW_SERVER_URL_LABEL

	#include "../abstract/Label.h"

	class ServerUrlLabel : public Label {
		public:
			ServerUrlLabel() : Label() {
				x = 79;
				y = 20;
				width = 139;
				height = 17;
				text = "Endereco do servidor:";
			}
	};

#endif