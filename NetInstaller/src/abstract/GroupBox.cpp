#include "../../header/abstract/GroupBox.h"

GroupBox::GroupBox() : Label() {
	this->type = Control::TYPE_GROUPBOX;
	this->style = Control::BASIC_STYLE | BS_GROUPBOX;
	this->text = "GROUPBOX";
}