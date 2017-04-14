#pragma once

#if !defined _VIEW_VERSION_LABEL
	#define _VIEW_VERSION_LABEL

	#include "../abstract/Label.h"

	class VersionLabel : public Label {
		public:
			VersionLabel() : Label() {
				x = 133;
				y = 388;
				width = 100;
				height = 17;
				text = "1.2-3456 x86";
				this->style |= SS_RIGHT;
			}
	};

#endif