#include "../header/Controller.h"
#include "../header/WinMain.h"
#include "../header/util/Conversions.h"
#include "../header/util/NetworkChecker.h"


Controller::Controller(){
	this->nwStatusLabel = (Label *) WinMain::getInstance()->getControlsStore()->getElementById(10);
	this->serverUrlText = (Text *) WinMain::getInstance()->getControlsStore()->getElementById(11);
	this->startBtn = (Button *) WinMain::getInstance()->getControlsStore()->getElementById(200);
	this->letterDropdown = (Dropdown *)WinMain::getInstance()->getControlsStore()->getElementById(300);
}

int Controller::exec(std::string cmd) {
	OutputDebugStringA("EXEC: ");
	OutputDebugStringA(cmd.c_str());
	OutputDebugStringA("\n");
	return system(cmd.c_str());
}

int Controller::exec(char *cmd) {
	std::string c = cmd;
	return this->exec(c);
}

BOOL Controller::loadDriver(std::string path, BOOL tryNet) {
	std::string cmd = WinMain::getInstance()->loadString(SCRIPT_LOADDRIVER);
	cmd += " " + path;

	if (tryNet) {
		cmd += " " + this->serverRoot;
	}

	return this->exec(cmd) == 0;
}

BOOL Controller::hasNetwork() {
	std::string cmd = WinMain::getInstance()->loadString(SCRIPT_NETTEST);
	cmd += " " + this->serverRoot;
	return this->exec(cmd) == 0;
}

/* CALLBACKS */

void Controller::onReady(HWND hwnd) {
	this->mainHwnd = hwnd;

	//Instancia o FilePicker
	this->filePicker = new FilePicker(hwnd, "Carregar driver...");
	this->filePicker->seTypeFilter(_TEXT("Driver (*.inf)\0*.INF\0Qualquer (*.*)\0*.*\0"));

	//Carrear dos recursos
	this->serverUrlText->setText(this->serverRoot + this->serverInstallPath);
	//this->onRefreshBtnClicked(); 
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

	std::string serverUrl = this->serverUrlText->getText();
	if (serverUrl.empty()) {
		MessageBox(
			NULL,
			L"Um endere�o para o arquivos de instala��o deve ser informado.\n",
			NULL,
			NULL
		);
		return;
	}

	std::string cmd = WinMain::getInstance()->loadString(SCRIPT_SETUP);
	cmd += " " + this->letter;
	cmd += " " + serverUrl;
	cmd += " " + this->installerFile;

	int code = this->exec(cmd);
	if (code != 0) {

		OutputDebugStringA("Return Code: ");
		OutputDebugStringA(std::to_string(code).c_str());
		OutputDebugStringA("\n");

		MessageBox(
			NULL,
			L"Houve um erro durante a tentativa de inicializar a instala��o.\n",
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

	std::string driverFile = this->filePicker->getFilePath(TRUE);

	if (driverFile.empty()) {
		OutputDebugStringA("Nenhum arquivo selecionado\n");
		return;
	}

	OutputDebugStringA("Arquivo selecionado: ");
	OutputDebugStringA(driverFile.c_str());
	OutputDebugStringA("\n");

	if (!this->loadDriver(driverFile, TRUE)) {
		MessageBox(
			NULL,
			L"Houve um erro durante o carregamento do driver\n",
			NULL,
			NULL
		);

		return;
	}

	this->onHasNetwork();
}

void Controller::onDiskpartBtnClicked() {
	OutputDebugStringA("onDiskpartBtnClicked\n");
	this->exec("diskpart.exe");
}

void Controller::onCmdBtnClicked() {
	OutputDebugStringA("onCmdBtnClicked\n");
	this->exec("cmd.exe");
}