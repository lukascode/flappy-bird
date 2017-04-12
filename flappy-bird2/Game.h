#pragma once
#include "MenuBackground.h"
#include "Text.h"
#include "Resources.h"
#include "allegro5/allegro.h"
#include "Bird.h"
#include "MenuBackground.h"
#include "TubeDown.h"
#include "TubeUp.h"
#include "ScrollTubes.h"
#include "Text.h",
#include "Windows.h"
#include "GameOver.h"


class Game {
public:
	Game() {
		bird = NULL;
		background = NULL;
		scrollTubes = NULL;
		gameoverPNG = NULL;
		gameOver = false;
		realGameOver = false;
		init();
	}
	void init() {
		destroy();
		bird = new Bird();
		background = new MenuBackground();
		scrollTubes = new ScrollTubes(bird);
		gameoverPNG = new GameOver();
		gameoverPNG->init();
		bird->init();
		background->init();
		gameOver = false;
		realGameOver = false;
	}
	void destroy() {
		if (bird != NULL) delete bird;
		if (background != NULL) delete background;
		if (scrollTubes != NULL) delete scrollTubes;
		if (gameoverPNG != NULL) delete gameoverPNG;
		gameoverPNG = NULL;
		scrollTubes = NULL;
		bird = NULL;
		background = NULL;
	}

	void render() {
		background->render();
		scrollTubes->render();
		bird->render();
		showPoints();
		if (realGameOver) gameoverPNG->render();
	}

	void handleEvent(ALLEGRO_EVENT* event) {
		if (event->type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (event->keyboard.keycode) {
			case ALLEGRO_KEY_SPACE: 
				if (!gameOver) {
					bird->jump();
					scrollTubes->startScroll();
					al_play_sample(Resources::getInstance()->getSample("jump"),
						1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
				}
				break;
			case ALLEGRO_KEY_C: scrollTubes->startScroll(); break;
			case ALLEGRO_KEY_X: scrollTubes->stopScroll(); break;
			case ALLEGRO_KEY_UP: bird->up(); break;
			case ALLEGRO_KEY_DOWN: bird->down(); break;
			case ALLEGRO_KEY_LEFT: bird->left(); break;
			case ALLEGRO_KEY_RIGHT: bird->right(); break;
			}
		} 
	
	}

	void update() {
		background->update();
		scrollTubes->update();
		bird->update();
		if (scrollTubes->collision(*bird) || (bird->getY() < 0) || (bird->getY() + bird->getHeight() > HEIGHT)) {
			gameOver = true;
			scrollTubes->stopScroll();
			
		}
		if (gameOver == true) {
			if (bird->getY() + bird->getHeight() + 2 >= HEIGHT) {
				bird->stop();
				realGameOver = true;
			}
		}
	}
	
private:
	Bird* bird;
	MenuBackground* background;
	ScrollTubes* scrollTubes;
	bool gameOver;
	bool realGameOver;
	GameOver* gameoverPNG;
	

	void showPoints() {
		Resources* res = Resources::getInstance();
		std::string scoreText = "SCORE: " + std::to_string(bird->getScore());
		Text* score = new Text(res->getFont("oswald-bold25"), scoreText, 10, 10);
		score->setColor(160, 237, 255);
		score->draw();
		delete score;
	}

	
};