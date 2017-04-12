#include "Object.h"

Object::Object() {
	x = y = 0.0;
	velX = velY = 0.0;
	aX = aY = 0.0;
	width = height = 0;
	rotDegree = 0;
	scaleFactorX = 1;
	scaleFactorY = 1;
	ID = -1;
	bitmap = NULL;
	objectTimer = al_current_time();
}

int Object::getX() { return this->x; }
int Object::getY() { return this->y; }


Object::~Object() {
	destroy();
}

int Object::getWidth() {
	return this->width;
}

int Object::getHeight() {
	return this->height;
}

void Object::update() {
	
	//velocity upgrade
	float now = al_current_time();
	velX += aX*(now - objectTimer);
	velY += aY*(now - objectTimer);

	//position update
	x += velX*(now - objectTimer);
	y += velY*(now - objectTimer);

	objectTimer = now;
}

void Object::destroy() {
	
}

void Object::render() {
	al_draw_scaled_rotated_bitmap(this->bitmap, 0, 0, x, y, scaleFactorX, scaleFactorY, (rotDegree*PI)/180, 0);
}

void Object::init() {
	width = al_get_bitmap_width(bitmap)*scaleFactorX;
	height = al_get_bitmap_height(bitmap)*scaleFactorY;
}

bool Object::collision(const Object& obj) const {
	if ( (x < obj.x + obj.width) && ((x + width) > obj.x) &&
		(y < (obj.y + obj.height)) && ((y + height) > obj.y) ) return true;
	return false;
}