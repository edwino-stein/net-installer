#pragma once

#if !defined _VIEW_CONTROLS
#define _VIEW_CONTROLS
	
	#include "abstract\ControlsStore.h"
	
	#include "view\InstallBox.h"
	#include "view\ServerUrlLabel.h"
	#include "view\ServerUrlText.h"
	#include "view\SetupStartButton.h"
	#include "view\NwStatusBox.h"
	#include "view\NwStatusLabel.h"
	#include "view\NwRefreshBtn.h"
	#include "view\UtilBox.h"
	#include "view\InstallDriverButton.h"
	#include "view\DiskpartButton.h"
	#include "view\CmdButton.h"
	#include "view\LetterDropdown.h"
	#include "view\LetterLabel.h"
	#include "view\ServerPathLabel.h"
	#include "view\ServerPathText.h"
	#include "view\AboutLabel.h"
	#include "view\VersionLabel.h"

	class ViewControls : public ControlsStore {

		public:
			ViewControls(){

				Control *objs[] = {
					new InstallBox,
					new LetterLabel,
					new LetterDropdown,
					new ServerUrlLabel,
					new ServerUrlText,
					new ServerPathLabel,
					new ServerPathText,
					new SetupStartButton,
					new NwStatusBox,
					new NwStatusLabel,
					new NwRefreshBtn,
					new UtilBox,
					new InstallDriverButton,
					new DiskpartButton,
					new CmdButton,
					new AboutLabel,
					new VersionLabel
				};

				this->storeObjects(objs, sizeof(objs) / sizeof(objs[0]));
			}
	};

#endif