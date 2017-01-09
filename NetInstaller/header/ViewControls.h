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

	class ViewControls : public ControlsStore {

		public:
			ViewControls(){

				Control *objs[] = {
					new InstallBox,
					new ServerUrlLabel,
					new ServerUrlText,
					new SetupStartButton,
					new NwStatusBox,
					new NwStatusLabel,
					new NwRefreshBtn,
					new UtilBox,
					new InstallDriverButton,
					new DiskpartButton,
					new CmdButton
				};

				this->storeObjects(objs, sizeof(objs) / sizeof(objs[0]));
			}
	};

#endif