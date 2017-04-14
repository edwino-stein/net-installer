#pragma once

#if !defined _MAIN_CONTROLLER
	#define _MAIN_CONTROLLER
	
	#include "../stdafx.h"
	#include "abstract/Label.h"
	#include "abstract/Text.h"
	#include "abstract/Button.h"
	#include "abstract/Dropdown.h"
	#include "util/FilePicker.h"

	class Controller {

		private:
				
			HWND mainHwnd;
			Label *nwStatusLabel;
			Text *serverUrlText;
			Text *serverPathText;
			Button *startBtn;
			Dropdown *letterDropdown;

			BOOL connected = 0;

			nlohmann::json config;
			std::vector<char> letterList;

			FilePicker *filePicker;

			//Definições Singleton
			Controller(Controller const&);
			void operator=(Controller const&);

			//Contrutor
			Controller();
			
			int exec(std::string cmd);
			int exec(char *cmd);

			BOOL loadDriver(std::string path, BOOL tryNet);
			BOOL hasNetwork();

			std::string getLetterSelected();
			void loadConfig();
		public:

			static Controller* getInstance() {
				static Controller *instance = new Controller;
				return instance;
			}

			void onReady(HWND hwnd);
			void onHasNetwork();
			void onNotHasNetwork();
			void onSetupBtnClicked();
			void onRefreshBtnClicked();

			void onInstallDriverBtnClicked();
			void onDiskpartBtnClicked();
			void onCmdBtnClicked();
	};
#endif