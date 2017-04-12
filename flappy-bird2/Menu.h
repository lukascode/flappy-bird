#pragma once
#include "MenuBackground.h"
#include "Text.h"
#include "Resources.h"

enum ActionMenu { NEWGAME, AUTHORS, QUIT };

struct PositionMenu {
public:
	PositionMenu(Text* text) {
		this->text = text;
		if (text) {
			default();
		}
	}
	~PositionMenu() {
		if (text) {
			delete text;
		}
	}

	void active() {
		text->setColor(ar, ag, ab);
	}
	void default() {
		text->setColor(dr, dg, db);
	}

	void draw() {
		text->draw();
	}

	ActionMenu action;
private:
	Text* text;
	
	//default color
	static const int dr = 255, dg = 0, db = 255;

	//active color
	static const int ar = 137, ag = 10, ab = 255;
};

struct PositionManager {
public:
	PositionManager(int posx, int posy, int space) {
		this->space = space;
		x = posx;
		y = posy;
		next_x = x;
		next_y = y;
		current = 0;
	}

	~PositionManager() {
		for (int i = 0; i < positions.size(); ++i) {
			if (positions[i])
				delete positions[i];
		}
		positions.clear();
	}

	void addPosition(std::string text, ActionMenu action) {
		Resources* res = Resources::getInstance();
		ALLEGRO_FONT* font = res->getFont(fontName);
		positions.push_back(new PositionMenu(new Text(font, text, next_x, next_y)));
		positions[positions.size() - 1]->action = action;
		next_y += space + al_get_font_line_height(font);
		if (positions.size() == 1) positions[0]->active();
	}

	void draw() {
		for (int i = 0; i < positions.size(); ++i) {
			positions[i]->draw();
		}
	}

	void up() {
		if (positions.size() == 0) return;
		positions[current]->default();
		if (current == 0) current = positions.size() - 1;
		else --current;
		positions[current]->active();
	}
	void down() {
		if (positions.size() == 0) return;
		positions[current]->default();
		if (current == positions.size()-1) current = 0;
		else ++current;
		positions[current]->active();
	}

	ActionMenu getCurrentAction() {
		return positions[current]->action;
	}
	
private:
	int space;
	std::vector<PositionMenu*> positions;
	int x, y;
	int next_x, next_y;
	int current;
	static const std::string fontName; 

};

const std::string PositionManager::fontName = "oswald-bold25";

class Menu {

public:
	Menu() : manager(200, 200, 5), background(), logo() {
		background.init();
		logo.init();

		Resources* res = Resources::getInstance();
		by = new Text(res->getFont("pacifico18"), "by Lukas & Tomasz", 480, 98);
		by->setColor(72, 173, 128);



		manager.addPosition("New Game", NEWGAME);
		manager.addPosition("Authors", AUTHORS);
		//manager.addPosition("Scores");
		manager.addPosition("Quit", QUIT);
	}
	~Menu() {
		if (by) delete by;
	}

	void draw() {
		background.render();
		logo.render();
		by->draw();
		manager.draw();
		ActionMenu a = action();
		switch (a) {
		case AUTHORS: drawAuthors(); break;
		case NEWGAME: drawNewGameInfo(); break;
		case QUIT: drawQuitInfo(); break;
		}
	}

	void up() {
		manager.up();
	}
	void down() {
		manager.down();
	}
	ActionMenu action() {
		return manager.getCurrentAction();
	}

private:
	PositionManager manager;
	MenuBackground background;
	Logo logo;
	Text* by;

	void drawAuthors() {
		int r = 130, g = 244, b = 255;
		const int x = 400, y = 220;
		Resources* res = Resources::getInstance();
		ALLEGRO_FONT* font = res->getFont("lato-regular16");
		Text* authors = new Text(font, "Authors", x, y);
		authors->setColor(r, g, b);
		Text* names = new Text(font, "Lukasz Sakowicz and Tomasz Suchwalko", x, y+20);
		names->setColor(r, g, b);
		Text* pb = new Text(font, "Politechnika Bialostocka 05.12.2016", x, y+40);
		pb->setColor(r, g, b);
		
		authors->draw();
		names->draw();
		pb->draw();

		delete authors;
		delete names;
		delete pb;
	}

	void drawNewGameInfo() {
		int r = 130, g = 244, b = 255;
		const int x = 400, y = 220;
		Resources* res = Resources::getInstance();
		ALLEGRO_FONT* font = res->getFont("lato-regular16");

		Text* newgame = new Text(font, "Start a New Game", x, y);
		newgame->setColor(r, g, b);

		newgame->draw();

		delete newgame;
	}

	void drawQuitInfo() {
		int r = 130, g = 244, b = 255;
		const int x = 400, y = 220;
		Resources* res = Resources::getInstance();
		ALLEGRO_FONT* font = res->getFont("lato-regular16");

		Text* close = new Text(font, "Close Application", x, y);
		close->setColor(r, g, b);

		close->draw();

		delete close;
	}

};