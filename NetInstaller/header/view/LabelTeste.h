#pragma once
#if !defined _VIEW_LABELTESTE
#define _VIEW_LABELTESTE

	#include "../abstract/Label.h"

	class LabelTeste : public Label {

	public:
		LabelTeste() : Label() {
			x = 12;
			y = 12;
			width = 194;
			height = 17;
			text = "Selecione a janela do jogo:";
		}
	};

#endif