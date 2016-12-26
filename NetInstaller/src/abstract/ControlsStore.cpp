#include "../../header/abstract/ControlsStore.h"

void ControlsStore::initObjects(HWND parent, HINSTANCE hInst) {

	int size = this->objects.size();
	int i;

	for (i = 0; i < size; i++) {
		this->objects[i]->setIndex(i);
		this->objects[i]->onCreate(parent, hInst);
	}
}

void ControlsStore::fireEvent(int index, int wmEvent, WPARAM wParam, LPARAM lParam) {
	Control * obj = this->getElementById(index);
	if (obj != NULL) {
		obj->onCommand(index, wmEvent, wParam, lParam);
	}

}

void ControlsStore::storeObjects(Control *objs[], unsigned int length) {
	if (objs != NULL){
		this->objects.assign(objs, objs + length);
	}
}

Control *ControlsStore::getElementById(int index) {

	int size = this->objects.size();
	int i;

	for (i = 0; i < size; i++) {
		if (this->objects[i]->getIndex() == index) {
			return this->objects[i];
		}
	}

	return NULL;
}

Control *ControlsStore::getElementByName(std::string name) {
	return this->getElementByName(name.c_str());
}

std::vector<Control *> ControlsStore::getElementsByType(int type) {

	std::vector<Control *> objs;
	int size = this->objects.size();
	int i;

	for (i = 0; i < size; i++) {
		if (this->objects[i]->getType() == type) {
			objs.push_back(this->objects[i]);
		}
	}

	return objs;
}

Control *ControlsStore::getElementByName(const char *name) {
	int size = this->objects.size();
	int i;

	for (i = 0; i < size; i++) {

		if (this->objects[i]->getName().empty()) {
			continue;
		}

		if (this->objects[i]->getName().compare(name) == 0) {
			return this->objects[i];
		}
	}

	return NULL;
}

