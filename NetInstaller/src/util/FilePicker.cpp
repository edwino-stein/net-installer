#include "../../header/util/FilePicker.h"
#include "../../header/util/Conversions.h"

FilePicker::FilePicker(HWND owner) {
	this->owner = owner;
	this->setTitle("Select a file...");
	this->seTypeFilter(NULL);
	this->buffer = NULL;
}

FilePicker::FilePicker(HWND owner, std::string title) : FilePicker(owner) {
	this->setTitle(title);
}

void FilePicker::cleanBuffer() {

	if (this->buffer != NULL) {
		delete[] this->buffer;
	}

	this->buffer = new TCHAR[this->BUFFER_SIZE]();
}

OPENFILENAME* FilePicker::newOPENFILENAME() {
	
	this->cleanBuffer();

	OPENFILENAME *ofns = new OPENFILENAME();
	ofns->lStructSize = sizeof(OPENFILENAME);

	ofns->hwndOwner = this->owner;
	ofns->lpstrFile = this->buffer;
	ofns->nMaxFile = this->BUFFER_SIZE;
	ofns->lpstrTitle = Conversions::stringToTCHAR(this->title.c_str());
	ofns->lpstrFileTitle = NULL;
	ofns->Flags = this->flags;

	if (this->typeFilter != NULL) {
		ofns->lpstrFilter = this->typeFilter;
		ofns->nFilterIndex = 1;
	}

	return ofns;
}

std::string FilePicker::getFilePath() {
	OPENFILENAME *ofns = this->newOPENFILENAME();
	GetOpenFileName(ofns);
	delete ofns;
	return Conversions::TCHARToString(this->buffer);
}

FilePicker *FilePicker::setTitle(std::string title) {
	this->title = title;
	return this;
}

FilePicker *FilePicker::seTypeFilter(LPCWSTR typeFilter) {
	this->typeFilter = typeFilter;
	return this;
}