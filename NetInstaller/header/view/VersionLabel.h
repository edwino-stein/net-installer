#pragma once

#if !defined _VIEW_VERSION_LABEL
	#define _VIEW_VERSION_LABEL

	#include "../abstract/Label.h"

	class VersionLabel : public Label {
		public:
			VersionLabel() : Label() {

				std::string version = VER_FILE_VERSION_SIMPLE_STR;
				std::string arch = VER_ARCH_STR;
				std::string buildSet = VER_BUILD_SET_STR;

				x = 133;
				y = 388;
				width = 100;
				height = 17;
				text = "v" + version + buildSet + " "+ arch;
				this->style |= SS_RIGHT;
			}
	};

#endif