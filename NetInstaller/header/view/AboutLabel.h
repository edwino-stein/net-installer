#pragma once

#if !defined _VIEW_ABOUT_LABEL
	#define _VIEW_ABOUT_LABEL

	#include "../abstract/Label.h"

	class AboutLabel : public Label {
		public:
			AboutLabel() : Label() {
				x = 13;
				y = 388;
				width = 100;
				height = 17;
				text = "Edwino Stein - 2017";
			}
	};

#endif