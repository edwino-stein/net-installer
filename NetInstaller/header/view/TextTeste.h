#pragma once

#if !defined _VIEW_TEXTTESTE
#define _VIEW_TEXTTESTE

#include "../abstract/Text.h"

class TextTeste : public Text {

public:

	TextTeste() : Text() {
		index = 11;
		x = 12;
		y = 200;
		width = 194;
		height = 30;
		text = "Iniciar";
	}
};

#endif