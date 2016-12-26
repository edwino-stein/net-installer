#include "../../header/abstract/Label.h"

Label::Label() : Control() {
	this->type = Control::TYPE_LABEL;
	this->style = Control::BASIC_STYLE | SS_LEFT;
	this->x = 0;
	this->y = 0;
	this->width = 10;
	this->height = 10;
	this->text.append("LABEL");
}

LRESULT Label::onCreate(HWND parent, HINSTANCE hInst) {

	TCHAR * type = Conversions::stringToTCHAR(this->getWin32Type());
	TCHAR * text = Conversions::stringToTCHAR(this->text);

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
	}

	delete[] type;
	delete[] text;
	return 0;
}

/*
TODO: Verificar como capturar os eventos
*/
LRESULT Label::onCommand(int index, int wmEvent, WPARAM wParam, LPARAM lParam) { return 0; }

/*
TODO: Implementar o toggleEnabled
*/
void Label::toggleEnabled() {}

void Label::setText(std::string text) {
	Control::setText(text);

	if (this->inited()) {
		SendMessage(this->handle, WM_SETTEXT, NULL, (LPARAM)Conversions::stringToTCHAR(text));
	}
}

void Label::setText(char* text) {
	Control::setText(text);

	if (this->inited()) {
		SendMessage(this->handle, WM_SETTEXT, NULL, (LPARAM)Conversions::charToTCHAR(text));
	}
}