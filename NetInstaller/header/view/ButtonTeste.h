#pragma once

#if !defined _VIEW_BUTTONTESTE
	#define _VIEW_BUTTONTESTE

	#include "../abstract/Button.h"

	class ButtonTeste : public Button {

		public:

			ButtonTeste() : Button() {
				index = 10;
				x = 12;
				y = 103;
				width = 194;
				height = 30;
				text = "Iniciar";
				font.weight = FONT_WEIGHT_BOLD;
				font.size = FONT_SIZE_BIG;
				dfaut = true;
				enabled = true;
			}

			void onClick() {
				OutputDebugStringA("teste");
			}
	};

#endif