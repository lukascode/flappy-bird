#pragma once

#include <allegro5/allegro.h>
#include <cmath>
#include "Globals.h"

class Object {
public:
	int getWidth();
	int getHeight();
	int getX();
	int getY();

	bool collision(const Object& obj) const;

	virtual void init();
	virtual void update();
	virtual void destroy();
	virtual void render();

	Object();
	virtual ~Object();

protected:
	float x, y;
	float velX, velY;
	float aX, aY;
	int width, height;
	int rotDegree;
	float scaleFactorX;
	float scaleFactorY;
	float objectTimer;

	ALLEGRO_BITMAP* bitmap;

	int ID;

};