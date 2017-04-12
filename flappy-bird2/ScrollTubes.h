#pragma once
#include "TubeDown.h"
#include "TubeUp.h"
#include "Globals.h"
#include "Bird.h"

class ScrollTubes;

struct TubesPair {
	TubesPair() {
		tdown = new TubeDown(); tdown->init();
		tup = new TubeUp(); tup->init();
		tdown->randomHeight();
		tup->randomHeight();
		this->givePointsFlag = false;
	}
	~TubesPair() {
		if (tup) delete tup;
		if (tdown) delete tdown;
	}

	void random() {
		tup->randomHeight();
		tdown->randomHeight();
		setPosition(tup->getX(), tup->getY());
	}

	void render() {
		tdown->render();
		tup->render();
	}

	void update() {
		tdown->update();
		tup->update();
	}

	void setVelocity(float vel) {
		tdown->setVelocityX(vel);
		tup->setVelocityX(vel);
	}
	void setPosition(int x, int y) {
		tup->setPosition(x, y);
		tdown->setPosition(x, HEIGHT - tdown->getHeight());
	}

	bool collision(const Object& obj) const {
		return tdown->collision(obj) || tup->collision(obj);
	}


private:
	TubeDown* tdown;
	TubeUp* tup;
	bool givePointsFlag;

	friend class ScrollTubes;
};

class ScrollTubes {
public: 
	ScrollTubes(Bird* bird) : speed(-180.0) {
		this->bird = bird;
		const int x = WIDTH, y = 0;
		const int space = 200;
		const int N = 3;
		
		for (int i = 0; i < N; ++i) {
			tubes.push_back(new TubesPair()); 
			tubes[i]->setPosition(x + i*tubes[i]->tup->getWidth() + i*space, y);
		}
	}
	~ScrollTubes() {
		for (int i = 0; i < tubes.size(); ++i) {
			if (tubes[i] != NULL)
				delete tubes[i];
		}
		tubes.clear();
	}
	void startScroll() {
		for (int i = 0; i < tubes.size(); ++i) {
			tubes[i]->setVelocity(speed);
		}
	}
	void stopScroll() {
		for (int i = 0; i < tubes.size(); ++i) {
			tubes[i]->setVelocity(0.0);
		}
	}
	void update() {
		for (int i = 0; i < tubes.size(); ++i) {
			tubes[i]->update();
		}
		moveFirstTube();
		givePointsForBird();
	}

	void render() {
		for (int i = 0; i < tubes.size(); ++i) {
			tubes[i]->render();
		}
	}

	bool collision(const Object& obj) const {
		for (int i = 0; i < tubes.size(); ++i) {
			if (tubes[i]->collision(obj))
				return true;
		}
		return false;
	}


private:
	std::vector<TubesPair*> tubes;
	Bird* bird;
	
	const float speed;

	void moveFirstTube() {
		int posx = tubes[0]->tup->getX();
		int width = tubes[0]->tup->getWidth();
		if (posx + width < 0) {
			TubesPair* tube = tubes[0];
			tubes.erase(tubes.begin());
			tube->setPosition(WIDTH, 0);
			tube->random();
			tube->givePointsFlag = false;
			tubes.push_back(tube);
		}
	}

	void givePointsForBird() {
		for (int i = 0; i < tubes.size(); ++i) {
			if (bird->getX() > tubes[i]->tup->getX() + tubes[i]->tup->getWidth() && !tubes[i]->givePointsFlag) {
				bird->addPoint();
				tubes[i]->givePointsFlag = true;
				al_play_sample(Resources::getInstance()->getSample("point"),
					1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
			}
		}
	}
};