#include "../../header/abstract/Control.h"

/* PROTECTED */

Control::fontCfg Control::fontCfg::create() {

	Control::fontCfg cfg = {
		FONT_SIZE_NORMAL,
		FONT_WEIGHT_NORMAL,
		false,
		false,
		"Tahoma"
	};

	return cfg;
}

std::string Control::getWin32Type() {

	std::string type;

	switch (this->type) {

		case Control::TYPE_LABEL:
			type = "STATIC";
		break;

		case Control::TYPE_TEXT:
			type = "EDIT";
		break;

		case Control::TYPE_DROPDOWN:
			type = "COMBOBOX";
		break;

		case Control::TYPE_GROUPBOX:
		case Control::TYPE_BUTTON:
		default:
			type = "BUTTON";
		break;
	}

	return type;
}

HFONT Control::getWin32Font() {

	TCHAR *family = Conversions::stringToTCHAR(this->font.family);

	HFONT font = CreateFont(
		this->font.size,				//Height
		0,								//Width
		0,								//Escapement
		0,								//Orientation
		this->font.weight,				//Weight
		this->font.italic,				//Italic
		this->font.underlie,			//Underline
		FALSE,							//StrikeOut
		DEFAULT_CHARSET,				//CharSet
		OUT_TT_PRECIS,					//OutputPrecision
		CLIP_DEFAULT_PRECIS,			//ClipPrecision
		DEFAULT_QUALITY,				//Quality
		DEFAULT_PITCH | FF_DONTCARE,	//PitchAndFamily
		family							//Family
	);

	delete[] family;
	return font;
}

/* PUBLIC */

Control::Control() {
	this->handle = NULL;
	this->enabled = true;
	this->index = -1;
	this->name = "";
	this->font = Control::fontCfg::create();
}


/** GETTERS **/

bool Control::inited() {
	return this->handle != NULL;
}

int Control::getIndex() {
	return this->index;
}

HWND Control::getHandle() {
	return this->handle;
}

std::string Control::getName() {
	return this->name;
}

std::string Control::getText() {
	return this->text;
}

int Control::getType() {
	return this->type;
}

unsigned int Control::getX() {
	return this->x;
}

unsigned int Control::getY() {
	return this->y;
}

unsigned int Control::getWidth() {
	return this->width;
}

unsigned int Control::getHeight() {
	return this->height;
}

/** SETTERS **/

void Control::setIndex(int index) {
	this->index = this->index >= 0 ? this->index : index;
}

void Control::setText(std::string text) {
	this->text = text;
}

void Control::setText(char* text) {
	this->text = text;
}

void Control::setX(unsigned int x) {
	this->x = x;
}

void Control::setY(unsigned int y) {
	this->y = y;
}

void Control::setWidth(unsigned int width) {
	this->width = width;
}

void Control::setHeight(unsigned int height) {
	this->height = height;
}

bool Control::isEnabled() {
	return this->enabled;
}