#pragma once
#include "Object.h"
#include "Resources.h"

class MenuBackground : public Object {
public:
	void init() {
		Resources* res = Resources::getInstance();
		bitmap = res->getBitmap("menu_background");
		Object::init();
	}
};