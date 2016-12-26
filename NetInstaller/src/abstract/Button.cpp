#include "../../header/abstract/Button.h"

Button::Button() : Control() {
	this->type = Control::TYPE_BUTTON;
	this->style = Control::BASIC_STYLE;
	this->x = 0;
	this->y = 0;
	this->width = 10;
	this->height = 10;
	this->text.append("BUTTON");
	this->dfaut = false;
}

LRESULT Button::onCreate(HWND parent, HINSTANCE hInst) {

	TCHAR * type = Conversions::stringToTCHAR(this->getWin32Type());
	TCHAR * text = Conversions::stringToTCHAR(this->text);

	this->parent = parent;
	this->handle = CreateWindow(
		type,
		text,
		this->style | (this->dfaut ? BS_DEFPUSHBUTTON : BS_PUSHBUTTON),
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

LRESULT Button::onCommand(int index, int wmEvent, WPARAM wParam, LPARAM lParam) {
	if (index == this->index) this->onClick();
	return 0;
}

void Button::toggleEnabled() {
	this->enabled = !this->enabled;
	EnableWindow(this->handle, this->enabled);
}

void Button::setText(std::string text) {
	Control::setText(text);
	if(this->inited())
		SetWindowText(this->handle, Conversions::stringToTCHAR(text));
}

void Button::setText(char* text) {
	Control::setText(text);
	if(this->inited())
		SetWindowText(this->handle, Conversions::charToTCHAR(text));
}

void Button::setDefault(bool dfault) {
	this->dfaut = dfault;
}