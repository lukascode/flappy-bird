#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <string>

class Text {
public:
	Text(ALLEGRO_FONT* font, std::string text, float pos_x, float pos_y) {
		this->font = font;
		this->text = text;
		this->r = r;
		this->g = g;
		this->b = b;
		this->pos_x = pos_x;
		this->pos_y = pos_y;
	}

	void setPosition(int x, int y) {
		pos_x = x;
		pos_y = y;
	}

	void setColor(int r, int g, int b) {
		this->r = r;
		this->g = g;
		this->b = b;
	}

	void setText(std::string text) {
		this->text = text;
	}

	void draw() {
		al_draw_text(font, al_map_rgb(r, g, b), pos_x, pos_y, 0, text.c_str());
	}

private:
	std::string text;
	ALLEGRO_FONT* font;
	int r, g, b;
	float pos_x, pos_y;
};