#pragma once

#if !defined _VIEW_LETTER_DROPDOWN
	#define _VIEW_LETTER_DROPDOWN

	#include "../abstract/Dropdown.h"
	#include "../Controller.h"

	class LetterDropdown : public Dropdown {

		public:

			static const int DD_ID = 300;

			LetterDropdown() : Dropdown() {
				index = DD_ID;
				x = 24;
				y = 39;
				width = 45;
				height = 100;
			}
	};

#endif