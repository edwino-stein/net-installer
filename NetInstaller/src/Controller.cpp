#include "../header/Controller.h"
#include "../header/WinMain.h"
#include "../header/util/Conversions.h"
#include "../header/util/NetworkChecker.h"

#include <process.h>

Controller::Controller(){
	this->nwStatusLabel = (Label *) WinMain::getInstance()->getControlsStore()->getElementById(10);
	this->serverUrlText = (Text *) WinMain::getInstance()->getControlsStore()->getElementById(11);
}

int Controller::exec(std::string cmd) {
	return system(cmd.c_str());
}

int Controller::exec(char *cmd) {
	return system(cmd);
}

BOOL Controller::tryMountShare(std::string url) {
	std::string cmd = "net use z: " + url;
	return this->exec(cmd) == 0;
}

BOOL Controller::loadDriver(std::string path) {
	std::string cmd = "drvload.exe " + path;
	return this->exec(cmd) == 0;
}

BOOL Controller::hasNetwork() {
	return NetworkChecker::check();
}

std::string Controller::getOpenFilename(std::string prompt, char *type) {

	const int BUFSIZE = 1024;
	TCHAR buffer[BUFSIZE] = { 0 };

	OPENFILENAME ofns = { 0 };
	ofns.lStructSize = sizeof(ofns);

	ofns.hwndOwner = this->mainHwnd;
	ofns.nMaxFile = 1;

	ofns.lpstrFile = buffer;
	ofns.nMaxFile = BUFSIZE;
	ofns.lpstrTitle = Conversions::stringToTCHAR(prompt.c_str());

	if (type != NULL) {
		ofns.lpstrFilter = Conversions::charToTCHAR(type);
	}

	GetOpenFileName(&ofns);
	return Conversions::TCHARToString(buffer);
}

std::string Controller::getOpenFilename(std::string prompt, std::string type) {
	return this->getOpenFilename(prompt, (char *) type.c_str());
}

std::string Controller::getOpenFilename(std::string prompt) {
	return this->getOpenFilename(prompt, NULL);
}


/* CALLBACKS */

void Controller::onReady(HWND hwnd) {
	this->mainHwnd = hwnd;

	//Carrear dos recursos
	this->serverUrlText->setText("\\\\server\\PXE\\Windows\\win7\\media");

	if (this->hasNetwork()) {
		this->nwStatusLabel->setText("Rede: conectado");
	}
	else {
		this->nwStatusLabel->setText("Rede: desconectado");
	}
}

void Controller::onSetupBtnClicked() {
	OutputDebugStringA("onSetupBtnClicked\n");
	std::string url = this->serverUrlText->getText();

	if (this->tryMountShare(url)) {
		this->exec("z:\\setup.exe");
	}
	else {
		MessageBox(
			NULL,
			L"Houve um erro enquanto o windows tentava montar a unidade de rede.\n",
			NULL,
			NULL
		);
	}
}

void Controller::onInstallDriverBtnClicked() {
	OutputDebugStringA("onInstallDriverBtnClicked\n");

	std::string driverFile = this->getOpenFilename("Selecione o arquivo do driver...");

	if (this->loadDriver(driverFile)) {
		MessageBox(
			NULL,
			L"O driver foi carregado com sucesso!\n",
			NULL,
			NULL
		);

		if (this->hasNetwork()) {
			this->nwStatusLabel->setText("Rede: conectado");
		}
		else {
			this->nwStatusLabel->setText("Rede: desconectado");
		}
	}
	else {
		MessageBox(
			NULL,
			L"Houve um erro durante o carregamento do driver\n",
			NULL,
			NULL
		);
	}
}