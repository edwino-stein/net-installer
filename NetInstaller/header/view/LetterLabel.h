#pragma once

#if !defined _VIEW_LETTER_LABEL
	#define _VIEW_LETTER_LABEL

	#include "../abstract/Label.h"

	class LetterLabel : public Label {
		public:
			LetterLabel() : Label() {
				x = 24;
				y = 20;
				width = 194;
				height = 17;
				text = "Unidade:";
			}
	};

#endif