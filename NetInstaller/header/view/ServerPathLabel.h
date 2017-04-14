#pragma once

#if !defined _VIEW_SERVER_PATH_LABEL
#define _VIEW_SERVER_PATH_LABEL

#include "../abstract/Label.h"

class ServerPathLabel : public Label {
public:
	ServerPathLabel() : Label() {
		x = 24;
		y = 65;
		width = 194;
		height = 17;
		text = "Caminho para instalacao:";
	}
};

#endif