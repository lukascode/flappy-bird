#pragma once
#include "Object.h"
#include "Resources.h"

class TubeUp : public Object {
public:
	TubeUp() {
		randomHeightTable = { 0.18, 0.20, 0.22 };
	}
	void init() {
		scaleFactorX = 0.16;
		scaleFactorY = 0.21;
		Resources* res = Resources::getInstance();
		bitmap = res->getBitmap("tubeUp");

		Object::init();

		x = WIDTH - width - 5;
		y = 0;

		//std::cout << "TubeUp width: " << width << std::endl;
		//velX = -100;
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