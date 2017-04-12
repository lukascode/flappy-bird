#pragma once
#include "Object.h"
#include "Resources.h"
#include "Globals.h"

class TubeDown : public Object {
public:

	TubeDown() {
		randomHeightTable = { 0.18, 0.20, 0.22 };
	}
	void init() {
		scaleFactorX = 0.16;
		scaleFactorY = 0.21;
		Resources* res = Resources::getInstance();
		bitmap = res->getBitmap("tubeDown");

		Object::init();

		x = WIDTH - width - 5;
		y = HEIGHT - height;

		//std::cout << "TubeDown width: " << width << std::endl;
		//velX = -40;
	}

	void setVelocityX(float v) {
		this->velX = v;
	}

	void setPosition(int x, int y) {
		this->x = x;
		this->y = y;
	}

	void randomHeight() {
		scaleFactorY = randomHeightTable[rand() % 3];
		Object::init();
	}

private:
	std::vector<double> randomHeightTable;
};