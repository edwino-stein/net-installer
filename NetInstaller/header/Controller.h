#pragma once

#if !defined _MAIN_CONTROLLER
	#define _MAIN_CONTROLLER
	
	#include "../stdafx.h"
	#include "abstract/Label.h"
	#include "abstract/Text.h"

	class Controller {

		private:
				
			HWND mainHwnd;
			Label *nwStatusLabel;
			Text *serverUrlText;

			//Definições Singleton
			Controller(Controller const&);
			void operator=(Controller const&);

			//Contrutor
			Controller();
			
			

			int exec(std::string cmd);
			int exec(char *cmd);

			BOOL tryMountShare(std::string url);
			BOOL loadDriver(std::string path);
			BOOL hasNetwork();


			std::string getOpenFilename(std::string prompt, char *type);
			std::string getOpenFilename(std::string prompt, std::string type);
			std::string getOpenFilename(std::string prompt);

		public:

			static Controller* getInstance() {
				static Controller *instance = new Controller;
				return instance;
			}

			void onReady(HWND hwnd);
			void onSetupBtnClicked();
			void onInstallDriverBtnClicked();
	};
#endif