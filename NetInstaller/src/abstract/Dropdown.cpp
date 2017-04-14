#include "../../header/abstract/Dropdown.h"

Dropdown::Dropdown() : Control() {
	this->type = Control::TYPE_DROPDOWN;
	this->style = Control::BASIC_STYLE | CBS_DROPDOWNLIST;
	this->x = 0;
	this->y = 0;
	this->width = 10;
	this->height = 10;
	this->text.append("");
}

void Dropdown::onChange() {}
void Dropdown::onBlur() {}
void Dropdown::onFocus() {}
void Dropdown::onExpand() {}
void Dropdown::onCollapse() {}

LRESULT Dropdown::onCreate(HWND parent, HINSTANCE hInst) {

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

		ComboBox_Enable(this->handle, this->enabled);
	}

	delete[] type;
	delete[] text;

	return 0;
}

LRESULT Dropdown::onCommand(int index, int wmEvent, WPARAM wParam, LPARAM lParam) {

	if (index != this->index) {
		return 0;
	}

	switch (wmEvent) {
	case Dropdown::EVENT_CHANGE:
		this->onChange();
		break;

	case Dropdown::EVENT_BLUR:
		this->onBlur();
		break;

	case Dropdown::EVENT_FOCUS:
		this->onFocus();
		break;

	case Dropdown::EVENT_EXPAND:
		this->onExpand();
		break;

	case Dropdown::EVENT_COLLAPSE:
		this->onCollapse();
		break;
	}

	return 0;
}

int Dropdown::getSelectedIndex() {
	return ComboBox_GetCurSel(this->handle);
}

int Dropdown::addItem(std::string label) {
	TCHAR * text = Conversions::stringToTCHAR(label);
	int itemIndex = ComboBox_AddItemData(this->handle, (LPARAM)text);
	delete[] text;
	return itemIndex;
}

int Dropdown::addItem(char *label) {
	TCHAR *text = Conversions::charToTCHAR(label);
	int itemIndex = ComboBox_AddItemData(this->handle, (LPARAM)text);
	delete[] text;
	return itemIndex;
}

void Dropdown::toggleEnabled() {
	if (this->enabled) {
		ComboBox_Enable(this->handle, false);
		this->enabled = false;
	}
	else {
		ComboBox_Enable(this->handle, true);
		this->enabled = true;
	}
}

int Dropdown::count() {
	return ComboBox_GetCount(this->handle);
}

void Dropdown::reset() {
	ComboBox_ResetContent(this->handle);
}
