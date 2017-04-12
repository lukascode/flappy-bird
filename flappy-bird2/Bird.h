#pragma once
#include "Object.h"
#include "Resources.h"
#include "Globals.h"

class Bird : public Object {
public:
	Bird() : Object() {
		frame1 = NULL;
		frame2 = NULL;
		score = 0;
	}
	void init() {
		scaleFactorX = scaleFactorY = 0.07;
		Resources* res = Resources::getInstance();
		bitmap = res->getBitmap("birdf1");
		frame2 = res->getBitmap("birdf2");
		frame1 = bitmap;
		
		Object::init();

		x = WIDTH / 2 - width / 2;
		y = HEIGHT/ 2 - height / 2;
	}

	void update() {
		Object::update();
		if (velY < 0 && rotDegree > -45.0) rotDegree -= 1.0;
		else if (velY > 0 && rotDegree < 45.0) rotDegree += 1.0;
		const float frameDelay = 0.1;
		static float lastFrameSwitch = al_current_time();
		if (al_current_time() - lastFrameSwitch >= frameDelay) {
			lastFrameSwitch = al_current_time();
			switchFrame();
		}
	}

	void jump() {
		//velY = -500.0;
		//aY = 800.0;
		velY = -500;
		aY = 1200;
	}

	void stop() {
		velY = 0;
		aY = 0;
		velX = 0;
		aX = 0;
	}

	void up() { y -= 10; }
	void down() { y += 10; }
	void left() { x -= 10; }
	void right() { x += 10; }

	void addPoint() {
		this->score += 1;
	}
	int getScore() {
		return this->score;
	}


private:
	ALLEGRO_BITMAP* frame1;
	ALLEGRO_BITMAP* frame2;
	int score;

	void switchFrame() {
		bitmap = (bitmap == frame1) ? frame2 : frame1;
	}
	
};