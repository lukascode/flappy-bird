#pragma once

#include "Object.h"
#include "Resources.h"

class GameOver : public Object {
public:
	void init() {
		scaleFactorX = scaleFactorY = 0.5;
		Resources* res = Resources::getInstance();
		bitmap = res->getBitmap("gameover");

		x = 120;
		y = 130;

		Object::init();
	}
};

