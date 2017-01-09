#include "../header/Controller.h"
#include "../header/WinMain.h"
#include "../header/util/Conversions.h"
#include "../header/util/NetworkChecker.h"


Controller::Controller(){
	this->nwStatusLabel = (Label *) WinMain::getInstance()->getControlsStore()->getElementById(10);
	this->serverUrlText = (Text *) WinMain::getInstance()->getControlsStore()->getElementById(11);
	this->startBtn = (Button *) WinMain::getInstance()->getControlsStore()->getElementById(200);
}

int Controller::exec(std::string cmd) {
	return system(cmd.c_str());
}

int Controller::exec(char *cmd) {
	return system(cmd);
}

BOOL Controller::tryUnmount(std::string letter) {
	std::string label = "echo Tentando desconectar do servidor...";
	std::string cmd = "net use " + letter + " /delete";
	cmd = label + " & " + cmd;
	return this->exec(cmd) == 0;
}

BOOL Controller::tryMountShare(std::string url, std::string letter) {

	std::string label = "echo Tentando conectar ao servidor...";
	std::string cmd = "net use " + letter +" " + url;
	cmd = label + " & " + cmd;

	if (this->pathExists(letter)) this->tryUnmount(letter);
	return this->exec(cmd) == 0;
}

BOOL Controller::pathExists(std::string letter) {
	std::string cmd = "dir " + letter;
	return this->exec(cmd) == 0;
}

BOOL Controller::loadDriver(std::string path) {
	std::string label = "echo Verificando conectividade rede...";
	std::string cmd = "drvload.exe " + path;
	cmd = label + " & " + cmd;
	return this->exec(cmd) == 0;
}

BOOL Controller::hasNetwork() {
	std::string label = "echo Verificando conectividade rede...";
	std::string cmd = "net view " + this->serverRoot;
	cmd = label + " & " + cmd;
	return this->exec(cmd) == 0;
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
	this->serverUrlText->setText(this->serverRoot + this->serverInstallPath);
	this->onRefreshBtnClicked(); 
}

void  Controller::onHasNetwork() {
	this->nwStatusLabel->setText("Rede: conectado");
	if (!this->startBtn->isEnabled()) this->startBtn->toggleEnabled();
}

void Controller::onNotHasNetwork() {
	this->nwStatusLabel->setText("Rede: desconectado");
	if (this->startBtn->isEnabled()) this->startBtn->toggleEnabled();
}

void Controller::onSetupBtnClicked() {

	OutputDebugStringA("onSetupBtnClicked\n");

	std::string installer = this->letter + "\\" + this->installerFile;

	if (this->pathExists(installer)) {
		this->exec(installer);
		return;
	}

	std::string url = this->serverUrlText->getText();

	if (this->tryMountShare(url, this->letter)) {
		this->exec(installer);
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

void Controller::onRefreshBtnClicked() {
	OutputDebugStringA("onRefreshBtnClicked\n");
	if (this->hasNetwork()) this->onHasNetwork();
	else this->onNotHasNetwork();
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

		this->onRefreshBtnClicked();
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