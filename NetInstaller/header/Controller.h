#pragma once

#if !defined _MAIN_CONTROLLER
	#define _MAIN_CONTROLLER
	
	#include "../stdafx.h"
	#include "abstract/Label.h"
	#include "abstract/Text.h"
	#include "abstract/Button.h"

	class Controller {

		private:
				
			HWND mainHwnd;
			Label *nwStatusLabel;
			Text *serverUrlText;
			Button *startBtn;

			BOOL connected = 0;

			std::string letter = "z:";
			std::string serverRoot = "\\\\server";
			std::string serverInstallPath = "\\PXE\\Windows\\win7\\media";
			std::string installerFile = "setup.exe";


			//Definições Singleton
			Controller(Controller const&);
			void operator=(Controller const&);

			//Contrutor
			Controller();
			
			int exec(std::string cmd);
			int exec(char *cmd);

			BOOL tryUnmount(std::string letter);
			BOOL tryMountShare(std::string url, std::string letter);
			BOOL loadDriver(std::string path);
			BOOL pathExists(std::string letter);
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
			void onHasNetwork();
			void onNotHasNetwork();
			void onSetupBtnClicked();
			void onRefreshBtnClicked();
			void onInstallDriverBtnClicked();
	};
#endif