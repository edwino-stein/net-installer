#include "../../header/abstract/Text.h"

Text::Text() : Control() {
	this->type = Control::TYPE_TEXT;
	this->style = Control::BASIC_STYLE | WS_BORDER;
	this->x = 0;
	this->y = 0;
	this->width = 50;
	this->height = 20;
	this->text.append("");
	this->lines = 1;
	this->readOnly = false;
	this->full = false;
}

LRESULT Text::onCreate(HWND parent, HINSTANCE hInst) {

	TCHAR * type = Conversions::stringToTCHAR(this->getWin32Type());
	TCHAR * text = Conversions::stringToTCHAR(this->text);

	if (this->lines > 1) {
		this->style |= ES_MULTILINE;
		this->height = 20 * this->lines;
	}
	else {
		this->height = 20;
	}

	if (this->readOnly) {
		this->style |= ES_READONLY;
	}

	this->parent = parent;
	this->handle = CreateWindow(
		type,
		text,
		this->style,
		this->x,
		this->y,
		this->width,
		this->height,
		this->parent,
		(HMENU) this->index,
		hInst,
		NULL
	);

	if (this->inited()) {
		SendMessage(
			this->handle,
			WM_SETFONT,
			(WPARAM) this->getWin32Font(),
			TRUE
		);

		EnableWindow(this->handle, this->enabled);
	}

	delete[] type;
	delete[] text;

	return 0;
}

LRESULT Text::onCommand(int index, int wmEvent, WPARAM wParam, LPARAM lParam) {

	if (index != this->index) return 0;

	switch (wmEvent) {

		case Text::EVENT_CHANGE: this->onChange(); break;

		case Text::EVENT_BLUR: this->onBlur(); break;

		case Text::EVENT_FOCUS: this->onFocus(); break;

		case Text::EVENT_FREE:
			this->full = false;
			this->onFree();
		break;

		case Text::EVENT_LIMIT:
			this->full = true;
			this->onLimit();
		break;
	}

	return 0;
}

std::string Text::getText() {

	if (this->inited()) {

		int length = this->getLength();
		TCHAR *tText = new TCHAR[length + 1];

		ZeroMemory(tText, length + 1);
		GetWindowText(this->handle, tText, length + 1);
		this->text = Conversions::TCHARToString(tText);

		delete[] tText;
	}

	return this->text;
}

int Text::getLength() {
	return GetWindowTextLength(this->handle);
}

void Text::setText(std::string text) {
	Control::setText(text);

	if (this->inited()) {
		TCHAR *tText = Conversions::stringToTCHAR(text);
		int itemIndex = SetWindowText(this->handle, tText);
		delete[] tText;
	}
}

void Text::setText(char* text) {
	Control::setText(text);

	if (this->inited()) {
		TCHAR *tText = Conversions::charToTCHAR(text);
		int itemIndex = SetWindowText(this->handle, tText);
		delete[] tText;
	}
}

void Text::setReadOnly(bool readOnly) {
	this->readOnly = readOnly;
	if (this->enabled) Edit_SetReadOnly(this->handle, readOnly);
}

void Text::setLines(unsigned int lines) {
	this->lines = lines;
}

unsigned int Text::getLines() {
	return this->lines;
}

void Text::toggleEnabled() {
	this->enabled = !this->enabled;
	Edit_Enable(this->handle, this->enabled);
}

bool Text::isFull() {
	return this->full;
}

bool Text::isEmpty() {
	return this->getLength() <= 0;
}

bool Text::isReadOnly() {
	return this->readOnly;
}

/* EVENTS */
void Text::onChange() {}
void Text::onBlur() {}
void Text::onFocus() {}
void Text::onFree() {}
void Text::onLimit() {}