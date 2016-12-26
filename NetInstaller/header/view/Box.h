#pragma once
#if !defined _VIEW_BOX
	#define _VIEW_BOX
	#include "../abstract/GroupBox.h"

	class Box : public GroupBox {

		public:
			Box() : GroupBox() {
				x = 100;
				y = 15;
				width = 194;
				height = 50;
				text = "Teste Box";
			}
	};

#endif