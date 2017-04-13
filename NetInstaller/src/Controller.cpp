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

	std::string installer = this->letter + "\\" + this->installerFile;

	if (this->pathExists(installer)) {
		this->exec(installer);
		return;
	}

	std::string url = this->serverUrlText->getText();
	if (url.empty()) {
		MessageBox(
			NULL,
			L"Um endereço para o arquivos de instalação deve ser informado.\n",
			NULL,
			NULL
		);
		return;
	}

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

	std::string driverFile = this->filePicker->getFilePath();

	if (driverFile.empty()) {
		OutputDebugStringA("Nenhum arquivo selecionado\n");
		return;
	}

	OutputDebugStringA("Arquivo selecionado: ");
	OutputDebugStringA(driverFile.c_str());
	OutputDebugStringA("\n");

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

void Controller::onDiskpartBtnClicked() {
	OutputDebugStringA("onDiskpartBtnClicked\n");
	this->exec("diskpart.exe");
}

void Controller::onCmdBtnClicked() {
	OutputDebugStringA("onCmdBtnClicked\n");
	this->exec("cmd.exe");
}