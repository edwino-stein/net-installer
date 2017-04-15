#include "../header/Controller.h"
#include "../header/WinMain.h"
#include "../header/util/Conversions.h"
#include "../header/util/NetworkChecker.h"


Controller::Controller(){
	this->nwStatusLabel = (Label *) WinMain::getInstance()->getControlsStore()->getElementById(10);
	this->serverUrlText = (Text *) WinMain::getInstance()->getControlsStore()->getElementById(11);
	this->serverPathText = (Text *) WinMain::getInstance()->getControlsStore()->getElementById(12);
	this->startBtn = (Button *) WinMain::getInstance()->getControlsStore()->getElementById(200);
	this->letterDropdown = (Dropdown *) WinMain::getInstance()->getControlsStore()->getElementById(300);
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
	std::string serverUri = this->config["serverUri"];

	cmd += " " + path;

	if (tryNet) {
		cmd += " " + serverUri;
	}

	return this->exec(cmd) == 0;
}

BOOL Controller::hasNetwork() {
	std::string cmd = WinMain::getInstance()->loadString(SCRIPT_NETTEST);
	std::string serverUri = this->config["serverUri"];
	cmd += " " + serverUri;
	return this->exec(cmd) == 0;
}

/* CALLBACKS */

void Controller::onReady(HWND hwnd) {
	this->mainHwnd = hwnd;

	OutputDebugStringA("Versao: ");
	OutputDebugStringA(VER_FILE_VERSION_STR);
	OutputDebugStringA("\n");

	//Instancia o FilePicker
	this->filePicker = new FilePicker(hwnd, "Carregar driver...");
	this->filePicker->seTypeFilter(_TEXT("Driver (*.inf)\0*.INF\0Qualquer (*.*)\0*.*\0"));

	//Carrear dos recursos
	this->loadConfig();
	this->serverUrlText->setText(this->config["serverUri"]);
	this->serverPathText->setText(this->config["installPath"]);

	std::string letter;
	for (char l = 'A'; l <= 'Z'; l++) {
		this->letterList.push_back(l);
		letter = "";
		letter += l;
		letter += ':';
		this->letterDropdown->addItem(letter);
	}

	this->letterDropdown->setValue(0);

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
			L"Um endereço para o arquivos de instalação deve ser informado.\n",
			NULL,
			NULL
		);
		return;
	}

	std::string serverPath = this->serverPathText->getText();
	if (serverUrl.empty()) {
		MessageBox(
			NULL,
			L"O Caminho para a instalacao deve ser informado.\n",
			NULL,
			NULL
		);
		return;
	}

	std::string installExe = this->config["installExe"];
	std::string letter = this->getLetterSelected();

	std::string cmd = WinMain::getInstance()->loadString(SCRIPT_SETUP);
	cmd += " " + letter;
	cmd += " \\\\" + serverUrl + "\\" + serverPath;
	cmd += " " + installExe;

	int code = this->exec(cmd);
	if (code != 0) {

		OutputDebugStringA("Return Code: ");
		OutputDebugStringA(std::to_string(code).c_str());
		OutputDebugStringA("\n");

		MessageBox(
			NULL,
			L"Houve um erro durante a tentativa de inicializar a instalação.\n",
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

std::string Controller::getLetterSelected() {
	int index = this->letterDropdown->getSelectedIndex();
	char l = this->letterList[index];
	std::string letter = "";
	letter += l;
	letter += ':';
	return letter;
}

void Controller::loadConfig() {
	
	std::string file = WinMain::getInstance()->loadString(CONFIG_DEFAULT_FILE);
	std::ifstream i(file);

	if (i.is_open()) {
		i >> this->config;
		OutputDebugStringA("Carregando arquivo \"");
		OutputDebugStringA(file.c_str());
		OutputDebugStringA("\"\n");
		OutputDebugStringA(this->config.dump().c_str());
		OutputDebugStringA("\n");
	}
	else {
		OutputDebugStringA("AVISO: Arquivo de configuração não foi encontrado.\n");
	}
	
	if (this->config.find("serverUri") == this->config.end()) {
		this->config["serverUri"] = WinMain::getInstance()->loadString(CONFIG_DEFAULT_SERVER_URI);
	}

	if (this->config.find("installPath") == this->config.end()) {
		this->config["installPath"] = WinMain::getInstance()->loadString(CONFIG_DEFAULT_SERVER_PATH);
	}

	if (this->config.find("installExe") == this->config.end()) {
		this->config["installExe"] = WinMain::getInstance()->loadString(CONFIG_DEFAULT_INSTALL_EXE);
	}
}