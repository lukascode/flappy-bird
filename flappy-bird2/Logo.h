#pragma once
#include "Object.h"
#include "Resources.h"

class Logo : public Object {
public:
	void init() {
		scaleFactorX = scaleFactorY = 0.5;
		Resources* res = Resources::getInstance();
		bitmap = res->getBitmap("logo");

		x = 150;
		y = 20;

		Object::init();
	}
};